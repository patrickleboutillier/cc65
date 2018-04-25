/*****************************************************************************/
/*                                                                           */
/*                               accelerator.h                               */
/*                                                                           */
/*                      Accelerator specific definitions                     */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* (C) 2018 Marco van den Heuvel                                             */
/* EMail:        blackystardust68@yahoo.com                                  */
/*                                                                           */
/*                                                                           */
/* This software is provided 'as-is', without any expressed or implied       */
/* warranty.  In no event will the authors be held liable for any damages    */
/* arising from the use of this software.                                    */
/*                                                                           */
/* Permission is granted to anyone to use this software for any purpose,     */
/* including commercial applications, and to alter it and redistribute it    */
/* freely, subject to the following restrictions:                            */
/*                                                                           */
/* 1. The origin of this software must not be misrepresented; you must not   */
/*    claim that you wrote the original software. If you use this software   */
/*    in a product, an acknowledgment in the product documentation would be  */
/*    appreciated but is not required.                                       */
/* 2. Altered source versions must be plainly marked as such, and must not   */
/*    be misrepresented as being the original software.                      */
/* 3. This notice may not be removed or altered from any source              */
/*    distribution.                                                          */
/*                                                                           */
/*****************************************************************************/



#ifndef _ACCELERATOR_H
#define _ACCELERATOR_H

/*****************/
/* Speed defines */
/*****************/

#define SPEED_SLOW   0x00
#define SPEED_FAST   0xFF

#define SPEED_1X   SPEED_SLOW
#define SPEED_2X    2 - 1        /* C64 Chameleon, C64DTV, C128, PET 65816, Apple2 Fast Chip, Apple2 TransWarp, Apple2 Zip Chip */
#define SPEED_3X    3 - 1        /* C64 Chameleon, C65, PET 65816, Apple2 Booster, Apple 2 Fast Chip, Apple2 Titan, Apple2 TransWarp, Apple2 Zip Chip */
#define SPEED_4X    4 - 1        /* C64 Chameleon, C64 TurboMaster, C64 TurboProcess, PET 65816, Apple2 Fast Chip, Apple2 Zip Chip */
#define SPEED_5X    5 - 1        /* C64 Chameleon, PET 65816, Apple2 Fast Chip */
#define SPEED_6X    6 - 1        /* C64 Chameleon, PET 65816, Apple2 Fast Chip */
#define SPEED_7X    7 - 1        /* PET 65816, Apple2 Fast Chip */
#define SPEED_8X    8 - 1        /* C64 Flash8, PET 65816, Apple 2 Fast Chip */
#define SPEED_10X  10 - 1        /* PET 65816, Apple2 Fast Chip */
#define SPEED_12X  12 - 1        /* Apple2 Fast Chip */
#define SPEED_16X  16 - 1        /* Apple2 Fast Chip */
#define SPEED_20X  20 - 1        /* C64/C128 SuperCPU */

/***********************************/
/* Accelerator function prototypes */
/***********************************/

/* C64/C128 SuperCPU cartridge */

extern unsigned char __fastcall__ set_scpu_speed (unsigned char speed);

/* Set the speed of the SuperCPU cartridge, using SPEED_SLOW will switch to
 * 1 Mhz mode, SPEED_20X or SPEED_FAST will switch to 20 Mhz mode.
 *
 * Note that any value lower than SPEED_20X will switch to 1 Mhz mode, and
 * any value higher or equal to SPEED_20X will switch to 20 Mhz mode.
 *
 * This function will return the actual speed the CPU is at after trying
 * to set the requested speed, if this is not the speed that was requested
 * then possibly the hardware speed switch prevented any software speed
 * switching.
 *
 * This function does not check for the presence of the SuperCPU cartridge,
 * make sure you use 'detect_scpu();' before using.
 */

extern unsigned char get_scpu_speed (void);

/* Get the speed of the SuperCPU cartridge.
 *
 * Possible return values:
 * SPEED_1X    :  1 Mhz mode
 * SPEED_20X   : 20 Mhz mode
 *
 * This function does not check for the presence of the SuperCPU cartridge,
 * make sure you use 'detect_scpu();' before using.
 */

extern unsigned char detect_scpu (void);

/* Check for the presence of the SuperCPU cartridge.
 *
 * Possible return values:
 * 0x00  : SuperCPU cartridge not present
 * 0x01  : SuperCPU cartridge present
 */


/* C64DTV */

extern unsigned char __fastcall__ set_c64dtv_speed (unsigned char speed);

/* Set the speed of the C64DTV, using SPEED_SLOW will switch to
 * slow mode, SPEED_2X or SPEED_FAST will switch to fast mode.
 *
 * Note that any value higher or equal to SPEED_2X will switch to fast mode.
 *
 * This function will return the actual speed the CPU is at after trying
 * to set the requested speed, to my knowledge the switch should not fail.
 *
 * This function does not check for the presence of the C64DTV,
 * make sure you use 'detect_c64dtv();' before using.
 */

extern unsigned char get_c64dtv_speed (void);

/* Get the speed of the C64DTV.
 *
 * Possible return values:
 * SPEED_1X    : slow mode
 * SPEED_2X    : fast mode
 *
 * This function does not check for the presence of the C64DTV,
 * make sure you use 'detect_c64dtv();' before using.
 */

extern unsigned char detect_c64dtv (void);

/* Check for the presence of the C64DTV.
 *
 * Possible return values:
 * 0x00  : C64DTV not present
 * 0x01  : C64DTV present
 */


/* C128 8502 CPU */

extern unsigned char __fastcall__ set_c128_speed (unsigned char speed);

/* Set the speed of the C128 8502 CPU, using SPEED_SLOW will switch to
 * 1 Mhz (slow) mode, SPEED_2X or SPEED_FAST will switch to 2Mhz (fast) mode.
 *
 * Note that any value higher or equal to SPEED_2X will switch to fast mode.
 *
 * This function will return the actual speed the CPU is at after trying
 * to set the requested speed, to my knowledge the switching should not fail.
 *
 * This function does not check if the C128 CPU is the current CPU, make sure
 * you use 'detect_c128();' before using.
 */

extern unsigned char get_c128_speed (void);

/* Get the speed of the C128 8502 CPU.
 *
 * Possible return values:
 * SPEED_SLOW  : Slow mode
 * SPEED_2X    : Fast mode
 *
 * This function does not check if the C128 CPU is the current CPU, make sure
 * you use 'detect_c128();' before using.
 */

extern unsigned char detect_c128 (void);

/* Check if the C128 CPU is the current CPU.
 *
 * Possible return values:
 * 0x00  : C128 CPU is not the current CPU
 * 0x01  : C128 CPU is the current CPU
 */

/* End of accelerator.h */
#endif

