/**
 **************************************************************************************************
 * @file        tea.c
 * @author
 * @version
 * @date        6/24/2016
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "stdint.h"
#include "tea.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    tea_Modules 
 * @{  
 */

/**
 * @defgroup      tea_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       tea_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      tea_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       tea_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      tea_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      tea_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      tea_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      tea_Functions 
 * @brief         
 * @{  
 */
void TEA_Encrypt(uint8_t *pPlain,uint8_t *pCipher,uint32_t *pKey)
{
    uint32_t y, z, sum=0, i;         /* set up */ 
    uint32_t delta=0x9e3779b9;                 /* a key schedule constant */ 
    uint32_t a=pKey[0], b=pKey[1], c=pKey[2], d=pKey[3];   /* cache key */ 

    y = ((uint32_t)pPlain[0]<<24) + ((uint32_t)pPlain[1]<<16) + ((uint32_t)pPlain[2]<<8) + (pPlain[3]);
    z = ((uint32_t)pPlain[4]<<24) + ((uint32_t)pPlain[5]<<16) + ((uint32_t)pPlain[6]<<8) + (pPlain[7]);

    for (i=0; i < 32; i++) 
    {                        /* basic cycle start */
        sum += delta; 
        y += ((z<<4) + a) ^ (z + sum) ^ ((z>>5) + b); 
        z += ((y<<4) + c) ^ (y + sum) ^ ((y>>5) + d);/* end cycle */ 
    } 

    pCipher[0] = (y>>24)&0x000000FF;
    pCipher[1] = (y>>16)&0x000000FF;
    pCipher[2] = (y>>8)&0x000000FF;
    pCipher[3] = (y)&0x000000FF;
    pCipher[4] = (z>>24)&0x000000FF;
    pCipher[5] = (z>>16)&0x000000FF;
    pCipher[6] = (z>>8)&0x000000FF;
    pCipher[7] = (z)&0x000000FF;
}

void TEA_Decrypt(uint8_t *pCipher,uint8_t *pPlain,uint32_t *pKey) 
{ 
    uint32_t y, z, sum=0xC6EF3720, i; /* set up */ 
    uint32_t delta=0x9e3779b9;                  /* a key schedule constant */ 
    uint32_t a=pKey[0], b=pKey[1], c=pKey[2], d=pKey[3];    /* cache key */ 


    y = ((uint32_t)pCipher[0]<<24) + ((uint32_t)pCipher[1]<<16) + ((uint32_t)pCipher[2]<<8) + ((uint32_t)pCipher[3]);
    z = ((uint32_t)pCipher[4]<<24) + ((uint32_t)pCipher[5]<<16) + ((uint32_t)pCipher[6]<<8) + ((uint32_t)pCipher[7]);

    for(i=0; i<32; i++) 
    {                            /* basic cycle start */ 
        z -= ((y<<4) + c) ^ (y + sum) ^ ((y>>5) + d); 
        y -= ((z<<4) + a) ^ (z + sum) ^ ((z>>5) + b);
        sum -= delta;                                /* end cycle */ 
    } 
    pPlain[0] = (y>>24)&0x000000FF;
    pPlain[1] = (y>>16)&0x000000FF;
    pPlain[2] = (y>>8)&0x000000FF;
    pPlain[3] = (y)&0x000000FF;
    pPlain[4] = (z>>24)&0x000000FF;
    pPlain[5] = (z>>16)&0x000000FF;
    pPlain[6] = (z>>8)&0x000000FF;
    pPlain[7] = (z)&0x000000FF;
}
//void TEA_Encrypt(uint32* v, uint32* k) 
//{ 
//    uint32 y=v[0], z=v[1], sum=0, i;         /* set up */ 
//    uint32 delta=0x9e3779b9;                 /* a key schedule constant */ 
//    uint32 a=k[0], b=k[1], c=k[2], d=k[3];   /* cache key */ 
//    for (i=0; i < 32; i++) 
//    {                        /* basic cycle start */
//        sum += delta; 
//        y += ((z<<4) + a) ^ (z + sum) ^ ((z>>5) + b); 
//        z += ((y<<4) + c) ^ (y + sum) ^ ((y>>5) + d);/* end cycle */ 
//    } 
//    v[0]=y;
//    v[1]=z; 
//} 

//void TEA_Decrypt(uint32* v, uint32* k) 
//{ 
//    uint32 y=v[0], z=v[1], sum=0xC6EF3720, i; /* set up */ 
//    uint32 delta=0x9e3779b9;                  /* a key schedule constant */ 
//    uint32 a=k[0], b=k[1], c=k[2], d=k[3];    /* cache key */ 
//    for(i=0; i<32; i++) 
//    {                            /* basic cycle start */ 
//        z -= ((y<<4) + c) ^ (y + sum) ^ ((y>>5) + d); 
//        y -= ((z<<4) + a) ^ (z + sum) ^ ((z>>5) + b);
//        sum -= delta;                                /* end cycle */ 
//    } 
//    v[0]=y; 
//    v[1]=z;
//}
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

