
#ifndef _SYSCONFIG_H_
#define _SYSCONFIG_H_

#include "arduboard.h"
 
/////////////////////////////////////////////
// Bluetooth Serial

// BLE
//#define BAUD_BTSERIAL      9600    
//#define BAUD_BTSERIAL      38400

//HC-06
#define BAUD_BTSERIAL      115200

#if defined(MEGA)
 #define USE_BTSERIAL  1  // 0, 1, 2, 3
#endif

/////////////////////////////////////////////
// Debug 

#define DBG_LOG

/// Arduino UNO  ///////////////////
#if defined(UNO)
 #if defined(DBG_LOG)
 
  #define BAUD_DBG_SWSER  9600
  #define DBG_CHANNEL_SWSERIAL

  // Define: Sw Serial Pin
  #define SWSERIAL_RX  2
  #define SWSERIAL_TX  3
 #endif

/// Arduino MEGA 2560 ////////////////
#elif defined(MEGA)

 #define BAUD_DBG_SERIAL  115200
 
 #if defined(DBG_LOG)
  #if USE_BTSERIAL==0
   #define DBG_CHANNEL_SERIAL1
  #elif USE_BTSERIAL==1
   #define DBG_CHANNEL_SERIAL0
  #endif   
 #endif
#endif

#if defined(DBG_LOG)
 char* uprintf(const char* fmt, ...);
 void  DPRINTS(const char* fmt, ...);
 #define DPRINTF  uprintf
#endif

void init_debug(void);

#endif
