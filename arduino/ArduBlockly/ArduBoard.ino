

#include "arduboard.h"
#include "sysconfig.h"


#if defined(UNO)

//const char mszPin = 20; // 54 + 16

ArPort mArdPort[] = {
  
  {  0, TPORT_DIGITAL | TPORT_SERIAL },
  {  1, TPORT_DIGITAL | TPORT_SERIAL },

  {  2, TPORT_DIGITAL },
  {  3, TPORT_DIGITAL | TPORT_PWM },
  {  4, TPORT_DIGITAL },
  {  5, TPORT_DIGITAL | TPORT_PWM },
  {  6, TPORT_DIGITAL | TPORT_PWM },
  {  7, TPORT_DIGITAL },
  {  8, TPORT_DIGITAL },
  {  9, TPORT_DIGITAL | TPORT_PWM },
  { 10, TPORT_DIGITAL | TPORT_PWM },
  { 11, TPORT_DIGITAL | TPORT_PWM | TPORT_SPI },
  { 12, TPORT_DIGITAL | TPORT_SPI },
  { 13, TPORT_DIGITAL | TPORT_SPI },

  { 14, TPORT_DIGITAL | TPORT_ANALG_IN },
  { 15, TPORT_DIGITAL | TPORT_ANALG_IN },
  { 16, TPORT_DIGITAL | TPORT_ANALG_IN },
  { 17, TPORT_DIGITAL | TPORT_ANALG_IN },
  { 18, TPORT_DIGITAL | TPORT_ANALG_IN | TPORT_I2C},
  { 19, TPORT_DIGITAL | TPORT_ANALG_IN | TPORT_I2C},

  { -1, 0 } // END
};

const char manalog_start_p = 14;
const char manalog_end_p = manalog_start_p+6;

char mport_i2c[2] = { 18, 19 };
char mport_spi[4] = { 10, 11, 12, 13 };

const char mport_ser_a = 0;
const char mport_ser_b = 1;


const char cport_pwm[6] = { 3, 5,6, 9,10,11 };
const char cport_leng = sizeof(cport_pwm);

#elif defined (MEGA) 

//const char mszPin = SZ_DIGITAL_PORT; // 54 + 16

