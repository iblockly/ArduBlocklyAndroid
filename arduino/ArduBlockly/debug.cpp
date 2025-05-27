
#include <Arduino.h>

#include "sysconfig.h"
#include "ucrt.h"

char gstrbuff[128];

#if defined(DBG_CHANNEL_SWSERIAL)

 #include <SoftwareSerial.h>
 SoftwareSerial DbgSerial(SWSERIAL_RX,SWSERIAL_TX);

 void dbg_print(char *pstr) { DbgSerial.print(pstr); }
 void dbg_write(byte c) { DbgSerial.write(c); }

 bool getDbgSerial(byte* cr)
 {
     byte c;
     if (DbgSerial.available()) {
         c = DbgSerial.read();
         //SerialBt.write(c);
         *cr = c;
         return true;
     }
     return false;
 }

#elif defined(DBG_CHANNEL_SERIAL0)

 void dbg_print(char* pstr) { Serial.print(pstr); }
 void dbg_write(byte c) { Serial.write(c); }

#elif defined(DBG_CHANNEL_SERIAL1)

 void dbg_print(char* pstr) { Serial1.print(pstr); }
 void dbg_write(byte c) { Serial1.write(c); }

#else
 void dbg_print(char* pstr) { }
 void dbg_write(byte c) { }
#endif

///////////////////////////////////////////////////////
// Debug

//#define DBG_CHANNEL_SERIAL0

void init_debug(void)
{
  #if defined(DBG_CHANNEL_SWSERIAL)
   DbgSerial.begin(BAUD_DBG_SWSER);	
   DbgSerial.print("Blockly+Arduino [SW]...\r\n");
  #elif defined(DBG_CHANNEL_SERIAL0)
   Serial.begin(BAUD_DBG_SERIAL);	
   Serial.print("Blockly+Arduino [0]...\r\n");
  #elif defined(DBG_CHANNEL_SERIAL1)
   Serial1.begin(BAUD_DBG_SERIAL);	
   Serial1.print("Blockly+Arduino [1]...\r\n");
  #endif
}


#if defined(DBG_LOG)

unsigned char mseqprt = 0;
extern unsigned long tm_curr;

void DPRINTS(const char *fmt, ...)
{
    va_list vlist;

    sprintf(gstrbuff, "%02d:%u ", mseqprt%100, (unsigned long) tm_curr);
    mseqprt++;

  	char *pstr = string_end(gstrbuff);
		
    va_start(vlist, fmt);
    vsprintf(pstr, fmt, vlist);
    va_end(vlist);

    dbg_print(gstrbuff);
}

char* uprintf(const char* fmt, ...)
{
    va_list vlist;

    va_start(vlist, fmt);
    vsprintf(gstrbuff, fmt, vlist);
    va_end(vlist);

    dbg_print(gstrbuff);
    return gstrbuff;
}

#endif

/// End ///////////////////////////////////////
