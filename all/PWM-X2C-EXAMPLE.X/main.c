/**
  main.c ? versione ?funzionale?: accende il LED collegato a PWM 1 e lo fa
  respirare a 1 Hz.

  Dispositivo : dsPIC33EP256MC506
  Compilatore : XC16 v2.10
  Generatore  : MCC 1.171.5 (base) + patch manuale sottostante
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
#define RAMP_STEPS             100U      // risoluzione sfumatura
#define BREATH_HZ                1U      // ciclo completo 1 s (1 Hz)
#define STEP_DELAY_MS (1000U / (2U * RAMP_STEPS * BREATH_HZ))

#define BLINK_PERIOD_MS         500U
#define BLINK_COUNT_MAX (BLINK_PERIOD_MS / STEP_DELAY_MS)

static uint16_t perCounts;               // periodo pre-calcolato

/*?????????????????????????????
 *  Abilitazione PWM 1
 *????????????????????????????*/
static void APP_PWM_Initialize(void)
{
    /* 1. Periodo per ~1 kHz */
    perCounts = (uint16_t)((FCY / (PWM_PRESCALE * CARRIER_HZ)) - 1U);
    PTCON2bits.PCLKDIV = 6;             // 1:64 prescaler
    PWM_MasterPeriodSet(perCounts);     // match master time base

    /* 2. Carico periodo e duty iniziale (0 %) */
    PWM_PeriodSet   (PWM_GENERATOR_1, perCounts);      // PHASE1
    PWM_DutyCycleSet(PWM_GENERATOR_1, 0U);             // PDC1

    /* 3. Disattivo override (i pin escono dallo stato high-Z) */
    PWM_OverrideHighDisable(PWM_GENERATOR_1);
    PWM_OverrideLowDisable (PWM_GENERATOR_1);

    /* 4. Abilito il modulo PWM globale (PTEN = 1)   */
    PWM_Enable();
}

/*?????????????????????????????
 *  Aggiornamento duty-cycle a
 *  triangolo (LED ?breathe?)
 *????????????????????????????*/
static void APP_BreatheUpdate(void)
{
    static uint16_t idx = 0;    // 0 ? RAMP_STEPS
    static int8_t   dir = 1;    // +1 salita, ?1 discesa

    uint16_t dc = (uint16_t)(((uint32_t)(perCounts + 1U) * idx) / RAMP_STEPS);
    PWM_DutyCycleSet(PWM_GENERATOR_1, dc);

    idx += dir;
    if (idx >= RAMP_STEPS) { idx = RAMP_STEPS; dir = -1; }
    else if (idx == 0U)    { dir =  1; }

    __delay_ms(STEP_DELAY_MS);
}

/*?????????????????????????????
 *  Aggiornamento lampeggio
 *  LED di debug (DBG_LED1)
 *????????????????????????????*/
static void APP_BlinkUpdate(void)
{
    static uint16_t count = 0;
    if (++count >= BLINK_COUNT_MAX)
    {
        count = 0;
        DBG_LED1_Toggle();
    }
}

/*?????????????????????????????
 *  Main application
 *????????????????????????????*/
int main(void)
{
    SYSTEM_Initialize();        // clock, pin, MCC driver
    APP_PWM_Initialize();       // patch PWM LED

    while (1)
    {
        /*
         * Simple duty-cycle toggle to verify PWM operation.
         * The duty is set to 100% for half a second and then
         * forced to 0% for another half second.
         */
        PWM_DutyCycleSet(PWM_GENERATOR_1, perCounts);
        __delay_ms(500);
        PWM_DutyCycleSet(PWM_GENERATOR_1, 0U);
        __delay_ms(500);

        APP_BlinkUpdate();      // lampeggio LED1
    }

    /* Non si raggiunge mai */
}
