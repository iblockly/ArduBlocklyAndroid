
//  ARDUINO + Android Blockly App.
//

#include "sysconfig.h"
#include "ucrt.h"

#include "I2C.h"
#include "AndroidComm.h"


const int TM_DATA_PROC = 100;


#if defined(UNO)

 #define SerialBt Serial
  
#elif defined(MEGA)

 #if USE_BTSERIAL==0
  #define SerialBt Serial
 #else 
  #define SerialBt Serial1
 #endif

 #if defined(DBG_LOG)
  #if defined(DBG_CHANNEL_SERIAL0)
   #define DSerial Serial
  #else 
   #define DSerial Serial1
  #endif
 #endif

#endif

bool getDbgSerial(byte* cr);


// I2C Id
extern byte mi2cId;
extern byte mi2cAddr;
extern byte mi2cSeq;

// Read
extern byte mNoRdByte;

// Register Setting
extern byte mi2cRegAddr;
extern byte mi2cData;
extern uint16_t mi2cData16;


//////////////////////////////////////////////////

I2C *mpI2C = NULL;

SI2C_DEVICE *getI2C(byte id,  byte iaddr)
{
	
	SI2C_DEVICE *pdev;

	if (mpI2C == NULL) {
	    mpI2C = new I2C();
	    mpI2C->begin();
	   
	   return mpI2C->make_idevice(id, iaddr);
	}
	
	pdev = mpI2C->search_i2c(id, iaddr);
	if (pdev == NULL)
		 pdev = mpI2C->make_idevice(id, iaddr);
	
  return pdev;
}

//////////////////////////////////////////////////

unsigned long tm_curr, tm_prev;
int cntloop;

byte gsendbuff[16];

SI2C_DEVICE *mpCurrDevI2C;

//////////////////////////////////////////////////

void setup()
{
    mpI2C = NULL;
	  mpCurrDevI2C = NULL;

    SerialBt.begin(BAUD_BTSERIAL);  // Bluetooth    
    init_debug();
    initPorts();

    tm_prev = millis();
    
}

/////////////////////////////////////////////////////

char mstSendPort;

void loop()
{
   tm_curr = millis();
   if ((tm_curr - tm_prev) > TM_DATA_PROC) {
      tm_prev = tm_curr;

      //sendDigitalInPort();
      mstSendPort = sendDigitalValues();
      mstSendPort += sendAnalogValues();

   }
   
   #if defined(DBG_CHANNEL_SWSERIAL)
   byte c;
   if (getDbgSerial(&c)) {
   	  SerialBt.write(c);
   } 
   #endif
    
   //delay(TM_DATA_PROC);
}

void bl_rx_proc(byte c)
{
	 char retc = 0;

	 retc = update_port_proc(c);
	 run_rx_proc(retc);
	 
    #ifdef DBG_LOG
	 if (retc) {
		  print_blocklyread(retc);
	 }
    #endif
}


