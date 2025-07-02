/**
 * Simplified example enabling PWM1 and blinking the debug LED.
 *
 * Device : dsPIC33EP256MC506
 * Compiler : XC16 v2.10
 * Generator : MCC 1.171.5
 */

#define FCY 70000000UL          // necessario prima di <libpic30.h>
#include <libpic30.h>           // __delay_ms()

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pwm.h"
#include "mcc_generated_files/pin_manager.h"

/*?????????????????????????????
 *  Parametri PWM LED
 *????????????????????????????*/
#define PWM_PRESCALE            64U      // deve corrispondere a MCC (1:64)
#define CARRIER_HZ            1000U      // ?1 kHz ? niente sfarfallio
static uint16_t perCounts;               // periodo pre-calcolato

/* Enable PWM1 with ~1 kHz carrier and 50% duty cycle */
static void APP_PWM_Initialize(void)
{
    /* Calcola il periodo per ~1 kHz */
    perCounts = (uint16_t)((FCY / (PWM_PRESCALE * CARRIER_HZ)) - 1U);
    PTCON2bits.PCLKDIV = 6;             // 1:64 prescaler
    PWM_MasterPeriodSet(perCounts);     // match master time base

    /* Carica periodo e duty al 50% */
    PWM_PeriodSet   (PWM_GENERATOR_1, perCounts);
    PWM_DutyCycleSet(PWM_GENERATOR_1, perCounts / 2U);

    /* Rilascia i pin dal controllo software */
    PWM_OverrideHighDisable(PWM_GENERATOR_1);
    PWM_OverrideLowDisable (PWM_GENERATOR_1);

    /* Abilita il modulo PWM */
    PWM_Enable();
}

int main(void)
{
    SYSTEM_Initialize();        // clock, pin e driver MCC
    APP_PWM_Initialize();       // attiva PWM1

    while (1)
    {
        DBG_LED1_Toggle();
        __delay_ms(500);       // lampeggio LED
    }
    return 1;
}
