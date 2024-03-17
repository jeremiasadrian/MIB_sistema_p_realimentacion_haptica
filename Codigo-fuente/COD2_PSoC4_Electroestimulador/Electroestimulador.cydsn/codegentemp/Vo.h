/*******************************************************************************
* File Name: Vo.h  
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

#if !defined(CY_PINS_Vo_H) /* Pins Vo_H */
#define CY_PINS_Vo_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Vo_aliases.h"


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
} Vo_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Vo_Read(void);
void    Vo_Write(uint8 value);
uint8   Vo_ReadDataReg(void);
#if defined(Vo__PC) || (CY_PSOC4_4200L) 
    void    Vo_SetDriveMode(uint8 mode);
#endif
void    Vo_SetInterruptMode(uint16 position, uint16 mode);
uint8   Vo_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Vo_Sleep(void); 
void Vo_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Vo__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Vo_DRIVE_MODE_BITS        (3)
    #define Vo_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Vo_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Vo_SetDriveMode() function.
         *  @{
         */
        #define Vo_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Vo_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Vo_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Vo_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Vo_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Vo_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Vo_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Vo_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Vo_MASK               Vo__MASK
#define Vo_SHIFT              Vo__SHIFT
#define Vo_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Vo_SetInterruptMode() function.
     *  @{
     */
        #define Vo_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Vo_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Vo_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Vo_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Vo__SIO)
    #define Vo_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Vo__PC) && (CY_PSOC4_4200L)
    #define Vo_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Vo_USBIO_DISABLE              ((uint32)(~Vo_USBIO_ENABLE))
    #define Vo_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Vo_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Vo_USBIO_ENTER_SLEEP          ((uint32)((1u << Vo_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Vo_USBIO_SUSPEND_DEL_SHIFT)))
    #define Vo_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Vo_USBIO_SUSPEND_SHIFT)))
    #define Vo_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Vo_USBIO_SUSPEND_DEL_SHIFT)))
    #define Vo_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Vo__PC)
    /* Port Configuration */
    #define Vo_PC                 (* (reg32 *) Vo__PC)
#endif
/* Pin State */
#define Vo_PS                     (* (reg32 *) Vo__PS)
/* Data Register */
#define Vo_DR                     (* (reg32 *) Vo__DR)
/* Input Buffer Disable Override */
#define Vo_INP_DIS                (* (reg32 *) Vo__PC2)

/* Interrupt configuration Registers */
#define Vo_INTCFG                 (* (reg32 *) Vo__INTCFG)
#define Vo_INTSTAT                (* (reg32 *) Vo__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Vo_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Vo__SIO)
    #define Vo_SIO_REG            (* (reg32 *) Vo__SIO)
#endif /* (Vo__SIO_CFG) */

/* USBIO registers */
#if !defined(Vo__PC) && (CY_PSOC4_4200L)
    #define Vo_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Vo_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Vo_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Vo_DRIVE_MODE_SHIFT       (0x00u)
#define Vo_DRIVE_MODE_MASK        (0x07u << Vo_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Vo_H */


/* [] END OF FILE */