char run_rx_proc(char code)
{
	char leng;
	
	switch (code) {
		case BKLY_AINTF_I2CSETID :
			if (!mpCurrDevI2C)
			    mpCurrDevI2C = getI2C(mi2cId, mi2cAddr);

			mpCurrDevI2C->seq = mi2cSeq;
			mpCurrDevI2C->state = I2CRUN_SETID;
			
			leng = make_setid_ack(gsendbuff, mpCurrDevI2C);
			sendBlutooth(gsendbuff, leng);
			break;
			
		case BKLY_AINTF_IWRITE :
			if (! mpCurrDevI2C)
			    mpCurrDevI2C = getI2C(mi2cId, mi2cAddr);

			if (mpCurrDevI2C) {
				  mpCurrDevI2C->state = I2CRUN_SETREG;
				  mpI2C->Write(mpCurrDevI2C->iaddr, (uint8_t) mi2cData);
			}
			break;
			
		case BKLY_AINTF_ISETREG :
			if (!mpCurrDevI2C)
				mpCurrDevI2C = getI2C(mi2cId, mi2cAddr);
			if (mpCurrDevI2C) {
				mpCurrDevI2C->state = I2CRUN_SETREG;
				mpCurrDevI2C->regaddr = mi2cRegAddr;
				mpI2C->write_byte(mpCurrDevI2C->iaddr, mi2cRegAddr, mi2cData);
			}
			break;
			
		case BKLY_AINTF_IREAD :
			if (!mpCurrDevI2C) {
				mpCurrDevI2C = getI2C(mi2cId, mi2cAddr);
				DPRINTF("GetI2C: I%d A %d\n", mi2cId, mi2cAddr);
			}
			if (mpCurrDevI2C) {
				byte data;
				mpCurrDevI2C->state = I2CRUN_GETREG;
				if (mNoRdByte == 0) {
				     data = mpI2C->read(mpCurrDevI2C->iaddr);
				     mpCurrDevI2C->data = data;
				     mpCurrDevI2C->rleng = 0;
				     leng = make_i2c_read(gsendbuff, mpCurrDevI2C);
					 DPRINTF("I RD_B %d\n", data);
				} else {
				     byte dataw[2];
				     uint16_t wdata;
				     wdata = mpI2C->read_ui16(dataw, mpCurrDevI2C->iaddr);
					 mpCurrDevI2C->datah = dataw[0];
				     mpCurrDevI2C->data  = dataw[1];
				     mpCurrDevI2C->rdata = wdata;
				     mpCurrDevI2C->rleng = 1;
				     leng = make_i2c_read(gsendbuff, mpCurrDevI2C);
					 DPRINTF("I RD_H %d\n", wdata);
				}
			    sendBlutooth(gsendbuff, leng);
			}
			break;
			
		case BKLY_AINTF_IGETREG :
			if (!mpCurrDevI2C)
				mpCurrDevI2C = getI2C(mi2cId, mi2cAddr);
			if (mpCurrDevI2C) {
				byte data;
				mpCurrDevI2C->state = I2CRUN_GETREG;
				mpCurrDevI2C->regaddr = mi2cRegAddr;
				 
				if (mNoRdByte == 0) {
				    data = mpI2C->read_register(mpCurrDevI2C->iaddr, mi2cRegAddr);
				    mpCurrDevI2C->data = data;
				    mpCurrDevI2C->rleng = 0;
				    leng = make_i2c_read(gsendbuff, mpCurrDevI2C);
				} else {
				    byte dataw[2];
				    uint16_t wdata;
				    wdata = mpI2C->read_reg_ui16(dataw, mpCurrDevI2C->iaddr, mi2cRegAddr);
				    mpCurrDevI2C->datah = dataw[0];
				    mpCurrDevI2C->data  = dataw[1];
				    mpCurrDevI2C->rdata = wdata;
				    mpCurrDevI2C->rleng = 1;
				    leng = make_i2c_read(gsendbuff, mpCurrDevI2C);
				}
			    sendBlutooth(gsendbuff, leng);
			}
			break;

		case BKLY_ERROR:
			sendErrorCode(merror_c); //RFUN_PERR_PWM
			break;
	}
	return 0;
}

//////////////////////////////////////////////////////////////
// Serial 

/// Arduino UNO  ///////////////////
#ifdef UNO
void serialEvent()
#elif defined (MEGA)
 #if USE_BTSERIAL==0
void serialEvent()
 #else 
void serialEvent1()
 #endif
#endif
{
	byte c;

	while (SerialBt.available()) {
	   c = SerialBt.read();
	   //dbg_write(c);
	   bl_rx_proc(c);
	}
}

void sendBlutooth(byte *pbuff, char leng)
{
   char c;
   for (c = 0;c < leng;c++, pbuff++) {
      SerialBt.write(*pbuff);
   }
}

/// Debug ///////////////

#if defined(DBG_LOG)&&defined(MEGA)

#if defined(DBG_CHANNEL_SERIAL0)
void serialEvent()
#elif defined(DBG_CHANNEL_SERIAL1)
void serialEvent1()
#endif
{
	byte c;

	while (DSerial.available()) {
	   c = DSerial.read();
	   SerialBt.write(c);
	}
}

#endif

/// End ///////////////////////////
