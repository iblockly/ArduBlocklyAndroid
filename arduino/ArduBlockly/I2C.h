
#ifndef _I2C_H_
#define _I2C_H_

#include "Wire.h"

/////////////////////////////////////////////////

#define I2CRUN_NULL     0
#define I2CRUN_SETID    1
#define I2CRUN_SETREG   2
#define I2CRUN_GETREG   3

struct _SI2C_DEVICE  {
    _SI2C_DEVICE *next;
    _SI2C_DEVICE *prev;
	 	 
    byte  id;
    byte  iaddr;
    byte  seq;
    byte  state; 
	 
    // The sensor's I2C address, either 0x23 or 0x5C
    uint8_t  regaddr;
      
    uint8_t  data;
    uint8_t  datah;
   
    uint16_t rdata;
   
    byte     rleng;

};

typedef struct _SI2C_DEVICE SI2C_DEVICE;

////////////////////////////////////////////////

class I2C {

public:

   // Class constructor
    I2C() {
        mpDevice = NULL;
        mpDeviceTail = NULL;
        i2c_err_ = 0;
    }


   byte i2c_err_;
   
   byte mdata;
   byte mdatah;
   
   // Set the I2C address, turn on the sensor, set the mode
   //void Begin(uint8_t Addr = Addr_LOW, uint8_t Mode = Continuous_H);

   static void begin()
   {
   	  Wire.begin(); // Start the I2C bus
   }
   
   SI2C_DEVICE *make_idevice(byte id,  byte ia)
   {
   	  SI2C_DEVICE *pdev;
   	  
   	  pdev = new SI2C_DEVICE;
   	  pdev->next = NULL;
   	  pdev->prev = NULL;
   	  	  
   	  pdev->id = id;
   	  pdev->iaddr = ia;
      pdev->seq = 0;
			pdev->state = 0;
			
   	  if (mpDevice) {
   	  	  pdev->prev = mpDeviceTail;
   	      mpDeviceTail->next = pdev;   	  	
    	} else {  	  	
   	  	  mpDevice = pdev;
   	  }
   	  mpDeviceTail = pdev;
      return pdev; 
   }
   
   SI2C_DEVICE *search_i2c(byte id,  byte iaddr)
   {
   	  SI2C_DEVICE *pdev = mpDevice;
   	  
   	  while(pdev) {
   	  	if (pdev->id == id && pdev->iaddr == iaddr)
   	  		return pdev;
   	  		
   	  	pdev = pdev->next;	
   	  }
   	  return NULL;
   }
   
  
   // Write a byte
   void Write(uint8_t address, uint8_t Opcode) {
      Wire.beginTransmission(address);
      Wire.write(Opcode);
      Wire.endTransmission();
   }
   
   void Write(uint8_t address, uint16_t wd) {

      uint8_t highbyte = wd>>8;
      uint8_t lowbyte = (uint8_t) wd;

      // Send the two bytes
      Wire.beginTransmission(address);
      Wire.write(highbyte);
      Wire.write(lowbyte);
      Wire.endTransmission();
   }
  
   byte write_byte(uint8_t address, uint8_t subAddress, uint8_t data) {
   	  byte i2c_err;
   	
      Wire.beginTransmission(address);    // Initialize the Tx buffer
      Wire.write(subAddress);             // Put slave register address in Tx buffer
      Wire.write(data);                   // Put data in Tx buffer
      i2c_err = Wire.endTransmission();  // Send the Tx buffer
      //if (i2c_err_) print_i2c_error();
      return i2c_err;
   }
    
   /*
   void setRegister(byte raddr, byte dt)
   {
      uint8_t highbyte = wd>>8;
      uint8_t lowbyte = (uint8_t) wd;

      // Send the two bytes
      Wire.beginTransmission(Address);
      Wire.write(raddr);
      Wire.write(dt);
      Wire.endTransmission();
   }
   */

   uint8_t read_register(uint8_t address, uint8_t subAddress)
   {
      uint8_t data = 0;                        // `data` will store the register data
      Wire.beginTransmission(address);        // Initialize the Tx buffer
      Wire.write(subAddress);                 // Put slave register address in Tx buffer
      i2c_err_ = Wire.endTransmission(false); // Send the Tx buffer, but send a restart to keep connection alive
      if (i2c_err_) //print_i2c_error();
      	 return 0; 
      Wire.requestFrom(address, (size_t)1);  // Read one byte from slave register address
      if (Wire.available()) 
      	 data = Wire.read();    // Fill Rx buffer with result
      Wire.endTransmission();    // Return data read from slave register
      return data;
   }
   
   uint16_t read_reg_ui16(byte *pdata, uint8_t address, uint8_t subAddress)
   {
      uint16_t wdata;
      uint8_t data = 0;                        // `data` will store the register data
      Wire.beginTransmission(address);        // Initialize the Tx buffer
      Wire.write(subAddress);                 // Put slave register address in Tx buffer
      i2c_err_ = Wire.endTransmission(false); // Send the Tx buffer, but send a restart to keep connection alive
      if (i2c_err_) //print_i2c_error();
      	 return 0; 
      Wire.requestFrom(address, (size_t)2);  // Read one byte from slave register address
      //if (Wire.available()) 
      data = Wire.read();    // Fill Rx buffer with result
      *pdata++ = data;
      mdata = data;
      wdata = (uint16_t) data; 
      wdata <<= 8;
        	 
      //if (Wire.available()) 
      data = Wire.read();    // Fill Rx buffer with result
      *pdata = data;
      mdatah = data;
      wdata |= (uint16_t)data & 0x00FF;
      
      i2c_err_ = Wire.endTransmission();    // Return data read from slave register
      return wdata;
   }
   
   uint8_t read(uint8_t address)
   {
      uint8_t data;
    
      // Ask the sensor for two bytes
      Wire.beginTransmission(address);
      Wire.requestFrom((int)address, 1);
      data = Wire.read();
      i2c_err_ = Wire.endTransmission();
      
      mdata = data;
      return data;
   }
   
   uint16_t read_ui16(byte *pdata, uint8_t address) {
      byte data;
      uint16_t wdata;
    
      // Ask the sensor for two bytes
      Wire.beginTransmission(address);
      Wire.requestFrom((int)address, 2);

      // Read the two bytes and OR them together for a 16 bit number
      data = Wire.read();
      *pdata++ = data;
      mdata = data;
      wdata = (uint16_t) data; 
      wdata <<= 8;
      
      data = Wire.read();
      *pdata = data;
      mdatah = data;
      wdata |= (uint16_t)data & 0x00FF;
      
      // End the transmission
      i2c_err_ = Wire.endTransmission();

      return wdata;   
   }
   

private:

   SI2C_DEVICE *mpDevice;
   SI2C_DEVICE *mpDeviceTail;

};

#endif

/// End ///////////////////////////
