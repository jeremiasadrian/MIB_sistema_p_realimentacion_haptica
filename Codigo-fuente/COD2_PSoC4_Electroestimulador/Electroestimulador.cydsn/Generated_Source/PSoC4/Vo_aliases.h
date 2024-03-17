/*******************************************************************************
* File Name: Vo.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Vo_ALIASES_H) /* Pins Vo_ALIASES_H */
#define CY_PINS_Vo_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Vo_0			(Vo__0__PC)
#define Vo_0_PS		(Vo__0__PS)
#define Vo_0_PC		(Vo__0__PC)
#define Vo_0_DR		(Vo__0__DR)
#define Vo_0_SHIFT	(Vo__0__SHIFT)
#define Vo_0_INTR	((uint16)((uint16)0x0003u << (Vo__0__SHIFT*2u)))

#define Vo_INTR_ALL	 ((uint16)(Vo_0_INTR))


#endif /* End Pins Vo_ALIASES_H */


/* [] END OF FILE */
