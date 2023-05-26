CC=gcc
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
AS=nasm
ASFLAGS=-f elf64
LD=ld
LDFLAGS=-T linker.ld
MKISO=grub-mkrescue

SRCDIR=src
BUILDDIR=obj
ISODIR=iso
BOOTDIR=$(ISODIR)/boot
BINFILE=$(BOOTDIR)/avsys.bin
ISOFILE=bin/avsys.iso

SRCS=$(shell find $(SRCDIR) -name '*.c' -o -name '*.asm')
OBJS=$(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(patsubst $(SRCDIR)/%.asm,$(BUILDDIR)/%.o,$(SRCS)))
DIRS=$(sort $(dir $(OBJS))) bin obj $(BOOTDIR)/grub

.PHONY: all

all: check distcheck $(BINFILE) copy_grub_cfg iso

check:
	@echo "Checking if required packages are installed..."
	@./configure

distcheck:
	@echo "Running distribution checks"

	@if [ "$(OS)" = "Windows_NT" ]; then \
		echo "Error: Windows is not supported!"; \
		exit 1; \
	fi

	@echo "Success!"

copy_grub_cfg:
	cp grub.cfg $(BOOTDIR)/grub/grub.cfg

$(BINFILE): $(OBJS) | $(BOOTDIR)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(DIRS)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.asm | $(DIRS)
	$(AS) $(ASFLAGS) $< -o $@

$(DIRS):
	mkdir -p $@

$(BOOTDIR):
	mkdir -p $@

iso: $(ISOFILE)

$(ISOFILE): $(BINFILE)
	$(MKISO) -o $@ $(ISODIR)

clean:
	rm -rf $(BUILDDIR) $(BINFILE) $(ISOFILE)
	rm -rf bin obj

run:
	qemu-system-x86_64 $(ISOFILE)
