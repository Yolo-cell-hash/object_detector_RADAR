// Includes the Servo library
#include <Servo.h>
#include <LiquidCrystal.h>

// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = 9;
const int echoPin = 8;
// Variables for the duration and the distance
long duration;
int distance;
Servo myServo; // Creates a servo object for controlling the servo motor
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //rs,e,d4,d5, d6, d7

int buzzer = 7;
int led = 10;

const int sensorPin = A0;
int lightCal;
int lightVal;


void setup() {
  lcd.begin(16, 2);
  pinMode(led, OUTPUT); //led
  pinMode(buzzer, OUTPUT); //Buzzer
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  myServo.attach(6); // Defines on which pin is the servo motor attached
  lightCal = analogRead(sensorPin);
}
void loop() {
  // rotates the servo motor from 15 to 165 degrees
  for(int i=15;i<=180;i++){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  
  Serial.print(i); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing

  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.println(" cm");
  lcd.setCursor(0,1);
  
  lightVal = analogRead(sensorPin);
  lcd.print("Luminosity: ");
  lcd.print(lightVal);
  //delay(200);  

  if (distance<=10) {
  digitalWrite(buzzer,HIGH);
  digitalWrite(led,HIGH);

  // lcd.clear();
  // lcd.setCursor(0,0);
  // lcd.print("Warning!!!");
  // lcd.setCursor(0,1);
  // lcd.print("Distance: ");
  // lcd.print(distance);
  // lcd.print(" cm");
  }
  else {
       digitalWrite(buzzer,LOW);
       digitalWrite(led,LOW);

       }


  }
  // Repeats the previous lines from 165 to 15 degrees
  for(int i=180;i>15;i--){  
  myServo.write(i);
  delay(20);
  distance = calculateDistance();
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");

lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.println(" cm");
  lcd.setCursor(0,1);
  
  lightVal = analogRead(sensorPin);
  lcd.print("Luminosity: ");
  lcd.print(lightVal);  


  if (distance<=10) {
  digitalWrite(buzzer,HIGH);
  digitalWrite(led,HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Warning!!!");
  lcd.setCursor(0,1);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm");
  }
  else{
  digitalWrite(buzzer,LOW);
  digitalWrite(led,LOW);
  }

  }
}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}