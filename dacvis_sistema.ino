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
        int command = IrReceiver.decodedIRData.command;  // პულტის ღილაკები

        if (command == 5) { // მოწმნდება დაეჭირა თუ არა ჩართვის ღილაკს
            gangashi = true;
            Serial.println("--chairto--");
            digitalWrite(ledpin, LOW);  //გამოირთვება ლედი თუ ჩავრთავთ მოწყობილობას

        } else if (command == 6) { //  მოწმნდება დაეჭირა თუ არა გამორთვის ღილაკს
            gangashi = false;
            digitalWrite(piezoPin, LOW); // თუ გამოირთო პიეზო გამოირთვება
            digitalWrite(ledpin, HIGH);  // თუ გამოირთო ლედი აინთება
            Serial.println("gangashi gamoirto, LED ainto");
        }

        IrReceiver.resume();
    }

    // თუ მოწყობილობა ჩართულია:
    if (gangashi) {
      //შევამოწმოთ motion sensor-იდან შემოსული ინმორმაცია
        bool mozraoba = digitalRead(mozraobapin);
      //სენსორმა თუ დააფიქსირა რამე:
        if (mozraoba) {
            digitalWrite(piezoPin, HIGH); // ჩაირთვება piezo 
            Serial.println("mozraoba dafiqsirda, gangashi!");
        } else {
            digitalWrite(piezoPin, LOW); // თუარადა გამორთული დარჩება
        }
    }
}