const ArPort mArdPort[] = {
  {  0, TPORT_DIGITAL | TPORT_SERIAL }, // Serial 0
  {  1, TPORT_DIGITAL | TPORT_SERIAL },

  {  2, TPORT_DIGITAL | TPORT_PWM },
  {  3, TPORT_DIGITAL | TPORT_PWM },
  {  4, TPORT_DIGITAL | TPORT_PWM },
  {  5, TPORT_DIGITAL | TPORT_PWM },
  {  6, TPORT_DIGITAL | TPORT_PWM },
  {  7, TPORT_DIGITAL | TPORT_PWM },
  {  8, TPORT_DIGITAL | TPORT_PWM },
  {  9, TPORT_DIGITAL | TPORT_PWM },
  { 10, TPORT_DIGITAL | TPORT_PWM },
  { 11, TPORT_DIGITAL | TPORT_PWM },
  { 12, TPORT_DIGITAL | TPORT_PWM },
  { 13, TPORT_DIGITAL | TPORT_PWM },

  { 14, TPORT_DIGITAL | TPORT_SERIAL }, // Serial 3
  { 15, TPORT_DIGITAL | TPORT_SERIAL },
  { 16, TPORT_DIGITAL | TPORT_SERIAL }, // Serial 2
  { 17, TPORT_DIGITAL | TPORT_SERIAL },
  { 18, TPORT_DIGITAL | TPORT_SERIAL }, // Serial 1
  { 19, TPORT_DIGITAL | TPORT_SERIAL },

  { 20, TPORT_DIGITAL | TPORT_I2C },
  { 21, TPORT_DIGITAL | TPORT_I2C },

  { 22, TPORT_DIGITAL },
  { 23, TPORT_DIGITAL },
  { 24, TPORT_DIGITAL },
  { 25, TPORT_DIGITAL },
  { 26, TPORT_DIGITAL },
  { 27, TPORT_DIGITAL },
  { 28, TPORT_DIGITAL },
  { 29, TPORT_DIGITAL },
  { 30, TPORT_DIGITAL },
  { 31, TPORT_DIGITAL },
  { 32, TPORT_DIGITAL },
  { 33, TPORT_DIGITAL },
  { 34, TPORT_DIGITAL },
  { 35, TPORT_DIGITAL },
  { 36, TPORT_DIGITAL },
  { 37, TPORT_DIGITAL },
  { 38, TPORT_DIGITAL },
  { 39, TPORT_DIGITAL },
  { 40, TPORT_DIGITAL },
  { 41, TPORT_DIGITAL },
  { 42, TPORT_DIGITAL },
  { 43, TPORT_DIGITAL },
  { 44, TPORT_DIGITAL },
  { 45, TPORT_DIGITAL },
  { 46, TPORT_DIGITAL },
  { 47, TPORT_DIGITAL },
  { 48, TPORT_DIGITAL },
  { 49, TPORT_DIGITAL },

  { 50, TPORT_DIGITAL | TPORT_SPI },
  { 51, TPORT_DIGITAL | TPORT_SPI },
  { 52, TPORT_DIGITAL | TPORT_SPI },
  { 53, TPORT_DIGITAL | TPORT_SPI },

  { 54, TPORT_DIGITAL | TPORT_ANALG_IN }, // A0
  { 55, TPORT_DIGITAL | TPORT_ANALG_IN }, // A1
  { 56, TPORT_DIGITAL | TPORT_ANALG_IN }, // A2
  { 57, TPORT_DIGITAL | TPORT_ANALG_IN }, // A3
  { 58, TPORT_DIGITAL | TPORT_ANALG_IN }, // A4
  { 59, TPORT_DIGITAL | TPORT_ANALG_IN }, // A5
  { 60, TPORT_DIGITAL | TPORT_ANALG_IN }, // A6
  { 61, TPORT_DIGITAL | TPORT_ANALG_IN }, // A7
  { 62, TPORT_DIGITAL | TPORT_ANALG_IN }, // A8
  { 63, TPORT_DIGITAL | TPORT_ANALG_IN }, // A9
  { 64, TPORT_DIGITAL | TPORT_ANALG_IN }, // A10
  { 65, TPORT_DIGITAL | TPORT_ANALG_IN }, // A11
  { 66, TPORT_DIGITAL | TPORT_ANALG_IN }, // A12
  { 67, TPORT_DIGITAL | TPORT_ANALG_IN }, // A13
  { 68, TPORT_DIGITAL | TPORT_ANALG_IN }, // A14
  { 69, TPORT_DIGITAL | TPORT_ANALG_IN }, // A15

  { -1, 0 } // END
};

const char manalog_start_p = 54;
const char manalog_end_p   = manalog_start_p+16;

const char mport_i2c[2] = { 20, 21 };
const char mport_spi[4] = { 50, 51, 52, 53 };

#if   USE_BTSERIAL==1
const char mport_ser_a  =  18;
const char mport_ser_b  =  19;
#elif USE_BTSERIAL==2
const char mport_ser_a  =  16;
const char mport_ser_b  =  17;
#elif USE_BTSERIAL==3
const char mport_ser_a  =  14;
const char mport_ser_b  =  15;
#endif

const char mpwm_start_p = 2;
const char mpwm_end_p   = 13;

#endif

char mport_digital_in[SZ_DIGITAL_PORT];
char mszdigital_in;

char mport_analog_in[SZ_ANALOG_IN];
char mszanalog_in;

char mport_pwm[SZ_PWM_PORT];
char mszpwm;

PortMap mport_funct[SZ_ARDUINO_PORT];


//////////////////////////////////////////////

void port_init_var()
{ 
    int c;
    const ArPort*  pportard = mArdPort;
    PortMap* pportset = mport_funct;

    for (c = 0; c < SZ_ARDUINO_PORT; c++, pportard++, pportset++) {
        pportset->dnum = pportard->dnum;
        pportset->fun = pportard->fun;
        pportset->set = PORTF_NULL;
    }
}

// UNO
//  { 0, TPORT_DIGITAL | TPORT_SERIAL },
//  { 1, TPORT_DIGITAL | TPORT_SERIAL },
// MEGA
//  { 18, TPORT_DIGITAL | TPORT_SERIAL },
//  { 19, TPORT_DIGITAL | TPORT_SERIAL },
//
void port_init_bluetooth()
{
    mport_funct[mport_ser_a].set = (char) PORTF_BT;
    mport_funct[mport_ser_b].set = (char) PORTF_BT;
}

////////////////////////////////////////////////////////////

// Digital Read

void make_digital_in_list()
{
    char c;
    PortMap* pportset = mport_funct;
    char l;

    l = 0;
    for (c = 0; c < SZ_ARDUINO_PORT; c++, pportset++) {
        if (pportset->set == PORTF_DIG_IN) {
            mport_digital_in[l] = pportset->dnum;
            l++;
        }
    }
    mszdigital_in = l;
}

