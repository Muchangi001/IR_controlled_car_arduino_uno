#include <IRremote.hpp>

const int IR_RECEIVE_PIN = 2;

#define ENA_L 5
#define ENB_R 6
#define INA_L1 7
#define INA_L2 8
#define INB_R1 11
#define INB_R2 12

void moveFoward();
void turnLeft();
void turnRight();
void stop();
void reverse();

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start IR receiver

  pinMode(ENA_L, OUTPUT);
  pinMode(INA_L1, OUTPUT);
  pinMode(INA_L2, OUTPUT);
  pinMode(ENB_R, OUTPUT);
  pinMode(INB_R1, OUTPUT);
  pinMode(INB_R2, OUTPUT);
}

void loop() {
  if (IrReceiver.decode()) 
  {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.printIRResultShort(&Serial);

    switch(IrReceiver.decodedIRData.decodedRawData)
    {
            case 0xA6595FA0: 
                moveFoward();
                break;
            case 0xAE515FA0: 
                reverse();
                break;
            case 0xA9565FA0: 
                turnLeft();
                break;
            case 0xEB145FA0: 
                turnRight();
                break;
            case 0xAA555FA0:
                 stop();
                 break;
            default:
                // Handle unknown codes if needed
                break;
    }

    IrReceiver.resume(); // Enable receiving of the next value
  }
}

void moveFoward() {
  analogWrite(ENA_L, 255);
  analogWrite(ENB_R, 255);
  digitalWrite(INA_L1, HIGH);
  digitalWrite(INA_L2, LOW);
  digitalWrite(INB_R1, HIGH);
  digitalWrite(INB_R2, LOW);
}

void turnLeft() {
  analogWrite(ENA_L, 0);
  analogWrite(ENB_R, 255);
  digitalWrite(INA_L1, LOW);
  digitalWrite(INA_L2, LOW);
  digitalWrite(INB_R1, HIGH);
  digitalWrite(INB_R2, LOW);
}

void turnRight() {
  analogWrite(ENA_L, 255);
  analogWrite(ENB_R, 0);
  digitalWrite(INA_L1, HIGH);
  digitalWrite(INA_L2, LOW);
  digitalWrite(INB_R1, LOW);
  digitalWrite(INB_R2, LOW);
}

void stop() {
  analogWrite(ENA_L, 0);
  analogWrite(ENB_R, 0);
  digitalWrite(INA_L1, LOW);
  digitalWrite(INA_L2, LOW);
  digitalWrite(INB_R1, LOW);
  digitalWrite(INB_R2, LOW);
}

void reverse(){
  analogWrite(ENA_L, 255);
  analogWrite(ENB_R, 255);
  digitalWrite(INA_L1, LOW);
  digitalWrite(INA_L2, HIGH);
  digitalWrite(INB_R1, LOW);
  digitalWrite(INB_R2, HIGH);
}
