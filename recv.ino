char a;
int illum = 0;
int count = 0;
int state = 1;
int bitbuf[9] = {0,};
float buf = 0.0;
float grad = 0.0;
unsigned long time;

void setup() {
  Serial.begin(2000000);
  time = micros();
  
}

void loop() {
  if(bitbuf[8] == 8){
    if((bitbuf[1]+bitbuf[2]+bitbuf[3]+bitbuf[4]+bitbuf[5]+bitbuf[6]+bitbuf[7]) % 2 != bitbuf[0]){
      Serial.println("Error Byte");
      bitbuf[8] = 0;
      }
    else{
      a = 64*bitbuf[1]+32*bitbuf[2]+16*bitbuf[3]+8*bitbuf[4]+4*bitbuf[5]+2*bitbuf[6]+bitbuf[7];
      Serial.print(a);
      bitbuf[8] = 0;
      }
    }
  illum = analogRead(0);
  illum -= analogRead(0);
  if((micros() - time < 10000)&&(abs(illum) > 300)){
    buf += analogRead(0)*state;
    count++;
    if(count == 2){
      grad+=abs(buf);
      count = 0;
      buf = 0.0;
      }
    state*=-1;
    }
  else{
    if(grad > 1000){
      bitbuf[bitbuf[8]] = 1;
      bitbuf[8] = bitbuf[8]+1;
      grad = 0.0;
      }
    else if(grad > 500){
      bitbuf[bitbuf[8]] = 1;
      bitbuf[8] = bitbuf[8]+1;
      grad = 0.0;
      }
    time = micros();
    }
  
 

}
