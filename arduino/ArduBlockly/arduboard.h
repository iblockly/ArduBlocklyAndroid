#ifndef _ARDUBOARD_H_
#define _ARDUBOARD_H_

#include <Arduino.h>

//#define SMARTBOARD

#if defined (__AVR_ATmega328__)
 #define UNO
#elif defined (__AVR_ATmega328P__) 
 #define UNO
#elif defined (__AVR_ATmega2560__)
 #define MEGA
#endif

////////////////////////////////////////////

#if defined(UNO)

 #define SZ_ARDUINO_PORT 20
 #define SZ_DIGITAL_PORT SZ_ARDUINO_PORT
 #define SZ_ANALOG_IN    6
 #define SZ_PWM_PORT     6

 #define PANALOG_START   0
 #define PANALOG_END     5

 #define PWM_VMASK  255

#elif defined(MEGA)

 #define SZ_ARDUINO_PORT 70

 #define SZ_DIGITAL_PORT SZ_ARDUINO_PORT
 #define SZ_ANALOG_IN    16
 #define SZ_PWM_PORT     12

 #define PANALOG_START   0
 #define PANALOG_END     15

 #define  PWM_VMASK  255

#endif

///////////////////////////////////////

#define TPORT_NULL      0x00

#define TPORT_DDIR_MASK 0x01

#define TPORT_DIG_IN    0x02
#define TPORT_DIG_OUT   0x03

#define TPORT_DIGITAL   0x02
#define TPORT_ANALG_IN  0x04
#define TPORT_PWM       0x08
#define TPORT_I2C       0x10
#define TPORT_SPI       0x20
#define TPORT_SERIAL    0x40


struct _ArdPort {
	char dnum;
	char fun;
};
typedef struct _ArdPort ArPort;

struct _PortMap {
	char dnum;
	char set;
	char fun;
};
typedef struct _PortMap PortMap;

#define PORTF_NULL      0x00

#define PORTF_DDIR_MASK 0x01
#define PORTF_DIG_IN    0x02
#define PORTF_DIG_OUT   0x03

#define PORTF_ANALG_IN  0x04
#define PORTF_PWM       0x08

#define PORTF_SPEC_MASK 0xF0
#define PORTF_I2C       0x10
#define PORTF_SPI       0x20
#define PORTF_BT        0x80

/////////////////////////////////////////

extern char mport_digital_in[];
extern char mszdigital_in;

extern const char manalog_start_p;
extern const char manalog_end_p;

extern char mport_analog_in[];
extern char mszanalog_in;

//////////////////////////////////////////

void port_init_var();
void port_init_bluetooth();
void make_digital_in_list();
char port_set_digital_in(char p);
char port_set_digital_out(char p);
void make_analog_in_list();
char port_set_analog_in(char p);
void make_pwm_list();

char port_set_PWM(char p);
void port_set_i2c();

char port_delete_list(char cst, char p);


#endif
