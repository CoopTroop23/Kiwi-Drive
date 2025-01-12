#include <math.h>
//radio stuff

int pulses = 0;
const int NUM_VALS = 9;
unsigned long controllerVals [NUM_VALS];
//variables for finding the begining of the signal
unsigned long cTime = 0; //current time
unsigned long pTime = 0; //past time
unsigned long dTime = 0; //change in time (delta time)
bool foundFront = false;
const unsigned long MAX_PULSE_LENGTH = 2100; //threashold for signal to be considerd a sync




double vx = 0;
double vy = 0;
double w = 0;
int MAXSPEED = 255;
const double MIDPOINT = 1500;

unsigned long moveTime = 0;


//motor stuff
struct motor{
  int dPin1;
  int dPin2;
  int sPin;
  double speed = 0;
  int direction = 0;
  motor(int d1, int d2, int s){
    dPin1 = d1;
    dPin2 = d2;
    sPin = s;
  }
};

//initalizing motor stuff
motor motor1(A0, A1, 9);
motor motor2(A2, A3, 10);
motor motor3(A4, A5, 11);


void setup() {
  Serial.begin(115200);
  
  pinMode(2,INPUT); //setting the interupt to input
  attachInterrupt(digitalPinToInterrupt(2),setTime,RISING);//defining the interupt


  //initialize motor speed to zero
  initMotor(motor1);
  initMotor(motor2);
  initMotor(motor3);

}

void loop() {
  //calculate linear and angular velocity
  vx = controllerVals[4] - MIDPOINT;
  vy = controllerVals[3] - MIDPOINT;
  //clip the end of the vector so it is only one max length
  double v = sqrt(pow(vx,2)+pow(vy,2));
  if(v > 500.0){
    vx = vx*500.0/v;  //vx /= v;
    vy = vy*500.0/v;
  }
  
  w = (controllerVals[1] - MIDPOINT);// / double(MIDPOINT);
  //make sure the velocity is a number. dont divide by zero!

  //set the speeds of all the motors
  
  motor1.speed = -vx*0.73 - (vy*sqrt(3)) - w;
  motor2.speed = vx - w;
  motor3.speed = -vx*0.73 + (vy*sqrt(3)) - w;

  //interrupting cow... MOOOOVE! the robot
  if(millis() - moveTime > 10 && controllerVals[0] != 0){
    moveMotor(motor1);
    moveMotor(motor2);
    moveMotor(motor3);
    moveTime = millis();
  }
  Serial.print(motor1.speed);
  Serial.print(' ');
  Serial.println(motor2.speed);
}

void moveMotor(motor m){ 
  uint8_t s = map(abs(m.speed),0,500,0,255);
  if(m.speed < 0){
    digitalWrite(m.dPin1,HIGH);
    digitalWrite(m.dPin2,LOW);
    analogWrite(m.sPin,s);
  }else if(m.speed > 0){
    digitalWrite(m.dPin1, LOW);
    digitalWrite(m.dPin2, HIGH);
    analogWrite(m.sPin, s);
  }else{
    digitalWrite(m.dPin1, LOW);
    digitalWrite(m.dPin2, LOW);
    analogWrite(m.sPin, 0);
  }
}

void initMotor(motor m){
  //set outputs as outputs
  pinMode(m.dPin1,OUTPUT);
  pinMode(m.dPin2,OUTPUT);
  pinMode(m.sPin,OUTPUT);
  //make motor not move
  digitalWrite(m.dPin1, LOW);
  digitalWrite(m.dPin2, LOW);
  analogWrite(m.sPin, 0);
}

void setTime(){
  cTime = micros();
  
  dTime = cTime - pTime;
  if(foundFront == true){
    if(pulses >= NUM_VALS || dTime > 2500){
      pulses = 0;
    }
    //making a deadzone
    if(abs(dTime - MIDPOINT) < 10){
      dTime = MIDPOINT;
    }
    // setting the values in the values array
    controllerVals[pulses] = dTime;
      
  }else{//the front of the signal is not found
    //find the front
    if(dTime >= MAX_PULSE_LENGTH){
      pulses = 0;
      foundFront = true;
    }
  }
  
  pulses++;
  pTime = cTime;
}
