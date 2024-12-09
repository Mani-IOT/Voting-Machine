#ifndef _EXTIO_H
#define _EXTIO_H

#include <CD74HC4067.h>
/**
 * @brief Main Class InOut
 * 
 * 
 */
class InOut: public CD74HC4067  

{
private:
    /* data */
    //byte Rp; 
    int common_Z;
    int threshold;
    const int idx[16];

public:
    InOut (int s0, int s1, int s2, int s3,int _common_Z=-1);
      
     


     //void RO_Write(byte ad,bool ac);
     //void DO_Write (byte ad,bool ac);
      bool DI_Read (byte ad);
      bool ACI_Read(byte ad);
};

#endif

