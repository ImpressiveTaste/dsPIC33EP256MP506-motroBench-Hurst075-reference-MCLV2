/**
 *   hardware_access_functions.h
 *
 *  This module provides hardware access function support.
 *
 *  Component: HAL
 */
 
/*
 *
 * Motor Control Application Framework
 * R8/RC38 (commit 128946, build on 2025 Apr 09)
 *
 * (c) 2017 - 2023 Microchip Technology Inc. and its subsidiaries. You may use
 * this software and any derivatives exclusively with Microchip products.
 *
 * This software and any accompanying information is for suggestion only.
 * It does not modify Microchip's standard warranty for its products.
 * You agree that you are solely responsible for testing the software and
 * determining its suitability.  Microchip has no obligation to modify,
 * test, certify, or support the software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE, OR ITS INTERACTION WITH
 * MICROCHIP PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY
 * APPLICATION.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL,
 * PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF
 * ANY KIND WHATSOEVER RELATED TO THE USE OF THIS SOFTWARE, THE
 * motorBench(R) DEVELOPMENT SUITE TOOL, PARAMETERS AND GENERATED CODE,
 * HOWEVER CAUSED, BY END USERS, WHETHER MICROCHIP'S CUSTOMERS OR
 * CUSTOMER'S CUSTOMERS, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES OR THE DAMAGES ARE FORESEEABLE. TO THE
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
 * CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
 * OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
 * SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF
 * THESE TERMS.
 *
 *
 ******************************************************************************/
 
#ifndef __HAF_H
#define __HAF_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "hardware_access_functions_types.h"
#include "hardware_access_functions_params.h"
#include "../parameters/hal_params.h"
#include "adc1.h"
#include "adc_module_features.h"
#include "clock.h"
#include "interrupt_manager.h"
#include "mcaf_button1.h"
#include "mcaf_button2.h"
#include "mcaf_led1.h"
#include "mcaf_led2.h"
#include "pin_manager.h"
#include "pwm.h"
#include "pwm_module_features.h"
#include "reset.h"
#include "reset_types.h"
#include "tmr2.h"
#include "system.h"
#include "system_types.h"
#include "tmr1.h"
#include "traps.h"
#include "uart1.h"
#include "watchdog.h"
#include "qei1.h"
#include "qei_temp_hal.h"


#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif

// This is the instruction cycle frequency required for libpic30.h
#define FCY  CLOCK_InstructionFrequencyGet()

/**
  Section: Traps helper macros
 */
    
#define HAL_OSCFAIL_TRAP_FUNCTION        _OscillatorFail
#define HAL_ADDRESSERROR_TRAP_FUNCTION   _AddressError
#define HAL_STACKERROR_TRAP_FUNCTION     _StackError
#define HAL_MATHERROR_TRAP_FUNCTION      _MathError

/**
  Section: ISR helper macros
 */
    
#define HAL_ADC_ISR            _AD1Interrupt
#define HAL_DMA0_ISR            _DMA0Interrupt
#define HAL_DMA1_ISR            _DMA1Interrupt
#define HAL_PWM1_ISR            _PWM1Interrupt
#define HAL_PWM2_ISR            _PWM2Interrupt
#define HAL_UART1_RXISR         _U1RXInterrupt
#define HAL_UART1_TXISR         _U1TXInterrupt
#define HAL_UART2_RXISR         _U2RXInterrupt
#define HAL_UART2_TXISR         _U2TXInterrupt
#define HAL_PWM4_ISR            _PWM4Interrupt
#define HAL_PWM5_ISR            _PWM5Interrupt
#define HAL_TIMER1_ISR          _T1Interrupt
#define HAL_TIMER2_ISR          _T2Interrupt
#define APP_TimerCallback       TMR2_CallBack


/**
  Section: Hardware Access Functions
 */     

/**
  Sub-section: PWM Module Access Functions
*/

/**
 * Enables the PWM module.
 * Summary: Enables the whole of the PWM module.
 * @example
 * <code>
 * HAL_PWM_ModuleEnable();
 * </code>
 */
inline static void HAL_PWM_ModuleEnable(void) { PWM_Enable(); }

/**
 * Sets the period cycle for all PWM to synchronize.
 * @param period PWM period value, expressed as pwm max counts
 * @example
 * <code>
 * HAL_PWM_SetPeriodIdentical(3500);
 * </code>
 */
inline static void HAL_PWM_SetPeriodIdentical(uint16_t period)
{
    PWM_MasterPeriodSet(period);
    PWM_PeriodSet(MOTOR1_PHASE_A,period);
    PWM_PeriodSet(MOTOR1_PHASE_B,period);
    PWM_PeriodSet(MOTOR1_PHASE_C,period);
}

