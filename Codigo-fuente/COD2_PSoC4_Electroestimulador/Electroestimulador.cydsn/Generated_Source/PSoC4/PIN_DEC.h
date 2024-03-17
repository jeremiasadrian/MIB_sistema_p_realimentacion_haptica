/*******************************************************************************
* File Name: PIN_DEC.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PIN_DEC_H) /* Pins PIN_DEC_H */
#define CY_PINS_PIN_DEC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PIN_DEC_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} PIN_DEC_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PIN_DEC_Read(void);
void    PIN_DEC_Write(uint8 value);
uint8   PIN_DEC_ReadDataReg(void);
#if defined(PIN_DEC__PC) || (CY_PSOC4_4200L) 
    void    PIN_DEC_SetDriveMode(uint8 mode);
#endif
void    PIN_DEC_SetInterruptMode(uint16 position, uint16 mode);
uint8   PIN_DEC_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PIN_DEC_Sleep(void); 
void PIN_DEC_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PIN_DEC__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PIN_DEC_DRIVE_MODE_BITS        (3)
    #define PIN_DEC_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PIN_DEC_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PIN_DEC_SetDriveMode() function.
         *  @{
         */
        #define PIN_DEC_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PIN_DEC_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PIN_DEC_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PIN_DEC_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PIN_DEC_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PIN_DEC_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PIN_DEC_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PIN_DEC_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PIN_DEC_MASK               PIN_DEC__MASK
#define PIN_DEC_SHIFT              PIN_DEC__SHIFT
#define PIN_DEC_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PIN_DEC_SetInterruptMode() function.
     *  @{
     */
        #define PIN_DEC_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PIN_DEC_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PIN_DEC_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PIN_DEC_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PIN_DEC__SIO)
    #define PIN_DEC_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PIN_DEC__PC) && (CY_PSOC4_4200L)
    #define PIN_DEC_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PIN_DEC_USBIO_DISABLE              ((uint32)(~PIN_DEC_USBIO_ENABLE))
    #define PIN_DEC_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PIN_DEC_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PIN_DEC_USBIO_ENTER_SLEEP          ((uint32)((1u << PIN_DEC_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PIN_DEC_USBIO_SUSPEND_DEL_SHIFT)))
    #define PIN_DEC_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PIN_DEC_USBIO_SUSPEND_SHIFT)))
    #define PIN_DEC_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PIN_DEC_USBIO_SUSPEND_DEL_SHIFT)))
    #define PIN_DEC_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PIN_DEC__PC)
    /* Port Configuration */
    #define PIN_DEC_PC                 (* (reg32 *) PIN_DEC__PC)
#endif
/* Pin State */
#define PIN_DEC_PS                     (* (reg32 *) PIN_DEC__PS)
/* Data Register */
#define PIN_DEC_DR                     (* (reg32 *) PIN_DEC__DR)
/* Input Buffer Disable Override */
#define PIN_DEC_INP_DIS                (* (reg32 *) PIN_DEC__PC2)

/* Interrupt configuration Registers */
#define PIN_DEC_INTCFG                 (* (reg32 *) PIN_DEC__INTCFG)
#define PIN_DEC_INTSTAT                (* (reg32 *) PIN_DEC__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PIN_DEC_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PIN_DEC__SIO)
    #define PIN_DEC_SIO_REG            (* (reg32 *) PIN_DEC__SIO)
#endif /* (PIN_DEC__SIO_CFG) */

/* USBIO registers */
#if !defined(PIN_DEC__PC) && (CY_PSOC4_4200L)
    #define PIN_DEC_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PIN_DEC_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PIN_DEC_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PIN_DEC_DRIVE_MODE_SHIFT       (0x00u)
#define PIN_DEC_DRIVE_MODE_MASK        (0x07u << PIN_DEC_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PIN_DEC_H */


/* [] END OF FILE */
