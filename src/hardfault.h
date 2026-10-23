#ifndef HARDFAULT_H
#define HARDFAULT_H


#include "defines.h"
#include "status.h"

#include "debug/debug.h"
#include "debug/debug_led.h"

#include <inttypes.h>


#define HARDFAULT_DETECT_FLAG 0xDEADBEEF

#define HARDFAULT_CFSR_DIVBYZERO_Pos    (25UL)
#define HARDFAULT_CFSR_DIVBYZERO_Msk    (1UL << HARDFAULT_CFSR_DIVBYZERO_Pos)
#define HARDFAULT_CFSR_DIVBYZERO        HARDFAULT_CFSR_DIVBYZERO_Msk
#define HARDFAULT_CFSR_UNALIGNED_Pos    (24UL)
#define HARDFAULT_CFSR_UNALIGNED_Msk    (1UL << HARDFAULT_CFSR_UNALIGNED_Pos)
#define HARDFAULT_CFSR_UNALIGNED        HARDFAULT_CFSR_UNALIGNED_Msk
#define HARDFAULT_CFSR_NOCP_Pos         (19UL)
#define HARDFAULT_CFSR_NOCP_Msk         (1UL << HARDFAULT_CFSR_NOCP_Pos)
#define HARDFAULT_CFSR_NOCP             HARDFAULT_CFSR_NOCP_Msk
#define HARDFAULT_CFSR_INVPC_Pos        (18UL)
#define HARDFAULT_CFSR_INVPC_Msk        (1UL << HARDFAULT_CFSR_INVPC_Pos)
#define HARDFAULT_CFSR_INVPC            HARDFAULT_CFSR_INVPC_Msk
#define HARDFAULT_CFSR_INVSTATE_Pos     (17UL)
#define HARDFAULT_CFSR_INVSTATE_Msk     (1UL << HARDFAULT_CFSR_INVSTATE_Pos)
#define HARDFAULT_CFSR_INVSTATE         HARDFAULT_CFSR_INVSTATE_Msk
#define HARDFAULT_CFSR_UNDEFINSTR_Pos   (16UL)
#define HARDFAULT_CFSR_UNDEFINSTR_Msk   (1UL << HARDFAULT_CFSR_UNDEFINSTR_Pos)
#define HARDFAULT_CFSR_UNDEFINSTR       HARDFAULT_CFSR_UNDEFINSTR_Msk
#define HARDFAULT_CFSR_BFARVALID_Pos    (15UL)
#define HARDFAULT_CFSR_BFARVALID_Msk    (1UL << HARDFAULT_CFSR_BFARVALID_Pos)
#define HARDFAULT_CFSR_BFARVALID        HARDFAULT_CFSR_BFARVALID_Msk
#define HARDFAULT_CFSR_STKERR_Pos       (12UL)
#define HARDFAULT_CFSR_STKERR_Msk       (1UL << HARDFAULT_CFSR_STKERR_Pos)
#define HARDFAULT_CFSR_STKERR           HARDFAULT_CFSR_STKERR_Msk
#define HARDFAULT_CFSR_UNSTKERR_Pos     (11UL)
#define HARDFAULT_CFSR_UNSTKERR_Msk     (1UL << HARDFAULT_CFSR_UNSTKERR_Pos)
#define HARDFAULT_CFSR_UNSTKERR         HARDFAULT_CFSR_UNSTKERR_Msk
#define HARDFAULT_CFSR_IMPRECISERR_Pos  (10UL)
#define HARDFAULT_CFSR_IMPRECISERR_Msk  (1UL << HARDFAULT_CFSR_IMPRECISERR_Pos)
#define HARDFAULT_CFSR_IMPRECISERR      HARDFAULT_CFSR_IMPRECISERR_Msk
#define HARDFAULT_CFSR_PRECISERR_Pos    (9UL)
#define HARDFAULT_CFSR_PRECISERR_Msk    (1UL << HARDFAULT_CFSR_PRECISERR_Pos)
#define HARDFAULT_CFSR_PRECISERR        HARDFAULT_CFSR_PRECISERR_Msk
#define HARDFAULT_CFSR_IBUSERR_Pos      (8UL)
#define HARDFAULT_CFSR_IBUSERR_Msk      (1UL << HARDFAULT_CFSR_IBUSERR_Pos)
#define HARDFAULT_CFSR_IBUSERR          HARDFAULT_CFSR_IBUSERR_Msk
#define HARDFAULT_CFSR_MMARVALID_Pos    (7UL)
#define HARDFAULT_CFSR_MMARVALID_Msk    (1UL << HARDFAULT_CFSR_MMARVALID_Pos)
#define HARDFAULT_CFSR_MMARVALID        HARDFAULT_CFSR_MMARVALID_Msk
#define HARDFAULT_CFSR_MSTKERR_Pos      (4UL)
#define HARDFAULT_CFSR_MSTKERR_Msk      (1UL << HARDFAULT_CFSR_MSTKERR_Pos)
#define HARDFAULT_CFSR_MSTKERR          HARDFAULT_CFSR_MSTKERR_Msk
#define HARDFAULT_CFSR_MUNSTKERR_Pos    (3UL)
#define HARDFAULT_CFSR_MUNSTKERR_Msk    (1UL << HARDFAULT_CFSR_MUNSTKERR_Pos)
#define HARDFAULT_CFSR_MUNSTKERR        HARDFAULT_CFSR_MUNSTKERR_Msk
#define HARDFAULT_CFSR_DACCVIOL_Pos     (1UL)
#define HARDFAULT_CFSR_DACCVIOL_Msk     (1UL << HARDFAULT_CFSR_DACCVIOL_Pos)
#define HARDFAULT_CFSR_DACCVIOL         HARDFAULT_CFSR_DACCVIOL_Msk
#define HARDFAULT_CFSR_IACCVIOL_Pos     (0UL)
#define HARDFAULT_CFSR_IACCVIOL_Msk     (1UL << HARDFAULT_CFSR_IACCVIOL_Pos)
#define HARDFAULT_CFSR_IACCVIOL         HARDFAULT_CFSR_IACCVIOL_Msk

