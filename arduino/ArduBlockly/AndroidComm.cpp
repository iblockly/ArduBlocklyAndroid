
#include <Arduino.h>

#include "sysconfig.h"

#include "I2C.h"
#include "AndroidComm.h"


char mmode_t = MPSET_NULL;
char mmode_ext = MPSET_NULL;

byte mm_port;
byte mdout = 0;
int  mvalue;

// I2C
char mSeq = 0;

char mRxSeq = 0;
char mRxCnt;

byte mRemValue;

// I2C Id
byte mi2cId;
byte mi2cAddr;
byte mi2cSeq;

// Read
byte mNoRdByte;

// Register Setting
byte mi2cRegAddr;
byte mi2cData;
uint16_t mi2cData16;


char merror_c;


//////////////////////////////////////////

char update_port_proc(byte c)
{
    if (c & 0x80) {
        if (c & 0x40) { // 11xx: Analog 
            byte mode = c & 0x30;// 0011 0000
            if (mode == 0x00) {  // 1100: Analog Input Setting
                mmode_t = MPSET_IN_ANL;
                byte port = c & 0x0F;
                //int p = (int) port;
                //mport_analog_input[p] = TPORT_ANALG_IN;
                if (port_set_analog_in((char) port) < 0) {
                    merror_c = RFUN_PERR_ANAL;
                    return BKLY_ERROR;
                }
                mm_port = port;
                return BKLY_AINTF_INANALOG;
            
            } else if (mode == 0x20) { // 1110: Port PWM Setting
                mmode_t = MPSET_PWM;
                mm_port = c & 0x0F;    // 11 10 pppp
                mvalue = 0;
                return BKLY_AINTF_PWM_ST;
                
            } else if (mode == 0x30) {
                
                // 1111 1111 Extend
                if ((c & 0x0F) == 0x0F) {
                    mmode_t = MPSET_EXTEND;
                    mRxCnt = 3;
                    return BKLY_AINTF_NULL;;
                }

                // 1111: I2C
                byte m = (c>>1) & 0x07;
                switch (m) {
                case 0 :  // 1111 000x: i2c_setId
            	     mmode_t = MPSET_ISETID;
            	  	 mi2cSeq = c & 0x01;
            	     mRxCnt = 2;
            	  	 break;
            	  	
                case 1 :  // 1111 001v: i2c_write
            	  	 mmode_t = MPSET_IWRITE;           	  	
             	  	 mi2cData = c<<7;
            	  	 break;
            	  	 
                case 2 :  // 1111 01xx i2c_setRegister
                case 3 :
            	  	 mmode_t = MPSET_ISETREG; 	 
                     mi2cRegAddr = (c<<6)&0x80;
            	     mi2cData  = (c<<7)&0x80;
            	     mRxCnt = 2;
             	  	 break;
            	  	 
                case 4 :  // 1111 100L i2c_read
             	  	 if (c & 0x01) mNoRdByte = 1;
             	  	 else mNoRdByte = 0;
             	  	 return BKLY_AINTF_IREAD;
             	  	
                case 5 :  // 1111 101r i2c_getRegister
            	  	 mmode_t = MPSET_IGETREG;     	  	
                     mi2cRegAddr = c<<7;
             	  	 mNoRdByte = 0;
             	  	 break;

                case 6:  // 1111 110r i2c_getRegister
                   mmode_t = MPSET_IGETREGL;
                   mi2cRegAddr = c << 7;
                   mNoRdByte = 1;
                   break;
                }
            }
        } else { // 10xx
            byte port = (c >> 2) & 0x0F;
            mm_port = port;
            if (c & 0x02) { // 101x: MPSET_DIG_WR - Digital Output Setting
                mmode_t = MPSET_DIG_WR;
                mdout = c & 0x01;
                mm_port = port;

                //digital_write(port, mdout);
                if (digital_write(port, mdout) < 0) {
                    merror_c = RFUN_PERR_DPORT;
                    return BKLY_ERROR;
                }
                return BKLY_AINTF_DIGOUT;
            } else {   // 100x
                mmode_t = MPSET_DIG_RD;
                mm_port = port;

                //digital_read(port);
                if (digital_read(port) < 0) {
                    merror_c = RFUN_PERR_DPORT;
                    return BKLY_ERROR;
                }
                
                return BKLY_AINTF_DIGIN;
            }
        }
    } else { // 0xxx
        switch (mmode_t) {
        case MPSET_PWM:
            {
             byte mode = c & 0xC0;  // 1100 0000
             if (mode == 0x40) {    // 01xx: Second
                 mm_port |= c & 0x30;
                 c &= 0x0F;
                 mvalue = c<<6;
                 return BKLY_AINTF_PWM_ST;

             } else if (mode == 0x00) { // 00xx:  3th
                mvalue |= (int)(c & 0x3F);
                if (mvalue > PWM_VMASK)
                    mvalue = PWM_VMASK;
                
                if (port_set_PWM(mm_port) < 0) {
                    merror_c = RFUN_PERR_PWM;
                    return BKLY_ERROR;
                }
                analogWrite(mm_port, mvalue);
                DPRINTF("PWM WR [%d] %d\n", mm_port, mvalue);
                return BKLY_AINTF_PWM;
             }
            }
            break;
 
        case MPSET_ISETID :        	
            if (mRxCnt == 2) {
        	  	mi2cSeq |= (c>>4) & 0x06;
            	mi2cId = c&0x1f;
            	mRxCnt--;
            } else {    
            	mi2cAddr = c;
                DPRINTF("$ %d\n", mi2cAddr);
                port_set_i2c();
            	return BKLY_AINTF_I2CSETID;
            }
            break;
            
        case MPSET_IWRITE :
        	mi2cData |= c;
        	return BKLY_AINTF_IWRITE;      
        	               	  
        case MPSET_ISETREG :        	
            if (mRxCnt == 2) {
            	mi2cRegAddr |= c;
            	mRxCnt--;
            } else {    
            	mi2cData |= c;
            	return BKLY_AINTF_ISETREG;
            }
            break;
   	          
        //case MPSET_IREAD : break;
        case MPSET_IGETREG :
        case MPSET_IGETREGL :
            mi2cRegAddr |= c&0x7f;
            return BKLY_AINTF_IGETREG;

        case MPSET_EXTEND:
            if (mRxCnt == 3) {
                mRxCnt--;
                if (!(c & 0x60)) { // Digital Extend
                    mm_port = c & 0x0F;
                    if (c & 0x10) { // Set Digital
                        mmode_ext = BKLY_AINTF_DIGOUT;
                    } else {        // Get Digital
                        mmode_ext = BKLY_AINTF_DIGIN;
                    }
                }
            } else { // Last
                if (mmode_ext == BKLY_AINTF_DIGOUT) {
                    if (c & 0x08) mdout = 1;
                    else mdout = 0;
                    
                    mm_port |= c & 0x30;
                    if (digital_write(mm_port, mdout) < 0) {
                        merror_c = RFUN_PERR_DPORT;
                        return BKLY_ERROR;
                    }
                    return BKLY_AINTF_DIGOUT;
                } else if (mmode_ext == BKLY_AINTF_DIGIN) {
                    mm_port |= c & 0x30;

                    if (digital_read(mm_port) < 0) {
                        merror_c = RFUN_PERR_DPORT;
                        return BKLY_ERROR;
                    }
                    return BKLY_AINTF_DIGIN;
                }
            }
            break;

        default:
            return BKLY_AINTF_UNKNOWN;
        }
    }
    return BKLY_AINTF_NULL;
}



