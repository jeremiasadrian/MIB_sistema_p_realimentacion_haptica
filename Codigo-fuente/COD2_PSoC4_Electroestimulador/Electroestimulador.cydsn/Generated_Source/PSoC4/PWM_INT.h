/*******************************************************************************
* File Name: PWM_INT.h
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
#if !defined(CY_ISR_PWM_INT_H)
#define CY_ISR_PWM_INT_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void PWM_INT_Start(void);
void PWM_INT_StartEx(cyisraddress address);
void PWM_INT_Stop(void);

CY_ISR_PROTO(PWM_INT_Interrupt);

void PWM_INT_SetVector(cyisraddress address);
cyisraddress PWM_INT_GetVector(void);

void PWM_INT_SetPriority(uint8 priority);
uint8 PWM_INT_GetPriority(void);

void PWM_INT_Enable(void);
uint8 PWM_INT_GetState(void);
void PWM_INT_Disable(void);

void PWM_INT_SetPending(void);
void PWM_INT_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the PWM_INT ISR. */
#define PWM_INT_INTC_VECTOR            ((reg32 *) PWM_INT__INTC_VECT)

/* Address of the PWM_INT ISR priority. */
#define PWM_INT_INTC_PRIOR             ((reg32 *) PWM_INT__INTC_PRIOR_REG)

/* Priority of the PWM_INT interrupt. */
#define PWM_INT_INTC_PRIOR_NUMBER      PWM_INT__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable PWM_INT interrupt. */
#define PWM_INT_INTC_SET_EN            ((reg32 *) PWM_INT__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the PWM_INT interrupt. */
#define PWM_INT_INTC_CLR_EN            ((reg32 *) PWM_INT__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the PWM_INT interrupt state to pending. */
#define PWM_INT_INTC_SET_PD            ((reg32 *) PWM_INT__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the PWM_INT interrupt. */
#define PWM_INT_INTC_CLR_PD            ((reg32 *) PWM_INT__INTC_CLR_PD_REG)



#endif /* CY_ISR_PWM_INT_H */


/* [] END OF FILE */
