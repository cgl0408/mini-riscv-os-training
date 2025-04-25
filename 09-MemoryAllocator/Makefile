# 設定編譯器和工具
CC = riscv-none-elf-gcc
LD = riscv-none-elf-ld
OBJDUMP = riscv-none-elf-objdump
QEMU = qemu-system-riscv32

# 編譯選項
# -Iinclude 讓編譯器知道標頭檔在 include 資料夾
CFLAGS = -nostdlib -fno-builtin -nostartfiles -ffreestanding -mcmodel=medany \
         -march=rv32imac_zicsr -mabi=ilp32 -Iinclude
LDFLAGS = -T os.ld

# QEMU 選項（不變）
QFLAGS = -nographic -smp 4 -machine virt -bios none

# 源碼文件
# 明確列出 src 資料夾中的 .c 和 .s 檔案
SRCS = src/start.s src/sys.s src/mem.s src/lib.c src/timer.c src/task.c src/os.c \
       src/user.c src/trap.c src/lock.c src/plic.c src/string.c src/virtio.c src/alloc.c

# 轉換成 .o 目標文件
# 把 src/*.c 和 src/*.s 轉成根目錄的 *.o
OBJS = $(patsubst src/%.c,%.o,$(patsubst src/%.s,%.o,$(SRCS)))

# 預設目標
all: os.elf kernel.elf

# 生成 os.elf
os.elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# 生成 kernel.elf
kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

# 編譯 C 文件（從 src 讀取）
%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# 編譯彙編 (.s) 文件（從 src 讀取）
%.o: src/%.s
	$(CC) $(CFLAGS) -c -o $@ $<

# QEMU 模擬執行 kernel.elf（不變）
qemu: kernel.elf
	@qemu-system-riscv32 -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	$(QEMU) $(QFLAGS) -drive if=none,format=raw,file=hdd.dsk,id=x0 -device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0 -kernel kernel.elf

# 清除編譯產物（不變）
clean:
	rm -f *.o *.elf

# 宣告偽目標
.PHONY: all qemu clean
