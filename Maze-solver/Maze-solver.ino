
#define leftMiddleSensor   3
#define leftInSensor     4
#define leftOutSensor      5
#define rightMiddleSensor  2
#define rightInSensor    1
#define rightOutSensor     0

int leftMiddleReading;
int leftInReading;
int leftOutReading;
int rightMiddleReading;
int rightInReading;
int rightOutReading;

int leftNudge;
int replaystage;
int rightNudge;

#define leapTime 200

#define leftMotorForward  7
#define leftMotorBackward  6

#define rightMotorForward 5
#define rightMotorBackward 8

#define led 13

char path[30] = {};
int pathLength;
int readLength;

void setup(){
  
  pinMode(leftMiddleSensor, INPUT);
  pinMode(leftInSensor, INPUT);
  pinMode(leftOutSensor, INPUT);
  pinMode(rightMiddleSensor, INPUT);
  pinMode(rightInSensor, INPUT);
  pinMode(rightOutSensor, INPUT);
    
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);
  pinMode(led, OUTPUT);
  //Serial.begin(115200);
  digitalWrite(led, HIGH);
  delay(1000);
}


void loop(){
  
 readSensors();                                                                                     
 
 if(leftOutReading<200 && rightOutReading<200 && 
   (leftMiddleReading>200 || rightMiddleReading>200) ){ 
    straight();                                                                                      
  }
  else{                                                                                              
    leftHandWall();                                                                                   
  }

}

void readSensors(){
  
  leftMiddleReading  = analogRead(leftMiddleSensor);
  leftInReading    = analogRead(leftInSensor);
  leftOutReading     = analogRead(leftOutSensor);
  rightMiddleReading = analogRead(rightMiddleSensor);
  rightInReading   = analogRead(rightInSensor);
  rightOutReading    = analogRead(rightOutSensor);  

// serial printing below for debugging purposes

// Serial.print("leftMiddleReading: ");
// Serial.println(leftMiddleReading);
// Serial.print("leftInReading: ");
// Serial.println(leftInReading);
// Serial.print("leftOutReading: ");
// Serial.println(leftOutReading);
  
// Serial.print("rightMiddleReading: ");
// Serial.println(rightMiddleReading);
// Serial.print("rightInReading: ");
// Serial.println(rightInReading);
// Serial.print("rightOutReading: ");
// Serial.println(rightOutReading);
// delay(200);
  

}


void leftHandWall(){
  

  if( leftOutReading>200 && rightOutReading>200){
    digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(rightMotorBackward, LOW);
    delay(leapTime);
    readSensors();
    
    if(leftOutReading>200 || rightOutReading>200){
      done();
    }
    if(leftOutReading<200 && rightOutReading<200){ 
      turnLeft();
    }
    
  }
  
  if(leftOutReading>200){ // if you can turn left then turn left
    digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(rightMotorBackward, LOW);
    delay(leapTime);
    readSensors();
      
      if(leftOutReading<200 && rightOutReading<200){
        turnLeft();
      }
      else{
        done();
      }
  }
   
  if(rightOutReading>200){
    digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(rightMotorBackward, LOW);
    delay(30);
    readSensors();
    
    if(leftOutReading>200){
      delay(leapTime-30);
      readSensors();
      
      if(rightOutReading>200 && leftOutReading>200){
        done();
      }
      else{
        turnLeft();
        return;
      }
    }
    delay(leapTime-30);
    readSensors();
    if(leftOutReading<200 && leftMiddleReading<200 &&
      rightMiddleReading<200 && rightOutReading<200){
      turnRight();
      return;
    }
    path[pathLength]='S';
   // Serial.println("s");
    pathLength++;
    //Serial.print("Path length: ");
    //Serial.println(pathLength);
    if(path[pathLength-2]=='B'){
    //Serial.println("shortening path");
    shortPath();
     }
    straight();
  }
  readSensors();
  if(leftOutReading<200 && leftMiddleReading<200 && rightMiddleReading<200 
    && rightOutReading<200 && leftInReading<200 && rightInReading<200){
    turnAround();
  }

}
void done(){
  digitalWrite(leftMotorForward, LOW);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, LOW);
    digitalWrite(rightMotorBackward, LOW);
  replaystage=1;
  path[pathLength]='D';
  pathLength++;
 while(analogRead(leftOutSensor)>200){
   digitalWrite(led, LOW);
   delay(150);
   digitalWrite(led, HIGH);
   delay(150);
 }
 delay(500);
  replay();
}

void turnLeft(){
  
    
 
  while(analogRead(rightMiddleSensor)>200||analogRead(leftMiddleSensor)>200){
     digitalWrite(leftMotorForward, LOW);
    digitalWrite(leftMotorBackward, HIGH);
    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(rightMotorBackward, LOW);
    delay(2);
     digitalWrite(leftMotorForward, LOW);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, LOW);
    digitalWrite(rightMotorBackward, LOW);
    delay(1);
  }
    
  while(analogRead(rightMiddleSensor)<200){
    digitalWrite(leftMotorForward, LOW);
    digitalWrite(leftMotorBackward, HIGH);
    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(rightMotorBackward, LOW);
    delay(2);
    digitalWrite(leftMotorForward, LOW);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, LOW);
    digitalWrite(rightMotorBackward, LOW);
    delay(1);
  }
 
  if(replaystage==0){
    path[pathLength]='L';
    //Serial.println("l");
    pathLength++;
    //Serial.print("Path length: ");
    //Serial.println(pathLength);
      if(path[pathLength-2]=='B'){
        //Serial.println("shortening path");
        shortPath();
      }
  }
}