/**
 * Sets identical PWM deadtime values for Centeraligned PWM mode on all three phases of Motor #1.
 * @param dt PWM deadtime value
 * @example
 * <code>
 * HAL_PWM_SetDeadtimeIdentical_Motor1(140);
 * </code>
 */
inline static void HAL_PWM_SetDeadtimeIdentical_Motor1(uint16_t dt)
{
    PWM_DeadTimeSet(MOTOR1_PHASE_A,dt);
    PWM_DeadTimeSet(MOTOR1_PHASE_B,dt);
    PWM_DeadTimeSet(MOTOR1_PHASE_C,dt);
}

/**
 * Clears the PWM fault interrupt status for Motor #1.
 * @example
 * <code>
 * HAL_PWM_FaultStatus_Clear();
 * </code>
 */
inline static void HAL_PWM_FaultStatus_Clear(void)
{
    PWM_GeneratorEventStatusClear(MOTOR1_PHASE_A, PWM_GENERATOR_INTERRUPT_FAULT);
}

/**
 * Gets the status of PWM fault interrupt for Motor #1.
 * @example
 * <code>
 * HAL_PWM_FaultStatus_Get();
 * </code>
 */
inline static bool HAL_PWM_FaultStatus_Get(void)
{
    return PWM_GeneratorEventStatusGet(MOTOR1_PHASE_A,PWM_GENERATOR_INTERRUPT_FAULT);
}

/**
 * Sets up the trigger designated to initiate sampling of analog channels. The trigger is
 * set such that the sampling of motor currents occurs at the center of the low side pulse.
 * @example
 * <code>
 * HAL_PWM_SetADCTrigger();
 * </code>
 */
inline static void HAL_PWM_SetADCTrigger()
{
    PWM_SpecialEventPrimaryCompareValueSet(1);
}

/**
 * Disables PWM override on the three low-side transistors for Motor #1.
 * Summary: Disables PWM override on the three low-side transistors for Motor #1.
 * @example
 * <code>
 * HAL_PWM_LowerTransistorsOverride_Disable();
 * </code>
 */
inline static void HAL_PWM_LowerTransistorsOverride_Disable(void)
{
    PWM_OverrideLowDisable(MOTOR1_PHASE_A);
    PWM_OverrideLowDisable(MOTOR1_PHASE_B);
    PWM_OverrideLowDisable(MOTOR1_PHASE_C);
}

/**
 * Enables PWM override to state LOW on the three low-side transistors for Motor #1.
 * Summary: Enables PWM override to state LOW on the three low-side transistors for Motor #1.
 * @example
 * <code>
 * HAL_PWM_LowerTransistorsOverride_Low();
 * </code>
 */
inline static void HAL_PWM_LowerTransistorsOverride_Low(void)
{
    /* Set PWM override data to 0b00 */
    PWM_OverrideDataSet(MOTOR1_PHASE_A,0);
    PWM_OverrideDataSet(MOTOR1_PHASE_B,0);
    PWM_OverrideDataSet(MOTOR1_PHASE_C,0);
    
    /* Enable PWM override */    
    PWM_OverrideLowEnable(MOTOR1_PHASE_A);
    PWM_OverrideLowEnable(MOTOR1_PHASE_B);
    PWM_OverrideLowEnable(MOTOR1_PHASE_C);
}

    
/**
 * Disables PWM override on the three high-side transistors for Motor #1.
 * Summary: Disables PWM override on the three high-side transistors for Motor #1.
 * @example
 * <code>
 * HAL_PWM_UpperTransistorsOverride_Disable();
 * </code>
 */
inline static void HAL_PWM_UpperTransistorsOverride_Disable(void)
{
    PWM_OverrideHighDisable(MOTOR1_PHASE_A);
    PWM_OverrideHighDisable(MOTOR1_PHASE_B);
    PWM_OverrideHighDisable(MOTOR1_PHASE_C);
}

/**
 * Enables PWM override to state LOW on the three high-side transistors for Motor #1.
 * Summary: Enables PWM override to state LOW on the three high-side transistors for Motor #1.
 * @example
 * <code>
 * HAL_PWM_UpperTransistorsOverride_Low();
 * </code>
 */
inline static void HAL_PWM_UpperTransistorsOverride_Low(void)
{
    /* Set PWM override data to 0b00 */
    PWM_OverrideDataSet(MOTOR1_PHASE_A,0);
    PWM_OverrideDataSet(MOTOR1_PHASE_B,0);
    PWM_OverrideDataSet(MOTOR1_PHASE_C,0);

    /* Enable PWM override */
    PWM_OverrideHighEnable(MOTOR1_PHASE_A);
    PWM_OverrideHighEnable(MOTOR1_PHASE_B);
    PWM_OverrideHighEnable(MOTOR1_PHASE_C);
}

