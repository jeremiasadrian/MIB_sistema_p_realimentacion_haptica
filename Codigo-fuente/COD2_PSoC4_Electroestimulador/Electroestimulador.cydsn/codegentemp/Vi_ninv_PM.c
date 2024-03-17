/*******************************************************************************
* File Name: Vi_ninv.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Vi_ninv.h"

static Vi_ninv_BACKUP_STRUCT  Vi_ninv_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Vi_ninv_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Vi_ninv_SUT.c usage_Vi_ninv_Sleep_Wakeup
*******************************************************************************/
void Vi_ninv_Sleep(void)
{
    #if defined(Vi_ninv__PC)
        Vi_ninv_backup.pcState = Vi_ninv_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Vi_ninv_backup.usbState = Vi_ninv_CR1_REG;
            Vi_ninv_USB_POWER_REG |= Vi_ninv_USBIO_ENTER_SLEEP;
            Vi_ninv_CR1_REG &= Vi_ninv_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Vi_ninv__SIO)
        Vi_ninv_backup.sioState = Vi_ninv_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Vi_ninv_SIO_REG &= (uint32)(~Vi_ninv_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Vi_ninv_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Vi_ninv_Sleep() for an example usage.
*******************************************************************************/
void Vi_ninv_Wakeup(void)
{
    #if defined(Vi_ninv__PC)
        Vi_ninv_PC = Vi_ninv_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Vi_ninv_USB_POWER_REG &= Vi_ninv_USBIO_EXIT_SLEEP_PH1;
            Vi_ninv_CR1_REG = Vi_ninv_backup.usbState;
            Vi_ninv_USB_POWER_REG &= Vi_ninv_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Vi_ninv__SIO)
        Vi_ninv_SIO_REG = Vi_ninv_backup.sioState;
    #endif
}


/* [] END OF FILE */
