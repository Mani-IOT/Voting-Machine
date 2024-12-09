#include<Arduino.h>
#include<CD74HC4067.h>
#include"EXTIO_Lib.h"


//function Definition
//idx{1, 2, 3, 4, 5, 6, 7, 8, 11, 0, 12, 13, 15, 10, 14, 9}
/**
 * @brief Constructor a new InOut:: InOut object and : intialised list {}
 * 
 * @param s0  Selecter pin s0
 * @param s1  Selecter pin s1
 * @param s2  Selecter pin s2
 * @param s3  Selecter pin s3
 * @param _common_Z Output pin 
 */
InOut::InOut(int s0, int s1, int s2, int s3, int _common_Z): CD74HC4067( s0,  s1,  s2, s3), common_Z(_common_Z), threshold(512), idx{0, 1, 2, 3, 4, 5, 6, 7, 10, 15, 11, 12, 14, 9, 13, 8}{
}

// DOXYGEN
/**
 * @brief write the RO status to the corresponding address 
 * 
 * @param ad address(ad) of RO
 * @param ac ON as 1 OFF as 0, status of RO
 */


/*void InOut::RO_Write(byte ad,bool ac)

{
    if(ac==1)
    {
        channel(ad+8);
       // delay(200);
    }
}


 * @brief write the DO status  to the corresponding address 
 * 
 * @param ad address(ad) of DO
 * @param ac ON as 1, OFF as 0, status of DO
 */

/* void InOut::DO_Write(byte ad,bool ac)

    if(ac==1)
    {
        channel(ad);
        //delay(200);
    }
}




 * @brief Read the DI status from the corresponding address 
 * 
 * @param ad address of DI
 * @return 1 ON status of DI
 * @return 0 OFF status of DI
 */
 bool InOut::DI_Read(byte ad)
{
    channel(idx[ad]);
    delay(2);
    if (analogRead(common_Z) <= threshold)
        return 1;
    else
        return 0;

}
/**
 * @brief Read the ACI status from the corresponding address  
 * 
 * @param ad address of ACI
 * @return 1 ON status of ACI
 * @return 0 OFF status of ACI
 */
 bool InOut:: ACI_Read(byte ad)
{
    
    channel(idx[ad+8]);
    delay(2);
    if (analogRead(common_Z) <= threshold)
    // {
    //     //Serial.println("Pin " + String(ad) + ": ON");

    //     return 1;
    // }
        return 1;
    else
        return 0;

}  