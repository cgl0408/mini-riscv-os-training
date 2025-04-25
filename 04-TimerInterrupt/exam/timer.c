#include "timer.h"

#define interval 10000000 // cycles; about 1 second in qemu.

void timer_init()
{
  // each CPU has a separate source of timer interrupts.
  int hart_id = r_mhartid();
  // ask the CLINT for a timer interrupt.
  
  *(reg_t*)CLINT_MTIMECMP(hart_id) = *(reg_t*)CLINT_MTIME + interval;

  // set the machine-mode trap handler.
  w_mtvec((reg_t)sys_timer);
  // enable machine-mode interrupts.
  //it will set MIE bit to on, it means machine mode can accept trap
  w_mstatus((reg_t) (r_mstatus() | MSTATUS_MIE));
  // enable machine-mode timer interrupts.
  w_mie((reg_t) (r_mie() | MIE_MTIE));
}

static int timer_count = 0;

reg_t timer_handler(reg_t epc, reg_t cause)
{
  reg_t return_epc = epc;
  int hart_id = r_mhartid();
  *(reg_t*)CLINT_MTIMECMP(hart_id) = *(reg_t*)CLINT_MTIME + interval;
  // disable machine-mode timer interrupts.
  w_mie((reg_t)(r_mie() & ~MIE_MTIE));
  lib_printf("timer_handler are processing: %d\n", ++timer_count);
  // enable machine-mode timer interrupts.
  w_mie((reg_t) (r_mie() | MIE_MTIE));

  return return_epc;
}