char make_setid_ack(byte *pdata, SI2C_DEVICE *pdev)
{
    byte dseq = pdev->seq;
    byte did  = pdev->id;
	  
    byte s, i;
    	 
    s  = ((dseq)&0x01) | 0xFC; // mi2cSeq
    i  = (dseq<<4) & 0x60;
    i |= did;
   
    *pdata++ = s;
    *pdata   = i;

    return 2;
}

char make_i2c_read(byte *pdata, SI2C_DEVICE *pdev)
{
    byte id = pdev->id;
	  
    byte i;
    	 
    if (pdev->rleng) { // 16 bits
    	
       byte data  = pdev->data;
       byte datah = pdev->datah;

       i =  id & 0x1F;
       if (data & 0x80)
    	    i |= 0x40;
       if (datah & 0x80)
    	    i |= 0x20;
    	           
       *pdata++ = 0xF9;
       *pdata++ = data & 0x7F;
       *pdata++ = i;
       *pdata   = datah & 0x7F;
       return 4;
       
    } else {           // 8 bits
       byte data = pdev->data;
       i =  id & 0x1F;
       if (data & 0x80)
    	    i |= 0x40;
   
       *pdata++ = 0xF8;
       *pdata++ = data & 0x7F;
       *pdata   = i;
    }
    return 3;
}

///////////////////////////////////////////////
// Debug

#ifdef DBG_LOG

void print_blocklyread(char retc)
{
    char port  = mm_port;
    char dout  = mdout;
    int  value = mvalue;

    switch (retc) {
    case BKLY_AINTF_DIGIN:
        //DPRINTS("D IN %d\n", port);
        break;

    case BKLY_AINTF_DIGOUT:
        //DPRINTS("D OUT %d\n", port);
        break;

    case BKLY_AINTF_INANALOG:
        //DPRINTS("A In [%d]\n", port);
        break;

    case BKLY_AINTF_PWM_ST:
        break;

    case BKLY_AINTF_PWM:
        //DPRINTS("PWM [%d]=%d\n", port, value);
        break;

    case BKLY_AINTF_PREAD:
        DPRINTS("A RD: %d\n", port);
        break;
        
    case BKLY_AINTF_ANSET:
        DPRINTS("A SET [%d]:%d\n", port, value);
        break;

    case BKLY_AINTF_I2CSETID:
        DPRINTS("I SETID [%d]:%d\n", mi2cId, mi2cAddr);
        break;
    	
    case BKLY_AINTF_IWRITE :
        DPRINTS("I WR %d\n", mi2cData);
        break;
    	
    case BKLY_AINTF_ISETREG :
        DPRINTS("I SREG [%d]:%d\n", mi2cRegAddr, mi2cData);
        break;
    	
    case BKLY_AINTF_IREAD :
        //DPRINTS("I RD %d\n", mNoRdByte);
        break;
    	
    case BKLY_AINTF_IGETREG :
        DPRINTS("I GET [%d] %d\n", mi2cRegAddr, mNoRdByte);
        break;
    	
    default:
        //DPRINTS("DEF %x P[%d]:%x\n", retc, port, value);
        break;
    }
    
}

#endif

/// End ///////////////////////////