void turnRight(){

    
  while(analogRead(rightMiddleSensor)>200){
     digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, LOW);
    digitalWrite(rightMotorBackward, HIGH);
    delay(2);
     digitalWrite(leftMotorForward, LOW);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, LOW);
    digitalWrite(rightMotorBackward, LOW);
    delay(1);
  }
   while(analogRead(rightMiddleSensor)<200){
     digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, LOW);
    digitalWrite(rightMotorBackward, HIGH);
    delay(2);
     digitalWrite(leftMotorForward, LOW);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, LOW);
    digitalWrite(rightMotorBackward, LOW);
    delay(1);
  }
   while(analogRead(leftMiddleSensor)<200){
     digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, LOW);
    digitalWrite(rightMotorBackward, HIGH);
    delay(2);
    digitalWrite(leftMotorForward, LOW);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, LOW);
    digitalWrite(rightMotorBackward, LOW);
    delay(1);
  }
  
  if(replaystage==0){
  path[pathLength]='R';
  Serial.println("r");
  pathLength++;
  Serial.print("Path length: ");
  Serial.println(pathLength);
    if(path[pathLength-2]=='B'){
      Serial.println("shortening path");
      shortPath();
    }
  }
 
}

void straight(){
  if( analogRead(leftMiddleSensor)<200){
    digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(rightMotorBackward, LOW);
    delay(1);
    digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, LOW);
    digitalWrite(rightMotorBackward, LOW);
    delay(5);
    return;
  }
  if(analogRead(rightMiddleSensor)<200){
    digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(rightMotorBackward, LOW);
    delay(1);
    digitalWrite(leftMotorForward, LOW);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(rightMotorBackward, LOW);
    delay(5);
    return;
  }
  
    digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(rightMotorBackward, LOW);
    delay(4);
    digitalWrite(leftMotorForward, LOW);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, LOW);
    digitalWrite(rightMotorBackward, LOW);
    delay(1);
  
}

void turnAround(){
    digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(rightMotorBackward, LOW);
    delay(150);
   while(analogRead(leftMiddleSensor)<200){
     digitalWrite(leftMotorForward, LOW);
    digitalWrite(leftMotorBackward, HIGH);
    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(rightMotorBackward, LOW);
    delay(2);
     digitalWrite(leftMotorForward, LOW);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, LOW);
    digitalWrite(rightMotorBackward, LOW);
    delay(1);
  }
  path[pathLength]='B';
  pathLength++;
  straight();
  //Serial.println("b");
  //Serial.print("Path length: ");
  //Serial.println(pathLength);
}

void shortPath(){
 int shortDone=0;
  if(path[pathLength-3]=='L' && path[pathLength-1]=='R'){
    pathLength-=3;
    path[pathLength]='B';
    //Serial.println("test1");
    shortDone=1;
  }
   
  if(path[pathLength-3]=='L' && path[pathLength-1]=='S' && shortDone==0){
    pathLength-=3;
    path[pathLength]='R';
    //Serial.println("test2");
    shortDone=1;
  }
   
  if(path[pathLength-3]=='R' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='B';
    //Serial.println("test3");
    shortDone=1;
  }
  
   
  if(path[pathLength-3]=='S' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='R';
    //Serial.println("test4");
    shortDone=1;
  }
     
  if(path[pathLength-3]=='S' && path[pathLength-1]=='S' && shortDone==0){
    pathLength-=3;
    path[pathLength]='B';
    //Serial.println("test5");
    shortDone=1;
  }
    if(path[pathLength-3]=='L' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='S';
    //Serial.println("test6");
    shortDone=1;
  }
  
  path[pathLength+1]='D';
  path[pathLength+2]='D';
  pathLength++;
  //Serial.print("Path length: ");
  //Serial.println(pathLength);
  //printPath();
}




void printPath(){
  Serial.println("+++++++++++++++++");
  int x;
  while(x<=pathLength){
  Serial.println(path[x]);
  x++;
  }
  Serial.println("+++++++++++++++++");
}


void replay(){
   readSensors();
  if(leftOutReading<200 && rightOutReading<200){
    straight();
  }
  else{
    if(path[readLength]=='D'){
       digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(rightMotorBackward, LOW);
    delay(100);
    digitalWrite(leftMotorForward, LOW);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, LOW);
    digitalWrite(rightMotorBackward, LOW);
      endMotion();
    }
    if(path[readLength]=='L'){
     digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(rightMotorBackward, LOW);
    delay(leapTime);
      turnLeft();
    }
    if(path[readLength]=='R'){
       digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(rightMotorBackward, LOW);
    delay(leapTime);
    turnRight();
    }
    if(path[readLength]=='S'){
       digitalWrite(leftMotorForward, HIGH);
    digitalWrite(leftMotorBackward, LOW);
    digitalWrite(rightMotorForward, HIGH);
    digitalWrite(rightMotorBackward, LOW);
    delay(leapTime);
    straight();
    }
    
    readLength++;
  }
    
  replay();
  
}

void endMotion(){
    digitalWrite(led, LOW);
    delay(500);
    digitalWrite(led, HIGH);
    delay(200);
      digitalWrite(led, LOW);
    delay(200);
    digitalWrite(led, HIGH);
    delay(500);
  endMotion();
}


