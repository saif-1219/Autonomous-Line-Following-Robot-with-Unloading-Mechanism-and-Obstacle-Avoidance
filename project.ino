#include <Servo.h>

  Servo myservo1;
 

  int servo1_control_pin = 17;  

  int unload_counts = 0;

  int servo1_pos = 0;
  int servo2_pos = 0;  
  // Motor A, TivaC and L298N connections
  int enA = 14;   //ENABLE pin (PD3) for Motor A to provide PWM 
  int enB = 15;
  int in1 = 6;   //IN1 pin (PA2) for Motor A for direction
  int in2 = 9;   //IN2 pin (PA3) for Motor A for direction
  int in3 = 10;
  int in4 = 11;
  
  int count = 0;
  int count2 = 0;

  int s1 = 2;
  int s2 = 3;

  int echo = 18;
  int  trig = 19;

  int r1;
  int r2;


  int speed = 150;
  int motor_left_speed = 250;
  int motor_right_speed = 250;

  long distance, duration;
  long cm = 0;
 
  bool direction = true;  //Flag for clockwise or anti-clockwise direction
  char blueTooth;
  int state = 0;

  long ultrasonic(){
      digitalWrite(trig, LOW);
      delayMicroseconds(2);
      digitalWrite(trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig, LOW);

      duration = pulseIn(echo, HIGH);   // Reads duration (microseconds) for which Echo pin reads HIGH till wave is reflected
      cm = microsecondsToCentimeters(duration);
      return cm;
  }
  
  void setup() {

    myservo1.attach(servo1_control_pin);

    //Serial initializing for Debugging
    //Specify pinModes for enA, in1 and in2 below
    Serial.begin(9600);
    pinMode(enA, OUTPUT); //Enable pin for Motor A
    pinMode(enB, OUTPUT);
    pinMode(in1, OUTPUT); //Direction pin 1 for Motor A
    pinMode(in2, OUTPUT); //Direction pin 2 for Motor A
    pinMode(in3, OUTPUT); //Direction pin 1 for Motor A
    pinMode(in4, OUTPUT); //Direction pin 2 for Motor A
  
    pinMode(s1, INPUT);
    pinMode(s2, INPUT);
    // Turn off motors - Initial state
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    pinMode(echo, INPUT);
    pinMode(trig, OUTPUT);

    TCCR0B = TCCR0B & B11111000 | B00000010 ;
  

  }
  
  void move_direction(char blueTooth){
    if (blueTooth == 'F'){
      state = 1;
    }
    else if (blueTooth == 'B'){
      state = 2;
    }
    else if (blueTooth == 'L'){
      state = 3;
    }
    else if (blueTooth == 'R'){
      state = 4;
    }
    else if (blueTooth == 'S'){
      state = 0;
    }
    else if (blueTooth == 'W'){
      state = 5;
    }
    else if (blueTooth == 'M'){
      state = 6;
    }
    else if (blueTooth == 'N'){
      state = 7;
    }
    else if (blueTooth == 'L'){
      state = 8;
    }
    else if (blueTooth == 'R'){
      state = 9;
    }
    else if (blueTooth == 'Q'){
      state = 10;
    }
  }  



long microsecondsToCentimeters(long microseconds)
{
  long distance = 0.03448 * microseconds; // 1/29 = 0.03448
  return distance / 2;
}

  void loop() {
      // delay(50); 
      r1 = digitalRead(s1);
      r2 = digitalRead(s2);

      // Make the motor run clockwise direction using in1 and in2 states below
      if(Serial.available()>0){
    
        //Read the bluetoot data and store it in colorDetect variable using Serial.read() command here
        blueTooth = Serial.read();

        //Following lines help debugging by printing whatever character recieved on Serial Monitor
        char Rec = char(blueTooth);
        if (Rec != '0')
        {
        Serial.println(Rec); //This is to visualise the received character on the serial monitor
        }  
      }

      move_direction(blueTooth);

      

      Serial.print('\n');
      Serial.print("No. of unloading = ");
      Serial.print(unload_counts);
      Serial.print('\n');

      if (state == 0){
        myservo1.write(90);
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        Serial.print("Stopped\n");
      }
      if (state == 1){
        Serial.print("Moving forward\n");
        cm = ultrasonic();
        Serial.print("dist = ");
        Serial.print(cm);
        Serial.print("\n");
        if (cm <= 15){
          state = 16;
        }
        else if (cm > 15){
          digitalWrite(in1, HIGH);
          digitalWrite(in2, LOW);
          digitalWrite(in3, HIGH);
          digitalWrite(in4, LOW);
          analogWrite(enA, 150); 
          analogWrite(enB, 225);
        }
       

      }
      else if (state == 2){
        Serial.print("Moving back\n");
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        analogWrite(enA, 150);
        analogWrite(enB, 225);
      }
      else if (state == 3){
        Serial.print("Left\n");
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        analogWrite(enA, 135);
        analogWrite(enB, 135);

      }
      else if (state == 4){
        Serial.print("Moving Right\n");
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        analogWrite(enA, 135);
        analogWrite(enA, 135);
      }
      else if (state == 5){
        // Serial.print("Line Following\n");
          Serial.print(r1);
          Serial.print(r2);
          analogWrite(enA, 250); 
          analogWrite(enB, 250);
          
          if ((r1 == 0)&&(r2 == 0)){
            // delay(30);
              
              digitalWrite(in1, HIGH);
              digitalWrite(in2, LOW);
              digitalWrite(in3, HIGH);
              digitalWrite(in4, LOW);

              delay(100);

              digitalWrite(in1, LOW);
              digitalWrite(in2, LOW);
              digitalWrite(in3, LOW);
              digitalWrite(in4, LOW);
              count  = 0;
              delay(10);
              
            }
          if ((r1 == 1)&&(r2 == 0)){
              // delay(30);
              digitalWrite(in1, LOW);
              digitalWrite(in2, LOW);
              digitalWrite(in3, HIGH);
              digitalWrite(in4, LOW);

              delay(100);

              digitalWrite(in1, LOW);
              digitalWrite(in2, LOW);
              digitalWrite(in3, LOW);
              digitalWrite(in4, LOW);
              count = 0;
              delay(10);
              
          }
          if ((r1 == 0)&&(r2 == 1)){
              // delay(30);
              digitalWrite(in1, HIGH);
              digitalWrite(in2, LOW);
              digitalWrite(in3, LOW);
              digitalWrite(in4, LOW);

              delay(100);

              digitalWrite(in1, LOW);
              digitalWrite(in2, LOW);
              digitalWrite(in3, LOW);
              digitalWrite(in4, LOW);
              count = 0;
              delay(10);
          }
          if ((r1 == 1)&&(r2 == 1)){
              digitalWrite(in1, LOW);
              digitalWrite(in2, LOW);
              digitalWrite(in3, LOW);
              digitalWrite(in4, LOW);
              count += 1;
              Serial.print('\n');
              Serial.print("count = ");
              Serial.print(count);
              Serial.print('\n');
              if (count >= 50){
                count = 0;
                unload_counts += 1;
                 state = 15;
              }
          }
          
          
                     
        }
        else if (state == 6){
          
          myservo1.write(180);
        }
        else if (state == 7){
        
          myservo1.write(0);
        }
        if (state == 15){
          myservo1.write(180);
          
        }
        if (state == 16){
          count2 += 1;
          if (count2 == 30){
            
            state = 0;
            count2 = 0;
          }
          digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        analogWrite(enA, 135);
        analogWrite(enB, 135);
        }
        }