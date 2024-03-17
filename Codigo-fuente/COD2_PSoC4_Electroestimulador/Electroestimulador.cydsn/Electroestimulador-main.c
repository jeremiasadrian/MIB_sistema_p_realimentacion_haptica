/* ========================================
    Programa para Electroestimulador.
======================================== */
    
#include <project.h>
#include <stdio.h>
    
uint8 estadoSIS = 0;    //Bandera de estado: 0 = reiniciado; 1 = configuración de TIc; 2 = configuración de Fx; 3 = configurado; 4 = en operación.
uint16 TIc = 0;         //Valor de TIc: 1=150us; 2=160us; 3=170us;....; 15=290us; 16=300us.
uint8 TIc_sel=0;        //Bandera de señalización del valor de TIc selecionado.
uint16 F1 = 0;          //Valor de la F1 asicoada al TIc seleccionado.
uint16 F2 = 0;          //Valor de la F2 asicoada al TIc seleccionado.
uint16 F3 = 0;          //Valor de la F3 asicoada al TIc seleccionado.
uint16 FREQ = 0;        //Valor de frecuencia seleccionado de las 3 disponibles.
uint8 F_sel=0;          //Bandera de selección de frecuencia temporal.
uint32 Iout;            //Variable para setear la salida de IDAC_1.
uint16 Ic=0;
char8 printTIc[3];
char8 printIc[3];
char8 printF1[4];
char8 printF2[4];
char8 printF3[4];
char8 printFREQ[4];

CY_ISR(ACEP_INT_Handler) //Subrutina del boton ACEPTAR/PARAR del menu.
{
    uint32 compVal;
    uint32 periodo;
    if(estadoSIS==4)
        estadoSIS = 1;
    else
        estadoSIS++;
    switch(estadoSIS)
    {
        case 1: PWM_Stop();
                IDAC_1_Stop();
                AMux_DisconnectAll();
                LCD_ClearDisplay();
                LCD_Position(0,0);
                LCD_PrintString("Seleccione TIc");
                TIc = 150;
                TIc_sel = 0;
                LCD_Position(1,0);
                sprintf(printTIc,"%3d",TIc);
                LCD_PrintString(printTIc);
                LCD_Position(1,5);
                LCD_PrintString("us");
                break;
        case 2: LCD_ClearDisplay();
                LCD_Position(0,0);
                LCD_PrintString("Seleccione Freq.");
                switch(TIc_sel)
                {
                 case 0: F1 = 1111;
                         F2 = 714;
                         F3 = 555;
                         break;
                 case 1: 
                         F1 = 1042;
                         F2 = 685;
                         F3 = 521; 
                         break;
                 case 2: F1 = 980;
                         F2 = 658;
                         F3 = 490;  
                         break;
                 case 3: F1 = 926;
                         F2 = 633;
                         F3 = 463; 
                         break;
                 case 4: F1 = 877;
                         F2 = 610;
                         F3 = 439;  
                         break;
                 case 5: F1 = 833;      //TIc = 200 us.
                         F2 = 588;
                         F3 = 417;  
                         break;
                 case 6: F1 = 794;
                         F2 = 568;
                         F3 = 397;
                         break;
                 case 7: F1 = 758;      //Tic = 220 us.
                         F2 = 549;
                         F3 = 379;
                         break;
                 case 8: F1 = 725;      //Tic = 230 us.
                         F2 = 532;
                         F3 = 362; 
                         break;
                 case 9: F1 = 695;
                          F2 = 515;
                          F3 = 347; 
                          break;
                 case 10: F1 = 666;
                          F2 = 500;
                          F3 = 333;  
                          break;
                 case 11: F1 = 641;
                          F2 = 485;
                          F3 = 320;
                          break;
                 case 12: F1 = 617;
                          F2 = 472;
                          F3 = 309;
                          break;
                 case 13: F1 = 595;
                          F2 = 459;
                          F3 = 298; 
                          break;
                 case 14: F1 = 575;
                          F2 = 446;
                          F3 = 287;
                          break;
                 case 15: F1 = 555;     //TIc = 300 us.
                          F2 = 435;
                          F3 = 278;
                          break;
                 default: break;
                }
                sprintf(printF1,"%4d",F1);
                sprintf(printF2,"%4d",F2);
                sprintf(printF3,"%4d",F3);
                LCD_Position(1,0);
                LCD_PutChar('>');
                LCD_Position(1,1);
                LCD_PrintString(printF1);
                LCD_Position(1,6);
                LCD_PrintString(printF2);
                LCD_Position(1,11);
                LCD_PrintString(printF3);
                F_sel=1;
                break;
        case 3: switch(F_sel)
                {
                    case 1: FREQ = F1;
                            break;
                    case 2: FREQ = F2;
                            break;
                    case 3: FREQ = F3;
                            break;
                    default: break;
                }
                LCD_ClearDisplay();
                LCD_Position(0,0);
                LCD_PrintString("TIc=   us");
                sprintf(printTIc,"%3d",TIc);
                LCD_Position(0,4);
                LCD_PrintString(printTIc);
                LCD_Position(0,10);
                LCD_PrintString("F=");
                sprintf(printFREQ,"%4d",FREQ);
                LCD_Position(0,12);
                LCD_PrintString(printFREQ);
                LCD_Position(1,0);
                LCD_PrintString("Ic=12uA INICIAR?");
                Iout = 5;
                break;
        case 4: PWM_Start();
                periodo = 450000/FREQ;  //Cálculo del valor a cargar en el periodo del TCPWM en función de clock de 450kHz.
                compVal = (450000*TIc)/1000000; //Cálculo del valor a cargar en el registro de comparación del TCPWM en función de clock de 450kHz.
                PWM_WritePeriod(periodo);   //Instrucciones para aceptar los valores selecionados.
                PWM_WriteCompare(compVal);
                IDAC_1_Start();
                LCD_ClearDisplay();
                LCD_Position(0,0);
                LCD_PrintString("Ic=    uA  >ON< ");
                Ic = Iout;
                LCD_Position(0,3);
                sprintf(printIc,"%3d",Ic);
                LCD_PrintString(printIc);
                LCD_Position(1,0);
                LCD_PrintString("Pulse ACEP p fin");
                IDAC_1_SetValue(Iout);
                break;
        default: break;
    }
    PIN_ACEP_ClearInterrupt();
    CyDelay(50);
}

