int meanval = 0; // Mean illuminance value in LED OFF state - for robust system
int input = 0; // Save analog input from A0
int signalset[10]; // Calculate grad
float grad = 0.0; // Save grad
int bitbuf[9]={0,0,0,0,0,0,0,0,0}; // bitbuf means one character(Byte), use 9 bits because of parity bit and indexing problem. 7 bits for ascii
char Byte; // save byte


void setup() {
 Serial.begin(2000000); // check input as 2M baud(very fast)

 // Make mean value, the LED OFF state, because of robust system. 
 
 for(int i=0; i<10; i++){
    input = analogRead(0); // read input from A0
    meanval += input; // generate meanval - sum part
    }
  meanval/=10; //generate meanval - make mean value part from summation
}

void loop() {
  int count = 0; // for determining sig
  float sig = 0.0; // determine the bit is 0 or 1 

  //always be ready for taking signal
  
  while(count < 10){ // in average time
    
    for(int i=0;i<10;i++){
      input = analogRead(0);
      signalset[i] = input-meanval;
      if (i == 9){
        grad = signalset[9]-signalset[0]; // use the average of change to make robust system
        }
      }
      
    if (abs(grad) >= 20){
      sig+=1;
      count++;
      }
      
    else if (abs(grad) >= 10){
      count++;
      }
      
  }
  
  sig/=10;
  
  if(sig > 0.5){
    bitbuf[bitbuf[8]] = 1;
    bitbuf[8] = bitbuf[8]+1;
  }
  
  else{
    bitbuf[bitbuf[8]] = 0;
    bitbuf[8] = bitbuf[8]+1;
  }
  
  if(bitbuf[8] == 8){
    bitbuf[8] = 0;
    Byte = 64*bitbuf[1] + 32*bitbuf[2]+ 16*bitbuf[3] + 8*bitbuf[4]+ 4*bitbuf[5]+ 2*bitbuf[6] + bitbuf[7];
    if((bitbuf[0] + bitbuf[1] + bitbuf[2]+ bitbuf[3] + bitbuf[4]+ bitbuf[5]+ bitbuf[6] + bitbuf[7]) % 2 != 0){ // use even parity bit
      Serial.println("ERROR BYTE");
    }
    else{
      Serial.print(Byte);
      }
    }
    
}
