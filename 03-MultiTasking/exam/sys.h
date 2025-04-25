#ifndef __SYS_H__
#define __SYS_H__
#include "riscv.h"
extern void sys_switch(struct context *ctx_save, struct context *ctx_load);

#endif
