#include "os.h"

void user_task0(void){
	lib_puts("Create user task 0 sucessfully \n");
	lib_puts("Task0: Now, return to kernel mode\n");
	os_kernel();
	while(1){
		lib_puts("Running task 0 \n");
		lib_delay(1000);
		os_kernel();
	}

}

void user_task1(void){
	lib_puts("Create user task 1 sucessfully \n");
	lib_puts("Task1: Now, return to kernel mode\n");
	os_kernel();// it will return to os_main when we call os_kernel
	while(1){
		lib_puts("Running task 1 \n");
		lib_delay(1000);
		os_kernel();
	}
}

void user_init() {
	task_create(user_task0);
	task_create(user_task1);
}
