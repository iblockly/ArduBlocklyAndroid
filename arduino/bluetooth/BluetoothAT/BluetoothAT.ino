/*
 * Bluetooth Setting
 *  Aruino UNO & MEGA 2560
 *
 */

#if defined (__AVR_ATmega328__)
 #define UNO
#elif defined (__AVR_ATmega328P__) 
 #define UNO
#elif defined (__AVR_ATmega2560__)
 #define MEGA
#endif

#if defined(UNO)
 #include <SoftwareSerial.h>
 SoftwareSerial SerialBt(2,3); // rxPin, txPin
#elif defined (MEGA)
 #define SerialBt  Serial1
#endif


#define BAUD_BT  9600
//#define BAUD_BT  38400
//#define BAUD_BT  115200


void setup() {
  Serial.begin(115200);
  SerialBt.begin(BAUD_BT);	// HC-06 module: Default 9600 baud

  while (Serial.available() > 0) {
    Serial.read();
  }
  Serial.println("Bluetooth Setting: AT-Command...");
}

void loop() {

  while (Serial.available()) {
    byte b = Serial.read();
    if (b == '\n') continue;  // Discard Line Feeds
    if (b != '\r') {
      SerialBt.write(b);
    } else {
      SerialBt.write("\r\n");
    }
  }

  while (SerialBt.available()) {
    Serial.write(SerialBt.read());
  }
}