/**
 * Sets identical duty cycle values on three phases of Motor #1.
 * Summary: Sets identical duty cycle values on three phases of Motor #1.
 * @param dc Duty cycle value
 * @example
 * <code>
 * HAL_PWM_DutyCycle_SetIdentical(500);
 * </code>
 */
inline static void HAL_PWM_DutyCycle_SetIdentical(uint16_t dc)
{
    PWM_DutyCycleSet(MOTOR1_PHASE_A,dc);
    PWM_DutyCycleSet(MOTOR1_PHASE_B,dc);
    PWM_DutyCycleSet(MOTOR1_PHASE_C,dc);
}

/**
 * Writes three unique duty cycle values to the PWM duty cycle registers
 * corresponding to Motor #1.
 * Summary: Writes to the PWM duty cycle registers corresponding to Motor #1.
 * @param pdc Pointer to the array that holds duty cycle values
 * @example
 * <code>
 * HAL_PWM_DutyCycleRegister_Set(&pdcMotor1);
 * </code>
 */
inline static void HAL_PWM_DutyCycleRegister_Set(const uint16_t *pdc)
{
    PWM_DutyCycleSet(MOTOR1_PHASE_A,pdc[0]);
    PWM_DutyCycleSet(MOTOR1_PHASE_B,pdc[1]);
    PWM_DutyCycleSet(MOTOR1_PHASE_C,pdc[2]);
}

/**
 * Writes three unique phase values to the PWM phase registers
 * corresponding to Motor #1.
 * Summary: Writes to the PWM phase registers corresponding to Motor #1.
 * @param phase Pointer to the array that holds phase values
 * @example
 * <code>
 * HAL_PWM_PhaseRegister_Set(&phaseMotor1);
 * </code>
 */
inline static void HAL_PWM_PhaseRegister_Set(const uint16_t *phase)
{
    // not supported in 33EP PWM
}

/**
 * Writes three unique duty cycle values to both halves of the PWM duty cycles corresponding to Motor #1.
 * Summary: Writes to both halves of the PWM duty cycles corresponding to Motor #1.
 * @param pdc Pointer to the array that holds duty cycle values
 * @example
 * <code>
 * HAL_PWM_DutyCycle_Set(*pdc);
 * </code>
 */
inline static void HAL_PWM_DutyCycle_Set(const uint16_t *pdc)
{
    HAL_PWM_DutyCycleRegister_Set(pdc);
}

/**
 * Writes six unique duty cycle values to the first half and second half of PWM duty cycles
 * corresponding to Motor #1.
 * Summary: Writes to the first-half and second-half of PWM duty cycles corresponding to Motor #1.
 * @param firstHalf Pointer to the array that holds information to set the first half of PWM duty cycle.
 * @param secondHalf Pointer to the array that holds information to set the second half of PWM duty cycle.
 * @example
 * <code>
 * HAL_PWM_DutyCycleDualEdge_Set(&firstHalf, &secondHalf);
 * </code>
 */
inline static void HAL_PWM_DutyCycleDualEdge_Set(const uint16_t *firstHalf, const uint16_t *secondHalf)
{
    // not supported in 33EP PWM
}

/**
* Begins the PWM fault clearing process for all PWM instances 
* Summary: Begins fault clearing process.
* <code>
* HAL_PWM_FaultClearBegin();
* </code>
*/
inline static void HAL_PWM_FaultClearBegin(void)
{
    #if (PWM_FAULT_LATCH_SOFTWARE_CLEAR_FEATURE_AVAILABLE)
    {
        PWM_FaultModeLatchClear(MOTOR1_PHASE_A);
        PWM_FaultModeLatchClear(MOTOR1_PHASE_B);
        PWM_FaultModeLatchClear(MOTOR1_PHASE_C);
    }
    #else
    {
        PWM_FaultModeLatchDisable(MOTOR1_PHASE_A);
        PWM_FaultModeLatchDisable(MOTOR1_PHASE_B);
        PWM_FaultModeLatchDisable(MOTOR1_PHASE_C);
    }
    #endif
}

/**
* Ends the PWM fault clearing process for all PWM instances 
* Summary: Ends fault clearing process.
* <code>
* HAL_PWM_FaultClearEnd();
* </code>
*/
inline static void HAL_PWM_FaultClearEnd(void)
{
    #if (PWM_FAULT_LATCH_SOFTWARE_CLEAR_FEATURE_AVAILABLE)
    {
        ; // no action required
    }
    #else
    {
        PWM_FaultModeLatchEnable(MOTOR1_PHASE_A);
        PWM_FaultModeLatchEnable(MOTOR1_PHASE_B);
        PWM_FaultModeLatchEnable(MOTOR1_PHASE_C);
    }
    #endif
}


