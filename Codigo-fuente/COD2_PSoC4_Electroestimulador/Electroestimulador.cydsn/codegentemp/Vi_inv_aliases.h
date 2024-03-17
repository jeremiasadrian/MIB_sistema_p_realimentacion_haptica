/*******************************************************************************
* File Name: Vi_inv.h  
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

#if !defined(CY_PINS_Vi_inv_ALIASES_H) /* Pins Vi_inv_ALIASES_H */
#define CY_PINS_Vi_inv_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Vi_inv_0			(Vi_inv__0__PC)
#define Vi_inv_0_PS		(Vi_inv__0__PS)
#define Vi_inv_0_PC		(Vi_inv__0__PC)
#define Vi_inv_0_DR		(Vi_inv__0__DR)
#define Vi_inv_0_SHIFT	(Vi_inv__0__SHIFT)
#define Vi_inv_0_INTR	((uint16)((uint16)0x0003u << (Vi_inv__0__SHIFT*2u)))

#define Vi_inv_INTR_ALL	 ((uint16)(Vi_inv_0_INTR))


#endif /* End Pins Vi_inv_ALIASES_H */


/* [] END OF FILE */