static const char* const HARDFAULT_CRASHLOG_CFSR_TEXT[] = {
    "IACCVIOL: Instruction access violation flag",
    "DACCVIOL: Data access violation flag",
    "",
    "MUNSTKERR: Memory manager fault on unstacking for a return from exception",
    "MSTKERR: Memory manager fault on stacking for exception entry",
    "", "",
    "MMARVALID: Memory Management Fault Address Register (MMAR) valid flag",

    "IBUSERR: Instracion bus error",
    "PRECISERR: Precise data bus error",
    "UNSTKERR: Bus fault on unstacking for a return from exception",
    "STKERR: Bus fault on stacking for exception entry",
    "", "",
    "BFARVALID: Bus Fault Address Register (BFAR) valid flag",

    "UNDEFINSTR: Undefined instruction usage fault",
    "INVSTATE: Invalid state usage fault",
    "INVPC: Invalid PC load usage fault, caused by an invalid PC load by EXC_RETURN",
    "OCP: No coprocessor usage fault",
    "", "", "", "",
    "UNALIGNED: Unaligned access usage fault",
    "DIVBYZERO: Divide by zero usage fault",
    "", "", "", "", "", ""
};


struct HardFault_Info {
    uint32_t R0;
    uint32_t R1;
    uint32_t R2;
    uint32_t R3;
    uint32_t R12;
    uint32_t LR;
    uint32_t PC;
    uint32_t PSR;
    uint32_t flag;

    uint32_t CFSR;

    uint32_t HFSR;
    uint32_t MMFAR;
    uint32_t BFAR;
};
volatile struct HardFault_Info HARDFAULT_CRASH_REPORT __attribute__((section(".noinit")));


