#include <MFRC522.h>
#include <SPI.h>
// Questions:
// #define vs const?
//What defines what nbaud rate is used for serial?

// define const pins. 
const  int ss = 7; // slave select pin #
const int rst = 10; //reset pin #'
const int redled = 26; //GPIO 32
const int greenled = 33;
//const int pushbt1 = ; //push button pin number
//const int pushbt2 = ;

// define non-const variables
String pswd = "";
bool authenticated[4]; //'binary' password of lenth 4
String guessed = "";

// SCK, MISO, MOSI, CS pins
const int sck = 6;
const int miso = 9;
const int mosi = 8;

// Create object instances

// RFID instance
MFRC522 rfid(ss,rst);
void clearserial()
{ // the illusion or clearing
  for (int i = 0; i < 30; i++) {
    Serial.println();
  }
}
void blinkled(int pin)
{
  for (int i = 0; i < 4 ; i++){
      digitalWrite(pin, HIGH);
      delay(200);
      digitalWrite(pin, LOW);
      delay(200);
    }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SPI.begin(sck,miso,mosi,ss); 
  rfid.PCD_Init();
  delay(200);
  rfid.PCD_DumpVersionToSerial();
  Serial.println("Hello, ESP32-S2!");
  clearserial(); // ASCII 12 is /f in prgramming languages, simulating a clearing affect
  Serial.println("Set a 4 bit binary password:  ");

  while (Serial.available()== 0){} // if nothing is entered wait here untill user enters password
  pswd = Serial.readStringUntil('\n'); // read input till new line character('Enter')
  pswd.trim();//remove newlines and spaces

  Serial.println("Encrypting password...."); // thats bs im rlly not, maybe later
  delay(2000);
  Serial.println("Password set! ");

  //ask user for password to be authenticated (first iteration)
  Serial.println("Enter binary password:");
  while (Serial.available()== 0){} // if nothing is entered wait here untill user enters password
  guessed = Serial.readStringUntil('\n');

  // LED PINMODES
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  digitalWrite(redled, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(redled,HIGH);
  clearserial();

  
  while (guessed != pswd)
  {
    blinkled(redled);
    Serial.println("Access Denied");
    Serial.println("Try Again");
    delay(2000);
    clearserial();
    Serial.println("Enter binary password:");

    while (Serial.available()== 0){} // if nothing is entered wait here untill user enters password
  
    guessed = Serial.readStringUntil('\n');
    guessed.trim();
  }
  Serial.println("Access Granted. Welcome!");
  digitalWrite(redled,LOW);
  //flash the green lef 4 times
  blinkled(greenled);
  digitalWrite(greenled,HIGH);
  pswd ="";
  delay(3000); // //time till password will be asked for again
}
