#
#	BSP Makefile for the ThunderCat project.
#

BASE=$(shell pwd)/../bitthunder/
BUILD_BASE=$(BASE)
MODULE_NAME="ThunderCat"

TARGETS=thundercat.img
TARGET_DEPS=thundercat.elf

BUILD_DIR=$(shell pwd)/build/

include $(BASE).dbuild/dbuild.mk

tool:
	@echo $(BASE)
	@echo $(BT_CONFIG_SUBARCH)
	@echo $(BT_CONFIG_TOOLCHAIN)
	@echo $(TOOLCHAIN)


all: thundercat.elf thundercat.list thundercat.img thundercat.syms
	$(Q)$(SIZE) thundercat.elf

thundercat.img: thundercat.elf
	$(Q)$(PRETTY) IMAGE $(MODULE_NAME) $@
	$(Q)$(OBJCOPY) thundercat.elf -O binary $@

thundercat.list: thundercat.elf
	$(Q)$(PRETTY) LIST $(MODULE_NAME) $@
	$(Q)$(OBJDUMP) -D thundercat.elf > $@

thundercat.syms: thundercat.elf
	$(Q)$(PRETTY) SYMS $(MODULE_NAME) $@
	$(Q)$(OBJDUMP) -t thundercat.elf > $@

thundercat.elf: $(OBJECTS)
	$(Q)$(PRETTY) --dbuild "LD" $(MODULE_NAME) $@
	$(Q)$(CC) -mtune=$(CC_MTUNE) -march=$(CC_MARCH) $(CC_TCFLAGS) $(CC_MACHFLAGS) -o $@ -T $(LINKER_SCRIPT) -Wl,-Map=thundercat.map -Wl,--gc-sections $(OBJECTS) -nostdlib -lc -lgcc
