  #include <SimpleTimer.h>   
  #include <Servo.h>
   
  Servo myservo;
  SimpleTimer timer;
   
  int led = 13;
  int led2 = 12;
  int pos = 0;
  int total = 0;
  int called = 0;
  long randPassive;
  int timerId;
  
  void setup() {
    Serial.begin(9600);    
    pinMode(led, OUTPUT);
    pinMode(led2, OUTPUT);
    myservo.attach(9);
    myservo.write(180);
    timer.setTimeout(10000,lightEyes);
    timerId = timer.setInterval(3300,passiveMoving);
  }
  
  void loop() {
   timer.run();
  }
  
  void lightEyes(){
    timer.disable(timerId);   
    myservo.write(180);
    digitalWrite(led, HIGH);
    digitalWrite(led2, HIGH);
    delay(5000);
    timer.setTimer(500,crazyHead, 12);
    timer.setTimer(50, flickEyes, 100);
  }
  
  void flickEyes(){
    digitalWrite(led,HIGH);
    digitalWrite(led2,HIGH);
    delay(5);
    digitalWrite(led,LOW);
    digitalWrite(led2,LOW);
  }
  
  
  void crazyHead(){
    if ( pos >= 0 && pos < 180 ) { pos = 180; }
    else if ( pos <= 180 ) { pos = 0; }
    myservo.write( pos );
    called +=1;
    if(called == 12){
      called = 0; 
      slowTurn();
    }
  }
  
  void slowTurn(){
      digitalWrite(led, HIGH);
      digitalWrite(led2, HIGH);
      for(int i = 180; i >= 0; i-=10){
        myservo.write(i);
        delay(300);
      }
      delay(4000);
      resetHead();
  }
  
  void passiveMoving(){
    randPassive = random(140,180);
    myservo.write(randPassive);
  }
  
  void resetHead(){
     digitalWrite(led, LOW);
     digitalWrite(led2, LOW);
     myservo.write(180);
     timer.setTimeout(10000,lightEyes);
     timer.enable(timerId);
  }