/**
 * Maintains the Motor #1 low-side transistors at the requested duty cycle while
 * keeping high-side transistors OFF.
 * Summary: Maintains the Motor #1 PWM outputs to an idle state with minimal impact to the motor.
 * @param pwmPeriodCount PWM period count
 * @param dc Duty cycle value for the low-side transistors
 * @example
 * <code>
 * HAL_PWM_LowerTransistorsDutyCycle_Set(3500,220);
 * </code>
 */
inline static void HAL_PWM_LowerTransistorsDutyCycle_Set(uint16_t pwmPeriodCount, uint16_t dc)
{
    HAL_PWM_UpperTransistorsOverride_Low();

    uint16_t dutyCycleLowSide = pwmPeriodCount;
    dutyCycleLowSide -= dc;

    HAL_PWM_DutyCycle_SetIdentical(dutyCycleLowSide);
}

/**
 * Disable the PWM channels assigned for Motor #1 by overriding them to low state.
 * Summary: Disable the PWM channels assigned for Motor #1 by overriding them to low state.
 * @example
 * <code>
 * HAL_PWM_Outputs_Disable();
 * </code>
 */
inline static void HAL_PWM_Outputs_Disable(void)
{
    PWM_OverrideDataSet(MOTOR1_PHASE_A,0);
    PWM_OverrideDataSet(MOTOR1_PHASE_B,0);
    PWM_OverrideDataSet(MOTOR1_PHASE_C,0);   
    
    PWM_OverrideHighEnable(MOTOR1_PHASE_A);
    PWM_OverrideLowEnable(MOTOR1_PHASE_A);    
    PWM_OverrideHighEnable(MOTOR1_PHASE_B);
    PWM_OverrideLowEnable(MOTOR1_PHASE_B);    
    PWM_OverrideHighEnable(MOTOR1_PHASE_C);
    PWM_OverrideLowEnable(MOTOR1_PHASE_C);    
}

/**
 * Disable the PWM channels assigned for Phase-A of Motor #1 by overriding them to low state.
 * Summary: Disable the PWM channels assigned for Phase-A of Motor #1 by overriding them to low state.
 * @example
 * <code>
 * HAL_PWM_PhaseAOutput_Disable();
 * </code>
 */
inline static void HAL_PWM_PhaseAOutput_Disable(void)
{
    PWM_OverrideDataSet(MOTOR1_PHASE_A,0);  
    
    PWM_OverrideHighEnable(MOTOR1_PHASE_A);
    PWM_OverrideLowEnable(MOTOR1_PHASE_A);
}

/**
 * Enable the PWM channels assigned for Phase-A of Motor #1.
 * Summary: Enable the PWM channels assigned for Phase-A of Motor #1.
 * @example
 * <code>
 * HAL_PWM_PhaseAOutput_Enable();
 * </code>
 */
inline static void HAL_PWM_PhaseAOutput_Enable(void)
{
    PWM_OverrideHighDisable(MOTOR1_PHASE_A);
    PWM_OverrideLowDisable(MOTOR1_PHASE_A);
}

/**
 * Disable the PWM channels assigned for Phase-B of Motor #1 by overriding them to low state.
 * Summary: Disable the PWM channels assigned for Phase-B of Motor #1 by overriding them to low state.
 * @example
 * <code>
 * HAL_PWM_PhaseBOutput_Disable();
 * </code>
 */
inline static void HAL_PWM_PhaseBOutput_Disable(void)
{
    PWM_OverrideDataSet(MOTOR1_PHASE_B,0);
    
    PWM_OverrideHighEnable(MOTOR1_PHASE_B);
    PWM_OverrideLowEnable(MOTOR1_PHASE_B);
}

/**
 * Enable the PWM channels assigned for Phase-B of Motor #1.
 * Summary: Enable the PWM channels assigned for Phase-B of Motor #1.
 * @example
 * <code>
 * HAL_PWM_PhaseBOutput_Enable();
 * </code>
 */
inline static void HAL_PWM_PhaseBOutput_Enable(void)
{
    PWM_OverrideHighDisable(MOTOR1_PHASE_B);
    PWM_OverrideLowDisable(MOTOR1_PHASE_B);
}

/**
 * Disable the PWM channels assigned for Phase-C of Motor #1 by overriding them to low state.
 * Summary: Disable the PWM channels assigned for Phase-C of Motor #1 by overriding them to low state.
 * @example
 * <code>
 * HAL_PWM_PhaseCOutput_Disable();
 * </code>
 */
