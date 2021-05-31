int meanval = 0; // check illuminance
int first = 0; // for making an average rate of change
int last = 0; // for making an average rate of change
int input = 0; // for saving analog input from A0
float grad = 0.0; // saving grad
int signalset[10]; // for calculating grad
int outsignalset[10]; // for determining the signal

void setup() {
 Serial.begin(2000000); // check input as 2M baud(very fast)
 for(int i=0; i<10; i++){
    input = analogRead(0); // read input from A0
    meanval += input;
    }
  meanval/=10; //generate meanval
}
void loop() {
  for(int i=0;i<10;i++){
    input = analogRead(0);
    signalset[i] = input-meanval;
    if (i == 9){
      grad = signalset[9]-signalset[0];
      }
  }
  if (abs(grad) >= 20){
    Serial.println(1);
  }
  else if (abs(grad) >= 10){
    Serial.println(0);
    }
  else{
  }
  }
 
