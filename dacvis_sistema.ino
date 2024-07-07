#include <IRremote.h> 

// Pins
const int mozraobapin = 7;    //  sensor pin
const int ledpin = 4;         // LED pin
const int piezoPin = 5;       // Piezo  pin
const int IR_PIN = 6;         // IR receiver pin

bool gangashi = false;         //gangashi


void setup() {
    pinMode(mozraobapin, INPUT);
    pinMode(ledpin, OUTPUT);
    pinMode(piezoPin, OUTPUT);
    IrReceiver.begin(IR_PIN);
  
    Serial.begin(9600);
}


void loop() {
    if (IrReceiver.decode()) {
        int command = IrReceiver.decodedIRData.command;

        if (command == 5) { // chartvis gilaki
            gangashi = true;
            Serial.println("--chairto--");
            digitalWrite(ledpin, LOW);  // gamoirtveba LED

        } else if (command == 6) { // gamortvis gilaki
            gangashi = false;
            digitalWrite(piezoPin, LOW); // piezos gamortva
            digitalWrite(ledpin, HIGH);  // chairtveba LED
            Serial.println("gangashi gamoirto, LED ainto");
        }

        IrReceiver.resume();
    }

    // shevamowmot motion sensor da tu sawiroa gangashi chavrtot
    if (gangashi) {
        bool mozraoba = digitalRead(mozraobapin);
        if (mozraoba) {
            digitalWrite(piezoPin, HIGH); // chairtveba piezo 
            Serial.println("mozraoba dafiqsirda, gangashi!");
        } else {
            digitalWrite(piezoPin, LOW); // gamoirtveba piezo
        }
    }
}
