#ifndef _ANDROIDCOMM_H_
#define _ANDROIDCOMM_H_


/////////////////////////////////////////////

#define BKLY_AINTF_UNKNOWN  -1
#define BKLY_AINTF_NULL     0
#define BKLY_AINTF_DIGOUT   1
#define BKLY_AINTF_DIGIN    2

#define BKLY_AINTF_INANALOG 3
#define BKLY_AINTF_PWM_ST   4
#define BKLY_AINTF_PWM      5

#define BKLY_AINTF_REMNEXT  11
#define BKLY_AINTF_PREAD    12
#define BKLY_AINTF_ANSET    13

#define BKLY_AINTF_I2CSETID  0x10
#define BKLY_AINTF_IWRITE   0x11
#define BKLY_AINTF_ISETREG  0x12
#define BKLY_AINTF_IREAD    0x13
#define BKLY_AINTF_IGETREG  0x14

#define BKLY_SEPEC_FUN      0xF0

#define BKLY_ERROR          -1

//////////////////////////////////////

#define MPSET_NULL     0
#define MPSET_DIG_RD   1
#define MPSET_DIG_WR   2
#define MPSET_IN_ANL   3
#define MPSET_PWM      4
#define MPSET_PWM_CONT 5
#define MPSET_ISETID   6
#define MPSET_IWRITE   7
#define MPSET_ISETREG  8
#define MPSET_IREAD    9
#define MPSET_IGETREG  10
#define MPSET_IGETREGL 11

#define MPSET_EXTEND   12

/// Error Code

#define RFUN_PERR_NULL     0x00
#define RFUN_PERR_DPORT    0x61 // 011 000 01
#define RFUN_PERR_ANAL     0x65 // 011 001 01
#define RFUN_PERR_PWM      0x69 // 011 010 01

//////////////////////////////////

extern char merror_c;

//////////////////////////////////

void initPorts();


char digital_write(char port, byte mode);
char digital_read(char port);


void sendDigitalInPort();
void sendAnalogValue(char pinNumber);

void setPortReadable(char port);
void setPortWritable(char port);
bool isPortWritable(char port);

void sendBlutooth(byte*pbuff, char leng);

void sendDigitalValue(char apin);
void sendDigitalValueExtend(char apin);
void sendAnalogValue(char apin);
void sendAnalogValueExtend(char apin);

void sendErrorCode(char err);

// Command Data Processor

void print_blocklyread(char retc);
char update_port_proc(byte c);

char make_setid_ack(byte* pdata, SI2C_DEVICE* pdev);
char make_i2c_read(byte* pdata, SI2C_DEVICE* pdev);

#endif
