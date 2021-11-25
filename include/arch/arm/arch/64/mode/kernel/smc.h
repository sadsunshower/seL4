#ifdef CONFIG_ARM_SMC_SUPPORT
#pragma once

exception_t decodeARMSMCInvocation(word_t invLabel, word_t length, cptr_t cptr,
                                   cte_t *cte, cap_t cap, word_t *buffer);

#endif