inline static void HAL_PWM_PhaseCOutput_Disable(void)
{
    PWM_OverrideDataSet(MOTOR1_PHASE_C,0);
    
    PWM_OverrideHighEnable(MOTOR1_PHASE_C);
    PWM_OverrideLowEnable(MOTOR1_PHASE_C);
}

/**
 * Enable the PWM channels assigned for Phase-C of Motor #1.
 * Summary: Enable the PWM channels assigned for Phase-C of Motor #1.
 * @example
 * <code>
 * HAL_PWM_PhaseCOutput_Enable();
 * </code>
 */
inline static void HAL_PWM_PhaseCOutput_Enable(void)
{
    PWM_OverrideHighDisable(MOTOR1_PHASE_C);
    PWM_OverrideLowDisable(MOTOR1_PHASE_C);
}

/**
 * Enables the PWM channels assigned for Motor #1 by disabling the PWM override function.
 * Summary: Enables the PWM channels assigned for Motor #1 by disabling the PWM override function.
 * @example
 * <code>
 * HAL_PWM_Outputs_Enable();
 * </code>
 */
inline static void HAL_PWM_Outputs_Enable(void)
{
    PWM_OverrideHighDisable(MOTOR1_PHASE_A);
    PWM_OverrideLowDisable(MOTOR1_PHASE_A);

    PWM_OverrideHighDisable(MOTOR1_PHASE_B);
    PWM_OverrideLowDisable(MOTOR1_PHASE_B);
    
    PWM_OverrideHighDisable(MOTOR1_PHASE_C);
    PWM_OverrideLowDisable(MOTOR1_PHASE_C);
}

/**
  Sub-section: GPIO Module Access Functions
*/

void HAL_Initialize(void);

/**
 * This function is generated and returns whether or not a development board has two buttons.
 * @return true = two buttons are present, false = two buttons are not present
 */
inline static bool HAL_hasTwoButtons(void)
{
    return true;
}

/**
 * Activates LED-GP1.
 * Summary: Activates LED-GP1.
 * @example
 * <code>
 * HAL_LedGp1_Activate();
 * </code>
 */
inline static void HAL_LedGp1_Activate(void) { MCAF_LED1_On(); }

/**
 * Deactivates LED-GP1.
 * Summary: Deactivates LED-GP1.
 * @example
 * <code>
 * HAL_LedGp1_Deactivate();
 * </code>
 */
inline static void HAL_LedGp1_Deactivate(void) { MCAF_LED1_Off(); }

/**
 * Activates LED-GP2.
 * Summary: Activates LED-GP2.
 * @example
 * <code>
 * HAL_LedGp2_Activate();
 * </code>
 */
inline static void HAL_LedGp2_Activate(void) { MCAF_LED2_On(); }

/**
 * Deactivates LED-GP2.
 * Summary: Deactivates LED-GP2.
 * @example
 * <code>
 * HAL_LedGp2_Deactivate();
 * </code>
 */
inline static void HAL_LedGp2_Deactivate(void) { MCAF_LED2_Off(); }

/**
 * Activates Testpoint-GP1.
 * Summary: Activates Testpoint-GP1.
 * @example
 * <code>
 * HAL_TestpointGp1_Activate();
 * </code>
 */
inline static void HAL_TestpointGp1_Activate(void) { MCAF_TESTPOINT1_SetHigh(); }

/**
 * Deactivates Testpoint-GP1.
 * Summary: Deactivates Testpoint-GP1.
 * @example
 * <code>
 * HAL_TestpointGp1_Deactivate();
 * </code>
 */
inline static void HAL_TestpointGp1_Deactivate(void) { MCAF_TESTPOINT1_SetLow(); }

/**
 * Get the raw GPIO input from button1.
 * @return bool raw GPIO state where true = button is pressed, false = button is not pressed
 */
inline static bool HAL_ButtonGp1RawInput(void) { return MCAF_BUTTON1_IsPressed(); }

/**
 * Get the raw GPIO input from button2.
 * @return bool raw GPIO state where true = button is pressed, false = button is not pressed
 */
inline static bool HAL_ButtonGp2RawInput(void) { return MCAF_BUTTON2_IsPressed(); }

/**
  Sub-section: ADC Module Access Functions
*/

/**
 * This function is only generated for dsPIC33EP to decide 
 * whether to start sensing DClink voltage or potentiomer first.
 */
inline static void HAL_ADC_SelectionInit(volatile HAL_DATA_T* halData)
{
    halData->adcSelect = HADC_VDC;
}

/**
 * This routine is a call back function to be called every ADC ISR.
 */
void HAL_ADC_StepIsrCallback(void);

/**
 * This function is executed every ADC ISR and updates 
 * the selection for the shared core ADC (for further details please refer to MCAF User's Guide).
 * @param halData pointer to hal data structure which stores the adc core selection. 
 */