__attribute__((used)) void HardFault_CrashReport(uint32_t* stack_pointer) {
    HARDFAULT_CRASH_REPORT.R0 = stack_pointer[0];
    HARDFAULT_CRASH_REPORT.R1 = stack_pointer[1];
    HARDFAULT_CRASH_REPORT.R2 = stack_pointer[2];
    HARDFAULT_CRASH_REPORT.R3 = stack_pointer[3];
    HARDFAULT_CRASH_REPORT.R12 = stack_pointer[4];
    HARDFAULT_CRASH_REPORT.LR = stack_pointer[5];
    HARDFAULT_CRASH_REPORT.PC = stack_pointer[6];
    HARDFAULT_CRASH_REPORT.PSR = stack_pointer[7];
    HARDFAULT_CRASH_REPORT.CFSR = SCB->CFSR;
    HARDFAULT_CRASH_REPORT.HFSR = SCB->HFSR;
    HARDFAULT_CRASH_REPORT.MMFAR = SCB->MMFAR;
    HARDFAULT_CRASH_REPORT.BFAR = SCB->BFAR;

    HARDFAULT_CRASH_REPORT.flag = HARDFAULT_DETECT_FLAG;

    GPIOB->ODR = 0;
    DebugLed_Exception_On();

    for(volatile uint32_t t0 = 0; t0 < 5; t0++) {
        DebugLed_Exception_Toggle();

        for(volatile uint32_t t = 0; t < 1000000; t++) { __NOP(); }
    }

    NVIC_SystemReset();
}


__attribute__((naked, used)) void HardFault_Handler(void) {
    __ASM volatile (
        " TST LR, #4                                 \n"
        " ITE EQ                                     \n"
        " MRSEQ R0, MSP                              \n"
        " MRSNE R0, PSP                              \n"
        " LDR R1, =HardFault_CrashReport             \n"
        " BX R1                                      \n"
    );
}


__STATIC_INLINE void HardFault_CFSR(void) {
    for(uint32_t i = 0; i < 32; i++) {
        if(HARDFAULT_CRASH_REPORT.CFSR & (1UL << i)) {
            DebugLog(STATUS_EXCEPTION, HARDFAULT_CRASHLOG_CFSR_TEXT[i]);
        }
    }
}


__STATIC_INLINE void HardFault_Log(void) {
    if(HARDFAULT_CRASH_REPORT.flag != HARDFAULT_DETECT_FLAG) {
        return;
    }

    HARDFAULT_CRASH_REPORT.flag = 0;

    DebugLogf(STATUS_EXCEPTION,
        "R0=%08"PRIX32
        " R1=%08"PRIX32
        " R2=%08"PRIX32
        " R3=%08"PRIX32
        " R12=%08"PRIX32
        " LR=%08"PRIX32
        " PC=%08"PRIX32
        " PSR=%08"PRIX32"",
        HARDFAULT_CRASH_REPORT.R0,
        HARDFAULT_CRASH_REPORT.R1,
        HARDFAULT_CRASH_REPORT.R2,
        HARDFAULT_CRASH_REPORT.R3,
        HARDFAULT_CRASH_REPORT.R12,
        HARDFAULT_CRASH_REPORT.LR,
        HARDFAULT_CRASH_REPORT.PC,
        HARDFAULT_CRASH_REPORT.PSR
    );

    DebugLogf(STATUS_EXCEPTION,
        "CFSR=%08"PRIX32" HFSR=%08"PRIX32" BFAR=%08"PRIX32" MMFAR=%08"PRIX32"",
        HARDFAULT_CRASH_REPORT.CFSR,
        HARDFAULT_CRASH_REPORT.HFSR,
        HARDFAULT_CRASH_REPORT.BFAR,
        HARDFAULT_CRASH_REPORT.MMFAR
    );

    HardFault_CFSR();
}


#endif // HARDFAULT_H
