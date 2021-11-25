#include <machine/assembler.h>

BEGIN_FUNC(invokeSMC)
    stp     x29, x30, [sp, #-16]!
    stp     x19, x20, [sp, #-16]!
    mov     x19, x0                 // copy input array pointer
    mov     x20, x1                 // copy output array pointer
    ldr     x0, [x19, #0]           // load arguments
    ldr     x1, [x19, #8]
    ldr     x2, [x19, #16]
    ldr     x3, [x19, #24]
    ldr     x4, [x19, #32]
    ldr     x5, [x19, #40]
    ldr     x6, [x19, #48]
    ldr     x7, [x19, #56]
    smc     #0                      // smc call
    str     x0, [x20, #0]	        // save results
    str     x1, [x20, #8]
    str     x2, [x20, #16]
    str     x3, [x20, #24]
    str     x4, [x20, #32]
    str     x5, [x20, #40]
    str     x6, [x20, #48]
    str     x7, [x20, #56]
    nop
    ldp     x19, x20, [sp], #16
    ldp     x29, x30, [sp], #16
    ret
    nop
END_FUNC(invokeSMC)