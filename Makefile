CC      = arm-none-eabi-gcc
MACH    = cortex-m3

CFLAGS  = -c -mcpu=$(MACH) -mthumb -std=gnu11 -O0 -Iinc
LDFLAGS = -nostdlib -T stm32f103_ls.ld -Wl,-Map=final.map

# Source files
SRCS = source/main.c \
       source/GPIO_driver.c \
       source/stm32f103_startup.c\
	   source/RCC_driver.c \
	   source/Flash_driver.c \
	   source/SysTick_Timer.c

# Object files (auto replace .c -> .o)
OBJS = $(SRCS:.c=.o)

# Final target
all: final.elf

# Compile rule (generic)
source/%.o: source/%.c
	$(CC) $(CFLAGS) -o $@ $^

# Link
final.elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Clean
clean:
	rm -rf source/*.o *.elf *.map