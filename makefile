CONFIG_MODULE_SIG=n

obj-m   := md5sum.o
ccflags-y := -std=gnu99
KERNELDIR ?= /usr/src/kernels/3.10.0-1127.13.1.el7.x86_64

#KERNELDIR ?= /lib/modules/$(shell uname -r)/

modules:
	$(MAKE) -C $(KERNELDIR) SUBDIRS=$(shell pwd) modules

clean:
	rm -f modules.order Module.symvers *.o *.ko
	rm -f .*.ko.cmd .*.mod.o.cmd .*.o.cmd
	rm -rf .tmp_versions
	rm -f *.mod.c
