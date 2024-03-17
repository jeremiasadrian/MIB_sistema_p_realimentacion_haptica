/*******************************************************************************
* File Name: INC_INT.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_INC_INT_H)
#define CY_ISR_INC_INT_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void INC_INT_Start(void);
void INC_INT_StartEx(cyisraddress address);
void INC_INT_Stop(void);

CY_ISR_PROTO(INC_INT_Interrupt);

void INC_INT_SetVector(cyisraddress address);
cyisraddress INC_INT_GetVector(void);

void INC_INT_SetPriority(uint8 priority);
uint8 INC_INT_GetPriority(void);

void INC_INT_Enable(void);
uint8 INC_INT_GetState(void);
void INC_INT_Disable(void);

void INC_INT_SetPending(void);
void INC_INT_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the INC_INT ISR. */
#define INC_INT_INTC_VECTOR            ((reg32 *) INC_INT__INTC_VECT)

/* Address of the INC_INT ISR priority. */
#define INC_INT_INTC_PRIOR             ((reg32 *) INC_INT__INTC_PRIOR_REG)

/* Priority of the INC_INT interrupt. */
#define INC_INT_INTC_PRIOR_NUMBER      INC_INT__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable INC_INT interrupt. */
#define INC_INT_INTC_SET_EN            ((reg32 *) INC_INT__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the INC_INT interrupt. */
#define INC_INT_INTC_CLR_EN            ((reg32 *) INC_INT__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the INC_INT interrupt state to pending. */
#define INC_INT_INTC_SET_PD            ((reg32 *) INC_INT__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the INC_INT interrupt. */
#define INC_INT_INTC_CLR_PD            ((reg32 *) INC_INT__INTC_CLR_PD_REG)



#endif /* CY_ISR_INC_INT_H */


/* [] END OF FILE */
