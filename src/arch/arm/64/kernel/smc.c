#ifdef CONFIG_ARM_SMC_SUPPORT
#include <stdint.h>
#include <arch/kernel/smc.h>

const word_t n_smcRegisters = 8;

extern void invokeSMC(uint64_t smc_reg_in[n_smcRegisters], uint64_t *smc_reg_out);

exception_t decodeARMSMCInvocation(word_t invLabel, word_t length, cptr_t cptr,
                                   cte_t *cte, cap_t cap, word_t *buffer)
{
    /* use a similar method to invokeTCB_ReadRegisters */
    tcb_t *thread = NODE_STATE(ksCurThread);
    word_t *ipcBuffer = lookupIPCBuffer(true, thread);
    word_t i = 0;

    uint64_t smc_reg_in[n_smcRegisters];
    uint64_t smc_reg_out[n_smcRegisters];

    /* copy input registers */
    for (i = 0; i < n_smcRegisters; i++) {
        smc_reg_in[i] = getSyscallArg(i, buffer);
    }

    invokeSMC(smc_reg_in, smc_reg_out);

    /* copy output registers */
    for (i = 0; i < n_smcRegisters && i < n_msgRegisters; i++) {
        setRegister(thread, msgRegisters[i], smc_reg_out[i]);
    }

    if (ipcBuffer != NULL && i < n_smcRegisters) {
        for (; i < n_smcRegisters; i++) {
            ipcBuffer[i + 1] = smc_reg_out[i];
        }
    }

    setRegister(thread, msgInfoRegister, wordFromMessageInfo(seL4_MessageInfo_new(0, 0, 0, i)));
    return EXCEPTION_NONE;
}
#endif
