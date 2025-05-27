
// Interface: ARDUINO <---> JS

#include "sysconfig.h"
#include "ucrt.h"

#include "I2C.h"
#include "AndroidComm.h"


/////////////////////////////////////////////////

const int DPORTSTART  = 2;
const int DPORTEND    = 8;

int APORTSTART  = PANALOG_START;
int APORTEND    = PANALOG_END;

//////////////////////////////////////////////////

#ifdef SMARTBOARD

// SMARTBOARD
void initPorts() {
    char apin;
    for (apin = DPORTSTART; apin <= DPORTEND; apin++) {
        pinMode(apin, OUTPUT);
        digitalWrite(apin, LOW);
    }
}

#else

// UNO & MEGA2560
void initPorts()
{
    port_init_var();
    port_init_bluetooth();
}

#endif

///////////////////////////////////////////////////
// Blockly Arduino Interface

#ifdef SMARTBOARD

// SMARTBOARD ///////////////////////////////////

char  sendDigitalValues() {  
  char pinNumber;
  for (pinNumber = DPORTSTART; pinNumber <= DPORTEND; pinNumber++) {
      sendDigitalValue(pinNumber);
  }
  return pinNumber- DPORTSTART;
}

char sendAnalogValues() {
  char pinNumber;  
  for (pinNumber = APORTSTART; pinNumber <= APORTEND; pinNumber++) {
      sendAnalogValue(pinNumber);
  }
  return pinNumber-APORTSTART;
}


void setPortReadable(char port) {
    if (isPortWritable(port)) {
        pinMode(port, INPUT);
    }
}

void setPortWritable(char port) {
    if (!isPortWritable(port)) {
        pinMode(port, OUTPUT);
    }
}

bool isPortWritable(char port) {
    if (port > 7)
        return bitRead(DDRB, port - 8);
    else
        return bitRead(DDRD, port);
}

/////////////////////////////////

void sendDigitalInPort() {
    int ipin = 0;
    for (ipin = 0; ipin < SZ_DIGITAL_PORT; ipin++) {
        if (mport_digital[ipin] == TPORT_DIG_IN) {
            sendDigitalValue(ipin);
        }
    }
}

void digital_write(char port, byte mode)
{
    setPortWritable(port);
    mport_digital[port] = TPORT_DIG_OUT;

    if (mode) digitalWrite(port, HIGH);
    else  digitalWrite(port, LOW);
}


void digital_read(char port)
{
    setPortReadable(port);
    mport_digital[port] = TPORT_DIG_IN;
}


#else

// UNO & MEGA2560 /////////////////////////////

char sendDigitalValues() {
  char ipin;
  char port;

  for (ipin = 0; ipin < mszdigital_in; ipin++) {
      port = mport_digital_in[ipin];

      if (port & 0xf0)
          sendDigitalValueExtend(port);
      else
          sendDigitalValue(port);

      //sendDigitalValue(mport_digital_in[ipin]);
  }
  return ipin;
}


char sendAnalogValues() {
    char ipin = 0;
    char port;

    for (ipin = 0; ipin < mszanalog_in; ipin++) {
        port = mport_analog_in[ipin]- manalog_start_p;

        if (port & 0xf8)
            sendAnalogValueExtend(port);
        else
            sendAnalogValue(port);
    }
    return ipin;
}

/////////////////////////////////

char digital_write(char port, byte mode)
{
    char rst = port_set_digital_out(port);
    if (rst < 0)
        return -1;

    if (mode) digitalWrite(port, HIGH);
    else  digitalWrite(port, LOW);
    return 0;
}

char digital_read(char port)
{
    return port_set_digital_in(port);
}

#endif

///////////////////////////////////////////////////////

void sendDigitalValue(char apin)
{
   if (digitalRead(apin) == HIGH) {
       SerialBt.write(0x80 // B1000 0000
                 | ((apin & 0x0F)<<2) //B1111
                 | 1);
   } else {
       SerialBt.write(0x80 // B10000000
               | ((apin & 0x0F)<<2)); // B1111
   }
}

void sendDigitalValueExtend(char apin)
{
    unsigned char a, b;
    unsigned char buff[4];

    a = apin & 0x0F;
    b = apin & 0x30;

    if (digitalRead(apin) == HIGH)
        b |= 0x01;

    buff[0] = 0xff;
    buff[1] = a;
    buff[2] = b;
    SerialBt.write(buff, 3);
}


void sendAnalogValue(char apin)
{
   unsigned char a, b;
   unsigned char buff[4];

   int value = analogRead(apin);
   a = 0xC0 // B11000000
     | ((apin & 0x07)<<3) // B111
     | ((value>>7) & 0x07);  // B111
   b = value & 0x7f;   // B111 1111
   buff[0] = a;
   buff[1] = b;
   SerialBt.write(buff,2);
   DPRINTF("\tA IN: [%d]=%d\n", apin, value);
}

void sendAnalogValueExtend(char apin)
{
    unsigned char a,b,c;
    unsigned char buff[4];

    a = apin & 0x0F; a |= 0x20;

    int value = analogRead(apin);
    b = value & 0x7f;
    value >>= 3;
    c = (unsigned char)value & 0x70;

    buff[0] = 0xff;
    buff[1] = a;
    buff[2] = b;
    buff[3] = c;
    SerialBt.write(buff, 4);
    DPRINTF("\tA IN EXT:  [%d]=%d\n", apin, value);
}

void sendErrorCode(char err)
{
   unsigned char buff[4];

   buff[0] = 0xff;
   buff[1] = err;
   SerialBt.write(buff, 2);
}


/// End ///////////////////////////