inline static void HAL_ADC_StepIsr(volatile HAL_DATA_T* halData)
{
    if(halData->adcSelect == HADC_POTENTIOMETER)
    {
        halData->adcInputs.potentiometer = ADC1_ConversionResultGet(MCAF_ADC_POTENTIOMETER);
        ADC1_ChannelSelect(MCAF_ADC_DCLINK_VOLTAGE);
        halData->adcSelect = HADC_VDC;
    }
    else
    {
        halData->adcInputs.vDC = ADC1_ConversionResultGet(MCAF_ADC_DCLINK_VOLTAGE);
        ADC1_ChannelSelect(MCAF_ADC_POTENTIOMETER);
        halData->adcSelect = HADC_POTENTIOMETER;
    }
}

/**
 * Get the ADC channel number corresponding to the potentiometer analog input for motor #1.
 * @return ADC channel number
 */
inline static uint16_t HAL_ADC_ChannelPotentiometer(void) { return MCAF_ADC_POTENTIOMETER; }

/**
 * Get the ADC channel number corresponding to the DC link voltage sense analog input for motor #1.
 * @return ADC channel number
 */
inline static uint16_t HAL_ADC_ChannelDclink(void) { return MCAF_ADC_DCLINK_VOLTAGE; }

/**
 * Get the ADC channel number corresponding to phase current A analog input for motor #1.
 * @return ADC channel number
 */
inline static uint16_t HAL_ADC_ChannelPhaseACurrent(void) { return MCAF_ADC_PHASEA_CURRENT; }

/**
 * Get the ADC channel number corresponding to phase current B analog input for motor #1.
 * @return ADC channel number
 */
inline static uint16_t HAL_ADC_ChannelPhaseBCurrent(void) { return MCAF_ADC_PHASEB_CURRENT; }

/**
 * Get the ADC result corresponding to phase current A analog input for motor #1.
 * @return ADC result value
 */
inline static uint16_t HAL_ADC_ValuePhaseACurrent(void) { return ADC1_ConversionResultGet(MCAF_ADC_PHASEA_CURRENT); }

/**
 * Get the ADC result corresponding to phase current B analog input for motor #1.
 * @return ADC result value
 */
inline static uint16_t HAL_ADC_ValuePhaseBCurrent(void) { return ADC1_ConversionResultGet(MCAF_ADC_PHASEB_CURRENT); }

/**
 * Get the ADC result corresponding to phase current C analog input for motor #1.
 * @return ADC result value
 */
inline static uint16_t HAL_ADC_ValuePhaseCCurrent(void) { return 0; }

/**
 * Is the phase C current available?
 * @return whether phase C is available
 */
inline static bool HAL_ADC_IsPhaseCCurrentAvailable(void)
{
    return false;
}

extern volatile HAL_DATA_T halData;

/**
 * Get the ADC result corresponding to potentiometer analog input for motor #1.
 * @return ADC result value
 */
inline static uint16_t HAL_ADC_ValuePotentiometer(void) 
{ 
    return halData.adcInputs.potentiometer; 
}

/**
 * Get the ADC result corresponding to DC link voltage sense analog input for motor #1.
 * @return ADC result value
 */
inline static uint16_t HAL_ADC_ValueDCLinkVoltage(void)
{ 
    return halData.adcInputs.vDC; 
}

/**
 * Get the ADC result corresponding to power semiconductor bridge temperature sensor, if available
 * @return ADC result value
 */
inline static uint16_t HAL_ADC_ValueBridgeTemperature(void) { 
    return 0;
}

/**
 * Is the power semiconductor bridge temperature sensor available?
 * @return whether power semiconductor bridge temperature sensor is available
 */
inline static bool HAL_ADC_IsBridgeTemperatureAvailable(void)
{
    return false;
}

/**
 * Get the ADC result corresponding to absolute reference voltage, if available
 * @return ADC result value
 */
inline static uint16_t HAL_ADC_ValueAbsoluteReferenceVoltage(void) { 
    return 0;
}

/**
 * Is the absolute reference voltage available?
 * @return whether absolute reference voltage is available
 */
inline static bool HAL_ADC_IsAbsoluteReferenceVoltageAvailable(void)
{
    return false;
}

/**
* Enables the ADC module.
* Summary: Enables the whole of the ADC module.
* @example
* <code>
* HAL_ADC_Enable();
* </code>
*/
inline static void HAL_ADC_Enable(void) { ADC1_Enable(); }

