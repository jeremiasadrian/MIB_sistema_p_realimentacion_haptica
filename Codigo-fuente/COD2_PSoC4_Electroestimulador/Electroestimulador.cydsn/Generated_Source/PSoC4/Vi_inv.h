/*******************************************************************************
* File Name: Vi_inv.h  
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

#if !defined(CY_PINS_Vi_inv_H) /* Pins Vi_inv_H */
#define CY_PINS_Vi_inv_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Vi_inv_aliases.h"


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
} Vi_inv_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Vi_inv_Read(void);
void    Vi_inv_Write(uint8 value);
uint8   Vi_inv_ReadDataReg(void);
#if defined(Vi_inv__PC) || (CY_PSOC4_4200L) 
    void    Vi_inv_SetDriveMode(uint8 mode);
#endif
void    Vi_inv_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vi_inv_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Vi_inv_Sleep(void); 
void Vi_inv_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Vi_inv__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Vi_inv_DRIVE_MODE_BITS        (3)
    #define Vi_inv_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Vi_inv_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Vi_inv_SetDriveMode() function.
         *  @{
         */
        #define Vi_inv_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Vi_inv_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Vi_inv_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Vi_inv_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Vi_inv_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Vi_inv_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Vi_inv_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Vi_inv_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Vi_inv_MASK               Vi_inv__MASK
#define Vi_inv_SHIFT              Vi_inv__SHIFT
#define Vi_inv_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vi_inv_SetInterruptMode() function.
     *  @{
     */
        #define Vi_inv_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Vi_inv_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Vi_inv_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Vi_inv_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Vi_inv__SIO)
    #define Vi_inv_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Vi_inv__PC) && (CY_PSOC4_4200L)
    #define Vi_inv_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Vi_inv_USBIO_DISABLE              ((uint32)(~Vi_inv_USBIO_ENABLE))
    #define Vi_inv_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Vi_inv_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Vi_inv_USBIO_ENTER_SLEEP          ((uint32)((1u << Vi_inv_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Vi_inv_USBIO_SUSPEND_DEL_SHIFT)))
    #define Vi_inv_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Vi_inv_USBIO_SUSPEND_SHIFT)))
    #define Vi_inv_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Vi_inv_USBIO_SUSPEND_DEL_SHIFT)))
    #define Vi_inv_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Vi_inv__PC)
    /* Port Configuration */
    #define Vi_inv_PC                 (* (reg32 *) Vi_inv__PC)
#endif
/* Pin State */
#define Vi_inv_PS                     (* (reg32 *) Vi_inv__PS)
/* Data Register */
#define Vi_inv_DR                     (* (reg32 *) Vi_inv__DR)
/* Input Buffer Disable Override */
#define Vi_inv_INP_DIS                (* (reg32 *) Vi_inv__PC2)

/* Interrupt configuration Registers */
#define Vi_inv_INTCFG                 (* (reg32 *) Vi_inv__INTCFG)
#define Vi_inv_INTSTAT                (* (reg32 *) Vi_inv__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Vi_inv_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Vi_inv__SIO)
    #define Vi_inv_SIO_REG            (* (reg32 *) Vi_inv__SIO)
#endif /* (Vi_inv__SIO_CFG) */

/* USBIO registers */
#if !defined(Vi_inv__PC) && (CY_PSOC4_4200L)
    #define Vi_inv_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Vi_inv_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Vi_inv_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Vi_inv_DRIVE_MODE_SHIFT       (0x00u)
#define Vi_inv_DRIVE_MODE_MASK        (0x07u << Vi_inv_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Vi_inv_H */


/* [] END OF FILE */