void delete_digital_in_list(char p)
{
    char c;
    char *plist;
    char* pnlist;

    plist = mport_digital_in;
    for (c = 0;c < mszdigital_in; c++, plist++) {
        if (*plist == p) {
            mszdigital_in--;
            break;
        }
    }
    
    pnlist = plist;
    pnlist++;
    for (;c < mszdigital_in; c++, plist++, pnlist++) {
        *plist = *pnlist;
    }
}

char port_set_digital_in(char p)
{
    char cst = mport_funct[p].set;

    if (cst != PORTF_DIG_IN) {
        if (cst & PORTF_SPEC_MASK) {
            return -1;
        }
        mport_funct[p].set = (char) PORTF_DIG_IN;
        pinMode(p, INPUT); //INPUT_PULLUP

        make_digital_in_list();
        port_delete_list(cst,p);

        return 1;
    }
    return 0;
}


// Digital Write - OUT

char port_set_digital_out(char p)
{
    char cst = mport_funct[p].set;

    if (cst != PORTF_DIG_OUT) {
        if (cst & PORTF_SPEC_MASK)
            return -1;

        mport_funct[p].set = (char) PORTF_DIG_OUT;
        pinMode(p, OUTPUT);

        port_delete_list(cst, p);
        return 1;
    }
    return 0;
}


// Ananlog Set

void make_analog_in_list()
{
    char c, l;
    PortMap* pportset = mport_funct;

    pportset += manalog_start_p;
    l = 0;
    for (c = manalog_start_p; c < manalog_end_p; c++, pportset++) {
        if (pportset->set == PORTF_ANALG_IN) {
            mport_analog_in[l] = pportset->dnum;
            l++;
        }
    }
    mszanalog_in = l;
}

char port_set_analog_in(char p)
{
    PortMap* pportset; 
    char cst;

    p += manalog_start_p;

    pportset = mport_funct;
    pportset += p;

    cst = pportset->set;
    if (cst != PORTF_ANALG_IN) {
        if (cst & PORTF_SPEC_MASK ) //== PORTF_I2C)
            return -1;
    
        pportset->set = (char) PORTF_ANALG_IN;

        make_analog_in_list();
        port_delete_list(cst,p);
        DPRINTF("\tA IN set %d\n", p);
        return 1;
    }
    return 0;
}

// PWM Set

char port_set_PWM(char p)
{
    char cst;
    PortMap* pportset = &mport_funct[p];

    if (!(pportset->fun & TPORT_PWM))
        return -1;

    cst = pportset->set;
    if (pportset->set != PORTF_PWM) {
        pportset->set = (char) PORTF_PWM;
        make_pwm_list();
        port_delete_list(cst, p);
        return 1;
    }
    return 0;
}

void make_pwm_list()
{
    char c;
    PortMap* pportset; //  = mport_funct;
    char l;

    l = 0;
#if defined (UNO)
    char port;
    for (c = 0; c < cport_leng; c++) {
        port = cport_pwm[c];
        pportset = &mport_funct[port];
        if (pportset->set == PORTF_PWM) {
            mport_pwm[l] = pportset->dnum;
            l++;
        }
    }
 #elif defined (MEGA) 
    pportset = mport_funct;
    pportset += mpwm_start_p;
    for (c = mpwm_start_p; c <= mpwm_end_p; c++, pportset++) {
        if (pportset->set == PORTF_PWM) {
            mport_pwm[l] = pportset->dnum;
            l++;
        }
    }
#endif
    mszpwm = l;
}


// I2C Set

void port_set_i2c_pin(char p)
{
    char cst;
    PortMap* pportset = &mport_funct[p];

    cst = pportset->set;
    if (cst != PORTF_I2C) {
        pportset->set = (char) PORTF_I2C;
        port_delete_list(cst, p);
    }
}

void port_set_i2c()
{
    port_set_i2c_pin(mport_i2c[0]);
    port_set_i2c_pin(mport_i2c[1]);
}


char port_delete_list(char cst, char p)
{
    switch (cst) {
    case PORTF_DIG_IN:
        //make_digital_in_list(p);
        delete_digital_in_list(p);
        break;
    case PORTF_ANALG_IN:
        make_analog_in_list();
        break;
    case PORTF_PWM:
        make_pwm_list();
        break;
    default:
        return -1;
    }
    return 0;
}