/**
* Clears the ADC interrupt flag.
* @example
* <code>
* HAL_ADC_InterruptFlag_Clear();
* </code>
*/
inline static void HAL_ADC_InterruptFlag_Clear(void) 
{ 
    #if (ADC_INDIVIDUAL_CHANNEL_INTERRUPT_FEATURE_AVAILABLE)
        // In order to clear the ADC ISR flag one must read the associated
        // ADC buffer. This dummy read is to ensure the ISR flag will be cleared.
        ADC1_ConversionResultGet(MCAF_ADC_POTENTIOMETER);
        ADC1_IndividualChannelInterruptFlagClear(MCAF_ADC_POTENTIOMETER);
    #else
        ADC1_InterruptFlagClear();   
    #endif
}

/**
* Enables the ADC interrupt flag.
* @example
* <code>
* HAL_ADC_Interrupt_Enable();
* </code>
*/
inline static void HAL_ADC_Interrupt_Enable(void) 
{     
    #if (ADC_INDIVIDUAL_CHANNEL_INTERRUPT_FEATURE_AVAILABLE)
        ADC1_IndividualChannelInterruptEnable(MCAF_ADC_POTENTIOMETER);
    #else
        ADC1_InterruptEnable(); 
    #endif
}

/**
 * Sets the ADC interrupt priority value.
 * Note: This is a dummy function, EP devices are not supported by Melody.
 */
inline static void HAL_ADC_IndividualChannelInterruptPrioritySet(void) {}

/**
 * Converts a signed input to an unsigned value.
 * Adding 0x8000 to input maps -32k to 32k -> 0 to 65k.
 * @param input input to be converted to unsigned value
 * @return unsigned value
*/
inline static int16_t HAL_ADC_UnsignedFromSignedInput(int16_t input) { return input + 0x8000; }

/**
  Sub-section: Interrupt Module Access Functions
*/

/**
* Returns the interrupt vector number.
* @example
* <code>
* vecNum = HAL_InterruptVector_Get();
* </code>
*/
inline static uint16_t HAL_InterruptVector_Get(void) { return _VECNUM; }

/**
  Sub-section: DMA Module Access Functions
*/

/**
 * Handles the DMA Error trap and returns whether or not it was properly handled
 * @return true = DMA Error was handled, false = DMA Error was not handled
 */
bool HAL_DMA_ErrorHandler(void);

/**
  Sub-section: UART Module Access Functions
*/

/**
* Initializes the UART module
*/
inline static void HAL_UART_Initialize(void) { UART1_Initialize(); }

/**
 * Writes data to the UART tx buffer
 * @param data data to be written to the buffer
 */
inline static void HAL_UART_Write(uint8_t data) { UART1_Write(data); }

/**
 * Reads data from the UART rx buffer
 * @return data received from the UART rx buffer
 */
inline static uint8_t HAL_UART_Read(void) { return UART1_Read(); }

/**
 * States whether or not the UART rx buffer contains data
 * @return true = UART rx buffer has data false = UART rx buffer does not have data
 */
inline static bool HAL_UART_IsRxReady(void) { return UART1_IsRxReady(); }

/**
 * States whether or not the UART tx buffer is ready for more data
 * @return true = UART tx buffer can accept more data false = UART tx buffer can not accept more data
 */
inline static bool HAL_UART_IsTxReady(void) { return UART1_IsTxReady(); }


/**
  Sub-section: Watchdog Module Access Functions
*/

/**
* Clears the Watchdog timer
*/
inline static void HAL_WATCHDOG_Timer_Clear(void) { WATCHDOG_TimerClear(); }

/**
* Enables the Watchdog timer
*/
inline static void HAL_WATCHDOG_Timer_Enable(void) { WATCHDOG_TimerSoftwareEnable(); }

/**
  Sub-section: CORCON Module Access Functions
*/

/**
 * Gets the CORCON register value
 * @return CORCON register value
 */
inline static uint16_t HAL_CORCON_RegisterValue_Get(void) { return SYSTEM_CORCONRegisterValueGet(); }

/**
 * Sets the value of the CORCON register
 * @param reg_value register value to be set for the CORCON register
 */
inline static void HAL_CORCON_RegisterValue_Set(uint16_t reg_value) { SYSTEM_CORCONRegisterValueSet(reg_value); }

/**
* Initializes the CORCON module
*/
inline static void HAL_CORCON_Initialize(void) { SYSTEM_CORCONModeOperatingSet(CORCON_MODE_ENABLEALLSATNORMAL_ROUNDBIASED); }

/**
  Sub-section: TMR Module Access Functions
*/

/**
* Starts the profiling timer used to time the various operations
*/
inline static void HAL_ProfilingCounter_Start(void) { TMR1_Start(); }

/**
 * Gets the timer value of the profiling timer
 * @return profiling timer counter value
 */
inline static uint16_t HAL_ProfilingCounter_Get(void) { return TMR1_Counter16BitGet(); }

/**
 * Sets the MC_TMR_TICK interrupt priority value.
 * Note: This is a dummy function, EP devices are not supported by Melody.
 */
