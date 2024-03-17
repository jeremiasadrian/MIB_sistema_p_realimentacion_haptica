/*******************************************************************************
* File Name: PIN_DEC.c  
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
#include "PIN_DEC.h"

static PIN_DEC_BACKUP_STRUCT  PIN_DEC_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: PIN_DEC_Sleep
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
*  \snippet PIN_DEC_SUT.c usage_PIN_DEC_Sleep_Wakeup
*******************************************************************************/
void PIN_DEC_Sleep(void)
{
    #if defined(PIN_DEC__PC)
        PIN_DEC_backup.pcState = PIN_DEC_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            PIN_DEC_backup.usbState = PIN_DEC_CR1_REG;
            PIN_DEC_USB_POWER_REG |= PIN_DEC_USBIO_ENTER_SLEEP;
            PIN_DEC_CR1_REG &= PIN_DEC_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PIN_DEC__SIO)
        PIN_DEC_backup.sioState = PIN_DEC_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        PIN_DEC_SIO_REG &= (uint32)(~PIN_DEC_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: PIN_DEC_Wakeup
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
*  Refer to PIN_DEC_Sleep() for an example usage.
*******************************************************************************/
void PIN_DEC_Wakeup(void)
{
    #if defined(PIN_DEC__PC)
        PIN_DEC_PC = PIN_DEC_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            PIN_DEC_USB_POWER_REG &= PIN_DEC_USBIO_EXIT_SLEEP_PH1;
            PIN_DEC_CR1_REG = PIN_DEC_backup.usbState;
            PIN_DEC_USB_POWER_REG &= PIN_DEC_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PIN_DEC__SIO)
        PIN_DEC_SIO_REG = PIN_DEC_backup.sioState;
    #endif
}


/* [] END OF FILE */
