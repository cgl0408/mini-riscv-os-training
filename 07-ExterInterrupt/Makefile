# 設定編譯器
CC = riscv-none-elf-gcc
LD = riscv-none-elf-ld
OBJDUMP = riscv-none-elf-objdump
QEMU = qemu-system-riscv32

# 編譯選項
CFLAGS = -nostdlib -fno-builtin -nostartfiles -ffreestanding -mcmodel=medany \
         -march=rv32imac_zicsr -mabi=ilp32
LDFLAGS = -T os.ld

# QEMU 選項
QFLAGS = -nographic -smp 4 -machine virt -bios none

# 源碼文件
SRCS = start.s sys.s lib.c timer.c task.c os.c user.c trap.c lock.c plic.c

# 轉換成 .o 目標文件
OBJS = $(SRCS:.c=.o)
OBJS := $(OBJS:.s=.o)  # 確保 .s 也轉換成 .o

# 預設目標
all: os.elf kernel.elf

# 生成 os.elf
os.elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# 生成 kernel.elf
kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

# 編譯 C 文件
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# 編譯彙編 (.s) 文件
%.o: %.s
	$(CC) $(CFLAGS) -c -o $@ $<

# QEMU 模擬執行 kernel.elf
qemu: kernel.elf
	@qemu-system-riscv32 -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	$(QEMU) $(QFLAGS) -kernel kernel.elf

# 清除編譯產物
clean:
	rm -f *.o *.elf