inline static void HAL_TMR_TICK_InterruptPrioritySet(void) {}

/**
 * Overrides the default callback function for the application timer
 * interrupt.
 * Note: This is a dummy function, EP devices are not supported by Melody.
 * @param callback function handle
 */
inline static void HAL_TMR_TICK_SetCallbackFunction(void (*handler)(void)) {}

/**
 * Starts the application timer.
 */
inline static void HAL_TMR_TICK_Start(void) { TMR2_Start(); }

/**
  Sub-section: QEI Module Access Functions
*/

/**
* Initializes the QEI module
*/
inline static void HAL_QEI_Initialize(void) { QEI1_Initialize(); }

/**
* Initializes the QEI position capture mode. This is only used
* when an encoder index signal is present. 
*/
inline static void HAL_QEI_PositionCaptureInit(void)
{
    QEI_FreeRunningCounterModeSet();
    QEI_PositionCaptureEventEnable();
    QEI_PositionCaptureInit();
}

/**
 * Sets the QEI module range between 0 and counts_per_rev - 1.
 */
inline static void HAL_QEI_CountsPerRevolutionSet(uint16_t counts_per_rev) { QEI1_ModuloMode16bitSet(counts_per_rev); }

/**
 * Enables the QEI module.
 */
inline static void HAL_QEI_Enable(void) { QEI1_ModuleEnable(); }

/**
 * Reads the QEI position count.
 * @return position count value
 */
inline static uint16_t HAL_QEI_PositionCountGet(void) { return QEI1_PositionCount16bitRead(); }

/**
 * Reads the QEI position capture value. Position capture value is the value of the position 
 * when an index pulse is detected.
 * @return position capture value
 */
inline static uint16_t HAL_QEI_PositionCaptureGet(void) { return QEI_PositionCaptureGet(); }

/**
 * Selects input voltage range for all op-amps.
 * Note: This is a dummy function, EP devices do not have this
 * feature.
 */
inline static void HAL_OpAmpsInputVoltageRangeSelect(void) {}

/**
 * Enables all op-amps
 */
inline static void HAL_OpAmpsEnable(void) {
}

/**
  Sub-section: CMP/DAC Module Access Functions
*/

/**
 * Sets the DAC data value.
 * Note: This is a dummy function, no action required on EP devices.
 */
inline static void HAL_CMP_SetComparatorOvercurrentThreshold(const uint16_t dacValue) {}

/**
 * Initializes remaining ADC signals
 */
inline static void HAL_ADC_SignalsInit(void) {
}

/**
 * Initializes ADC resolution
 */
inline static void HAL_ADC_ResolutionInit(void) {
}

/** Set PWM mode to center-aligned single update */
inline static void HAL_PWM_ModeSingleUpdate(void)
{
    // not supported in 33EP PWM
}

/** Set PWM mode to center-aligned double update */
inline static void HAL_PWM_ModeDoubleUpdate(void)
{
    // not supported in 33EP PWM
}

/** Enable PWM phase control from master(common) register*/
inline static void HAL_PWM_SelectMasterPhase(void)
{
    // not supported in 33EP PWM
}

/** Enable PWM phase control from local(independent) register */
inline static void HAL_PWM_SelectLocalPhase(void)
{
    // not supported in 33EP PWM
}

/** Set PWM mode to dual edge center-aligned updated once per cycle*/
inline static void HAL_PWM_ModeDualEdgeSingleUpdate(void)
{
    // not supported in 33EP PWM
}

/** Enable ADC Trigger 1 for compare event with PGxTRIGA */
inline static void HAL_PWM_ADCTrigger1AEnable(void)
{
    // not supported in 33EP PWM
}

/** Enable ADC Trigger 2 for compare event with PGxTRIGB */
inline static void HAL_PWM_ADCTrigger2BEnable(void)
{
    // not supported in 33EP PWM
}

/** Set Priority for Bus Current AN Interrupt */
inline static void HAL_ADC_BusCurrentInterruptPrioritySet(void)
{
    // not supported in 33EP PWM
}

/** Enable ADC Trigger 2 for compare event with PGxTRIGC */
inline static void HAL_PWM_ADCTrigger2CEnable(void)
{
    // not supported in 33EP PWM
}

/**
* Re-configures UART IO
* <code>
* HAL_UART_ReconfigureIoMapping();
* </code>
*/
inline static void HAL_UART_ReconfigureIoMapping(void)
{
    // no action required
}

/**
 * Set all interrupt priorities.
 * Note: This is a dummy function, no action required on EP devices.
 */
inline static void HAL_InterruptPrioritySet(void) {}


#ifdef __cplusplus
}
#endif

#endif /* __HAF_H */
