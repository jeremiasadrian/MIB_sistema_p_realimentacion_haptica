/*******************************************************************************
* File Name: Vo.c  
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
#include "Vo.h"

static Vo_BACKUP_STRUCT  Vo_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Vo_Sleep
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
*  \snippet Vo_SUT.c usage_Vo_Sleep_Wakeup
*******************************************************************************/
void Vo_Sleep(void)
{
    #if defined(Vo__PC)
        Vo_backup.pcState = Vo_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Vo_backup.usbState = Vo_CR1_REG;
            Vo_USB_POWER_REG |= Vo_USBIO_ENTER_SLEEP;
            Vo_CR1_REG &= Vo_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Vo__SIO)
        Vo_backup.sioState = Vo_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Vo_SIO_REG &= (uint32)(~Vo_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Vo_Wakeup
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
*  Refer to Vo_Sleep() for an example usage.
*******************************************************************************/
void Vo_Wakeup(void)
{
    #if defined(Vo__PC)
        Vo_PC = Vo_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Vo_USB_POWER_REG &= Vo_USBIO_EXIT_SLEEP_PH1;
            Vo_CR1_REG = Vo_backup.usbState;
            Vo_USB_POWER_REG &= Vo_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Vo__SIO)
        Vo_SIO_REG = Vo_backup.sioState;
    #endif
}


/* [] END OF FILE */
