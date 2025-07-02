/**
  @File Name:
    qei1.h

  @Summary:
    This module provides peripheral drivers for QEI1.

  @Description:
    This module provides peripheral drivers for QEI1.
 */
/* ********************************************************************
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
* *****************************************************************************/

#ifndef _QEI1_H
#define _QEI1_H

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif

/**
  Section: Driver Interface
 */
    
/**
 * Disables the QEI1 module.
 * Summary: Disables the QEI1 module.
 * @example
 * <code>
 * QEI1_ModuleDisable();
 * </code>
 */
inline static void QEI1_ModuleDisable(void)
{
    QEI1CONbits.QEIEN = 0;        // Disable QEI module
}
    
/**
 * Enables the QEI1 module.
 * Summary: Enables the QEI1 module.
 * @example
 * <code>
 * QEI1_ModuleEnable();
 * </code>
 */
inline static void QEI1_ModuleEnable(void)
{
    QEI1CONbits.QEIEN = 1;        // Enable QEI module
}

/**
 * Writes the requested 16-bit position count value into the QEI1 position count register. If the
 * QEI1 module has a 32-bit position count register, the upper 16 bits will be written as 0.
 * Summary: Writes the requested 16-bit position count value into the QEI1 position count register.
 * @param positionCount 16-bit position count value
 * @example
 * <code>
 * QEI1_PositionCount16bitWrite(0x0040);
 * </code>
 */
inline static void QEI1_PositionCount16bitWrite(uint16_t positionCount)
{
    POS1HLD = 0;
    POS1CNTL = positionCount;
}

/**
 * Writes the requested position count value into the QEI1 position count register.
 * Summary: Writes the requested position count value into the QEI1 position count register.
 * @param positionCount 32-bit position count value
 * @example
 * <code>
 * QEI1_PositionCountWrite(0x0F560040);
 * </code>
 */
inline static void QEI1_PositionCountWrite(uint32_t positionCount)
{
    uint32_t positionCountHigh = positionCount & 0xffff0000;
    positionCountHigh = positionCountHigh >> 16;
    POS1HLD = (uint16_t)positionCountHigh;
    POS1CNTL = (uint16_t)positionCount;
}

/**
 * Reads the QEI1 position count register as a 32-bit value. If the QEI position count
 * is a 16-bit value, the upper 16 bits will read as 0.
 * Summary: Reads the 32-bit position count value from the QEI1 position count register.
 * @return 32-bit position count register value
 * @example
 * <code>
 * qeiPosCountValue32 = QEI1_PositionCountRead();
 * </code>
 */
inline static uint32_t QEI1_PositionCountRead(void)
{
    uint16_t positionCountLow;
    uint16_t positionCountHigh;
    uint32_t positionCount;
    positionCountLow = POS1CNTL;
    positionCountHigh = POS1HLD;
    positionCount = positionCountHigh;
    positionCount = positionCount << 16;
    positionCount = positionCount | positionCountLow;
    
    return positionCount;
}

/**
 * Reads the QEI1 position count register as a 16-bit value. If the QEI position count is
 * a 32-bit value, the value returned will be the least significant bits of the position count.
 * Summary: Reads the 16-bit position count value from the QEI1 position count register.
 * @return 16-bit position count register value
 * @example
 * <code>
 * qeiPosCountValue16 = QEI1_PositionCount16bitRead();
 * </code>
 */
inline static uint16_t QEI1_PositionCount16bitRead(void)
{    
    return POS1CNTL;
}

/**
 * Sets the modulo count with a 16-bit value when QEI1 is configured to operate
 * in Modulo Count Mode. The upper 16-bits of the module count register is set to 0.
 * Summary: Sets the modulo count with a 16-bit value when QEI1 is configured to
 * operate in Modulo Count Mode.
 * @param modulus number of counts per wraparound
 * @example
 * <code>
 * QEI1_ModuloMode16bitSet(512);
 * </code>
 */
inline static void QEI1_ModuloMode16bitSet(uint16_t modulus)
{
    QEI1LECL = 0;
    QEI1LECH = 0;
    QEI1GECL = modulus - 1;
    QEI1GECH = 0;
}

/**
 * Gets the status of QEI input phase swap configuration.
 * @return boolean flag corresponding to the QEI input phase swap configuration
 * @example
 * <code>
 * if (QEI1_PhaseInputSwappedGet())
 * {
 *    // do something
 * }
 * </code>
 */
inline static bool QEI1_PhaseInputSwappedGet(void)
{
    return QEI1IOCbits.SWPAB;
}

/**
 * Sets the QEI phase inputs swapping configuration as swapped or not swapped.
 * @param swapEnabled boolean input if QEAx and QEBx need to be swapped prior to quadrature decoder logic
 * @example
 * <code>
 * QEI1_PhaseInputSwappedSet(true);
 * </code>
 */
inline static void QEI1_PhaseInputSwappedSet(bool swapEnabled)
{
    if (swapEnabled == true)
    {
        QEI1IOCbits.SWPAB = 1;
    }
    else
    {
        QEI1IOCbits.SWPAB = 0;
    }
}

/**
 * Initializes the QEI1 peripheral.
 * Summary: Initializes the QEI1 peripheral.
 * @example
 * <code>
 * QEI1_Initialize();
 * </code>
 */
void QEI1_Initialize();

#ifdef __cplusplus  // Provide C++ Compatibility
}
#endif

#endif //_QEI1_H