CY_ISR(DEC_INT_Handler) //Subrutina del boton DECREMENTAR del menu.
{
    switch(estadoSIS)
    {
        case 1: if(TIc_sel==0)
                    TIc_sel = 15;
                else
                    TIc_sel--;
                if(TIc<=150)
                    TIc = 300;
                else
                    TIc=TIc-10;
                LCD_Position(1,0);
                sprintf(printTIc,"%3d",TIc);
                LCD_PrintString(printTIc);
                LCD_Position(1,5);
                LCD_PrintString("us");
                break;
        case 2: F_sel--;
                if(F_sel<1)
                    F_sel=3;
                else{}
                switch(F_sel)
                {
                 case 1: LCD_Position(1,0);
                         LCD_PutChar('>');
                         LCD_Position(1,6);
                         LCD_PutChar(' ');
                         LCD_Position(1,11);
                         LCD_PutChar(' ');
                         break;
                 case 2: LCD_Position(1,0);
                         LCD_PutChar(' ');
                         LCD_Position(1,6);
                         LCD_PutChar('>');
                         LCD_Position(1,11);
                         LCD_PutChar(' ');
                         break;
                 case 3: LCD_Position(1,0);
                         LCD_PutChar(' ');
                         LCD_Position(1,6);
                         LCD_PutChar(' ');
                         LCD_Position(1,11);
                         LCD_PutChar('>');
                         break;
                 default: break;
                }
                break;
        case 4: Iout=Iout-5;
                if(Iout<10)
                    Iout=10;
                else{}
                Ic = Iout;
                LCD_Position(0,3);
                sprintf(printIc,"%3d",Ic);
                LCD_PrintString(printIc);
                break;
        default: break;
    }
    PIN_DEC_ClearInterrupt();
    CyDelay(50);
}

CY_ISR(INC_INT_Handler) //Subrutina del boton INCREMENTAR del menu.
{
    switch(estadoSIS)
    {
        case 1: if(TIc_sel==15)
                    TIc_sel = 0;
                else
                    TIc_sel++;
                if(TIc>=300)
                    TIc = 150;
                else
                    TIc=TIc+10;
                LCD_Position(1,0);
                sprintf(printTIc,"%3d",TIc);
                LCD_PrintString(printTIc);
                LCD_Position(1,5);
                LCD_PrintString("us");
                break;
        case 2: F_sel++;
                if(F_sel>3)
                    F_sel=1;
                else{}
                switch(F_sel)
                {
                 case 1: LCD_Position(1,0);
                         LCD_PutChar('>');
                         LCD_Position(1,6);
                         LCD_PutChar(' ');
                         LCD_Position(1,11);
                         LCD_PutChar(' ');
                         break;
                 case 2: LCD_Position(1,0);
                         LCD_PutChar(' ');
                         LCD_Position(1,6);
                         LCD_PutChar('>');
                         LCD_Position(1,11);
                         LCD_PutChar(' ');
                         break;
                 case 3: LCD_Position(1,0);
                         LCD_PutChar(' ');
                         LCD_Position(1,6);
                         LCD_PutChar(' ');
                         LCD_Position(1,11);
                         LCD_PutChar('>');
                         break;
                 default: break;
                }
                break;
        case 4: Iout=Iout+5;
                if(Iout>255)
                    Iout=255;
                else{}
                Ic = Iout;
                LCD_Position(0,3);
                sprintf(printIc,"%3d",Ic);
                LCD_PrintString(printIc);
                break;
        default: break;
    }
    PIN_INC_ClearInterrupt();
    CyDelay(50);
}

CY_ISR(PWM_INT_Handler) //Subrutina del cambio de estado de la señal.
{
    uint32 estadoINT_PWM = 0;
    estadoINT_PWM = PWM_GetInterruptSource();
    IDAC_1_SetValue(Iout);
    switch(estadoINT_PWM)
    {
        case PWM_INTR_MASK_TC:
            AMux_DisconnectAll();
            AMux_Select(1);
            PWM_ClearInterrupt(PWM_INTR_MASK_TC);
            break;
        case PWM_INTR_MASK_CC_MATCH:
            AMux_DisconnectAll();
            AMux_Select(0);
            PWM_ClearInterrupt(PWM_INTR_MASK_CC_MATCH);
            break;
        default:
            PWM_ClearInterrupt(PWM_INTR_MASK_TC);
            PWM_ClearInterrupt(PWM_INTR_MASK_CC_MATCH);
            break;
    }
}

int main(void)
{
    CyGlobalIntEnable; 
    ACEP_INT_StartEx(ACEP_INT_Handler);
    DEC_INT_StartEx(DEC_INT_Handler);
    INC_INT_StartEx(INC_INT_Handler);
    PWM_INT_StartEx(PWM_INT_Handler);
    LCD_Start();
    PWM_Init();
    IDAC_1_Init();
    IDAC_1_SetValue(0);
    AMux_Start();
    Comp_1_Start();
    LCD_Position(0,0);
    LCD_PrintString("Presione ACEPTAR");
    LCD_Position(1,0);
    LCD_PrintString("para configurar:");
    while(1)
    {}
}
