# Copyright 2010 Freescale 

ifndef FSL_GPUSDK_ROOT
FSL_GPUSDK_ROOT = .
endif

include $(FSL_GPUSDK_ROOT)/buildvars.mk

APPNAME			= testApp2
DESTDIR			= $(FSL_GPUSDK_ROOT)/bin
SRCDIR			= .

ifeq '$(FSL_PLATFORM)' 'MX31'
FSL_FAIL_PLATFORM = 1
endif

ifeq '$(FSL_PLATFORM)' 'MX35'
FSL_FAIL_PLATFORM = 1
endif

LFLAGS                  += $(EGL_FLAGS) $(ES20_FLAGS) -lm

OBJECTS			= $(SRCDIR)/lesson05_imx_fb.o


first: all

all: check_platform $(APPNAME)

.PHONY: check_platform

$(APPNAME): check_platform $(OBJECTS) $(FSLUTIL_LIB) $(GLU_LIB)
	-@$(MKDIR) $(DESTDIR)
	$(LD) $(LFLAGS) -o $(DESTDIR)/$(APPNAME) $(OBJECTS) $(FSLUTIL_LIB) $(GLU_LIB)

$(FSLUTIL_LIB):
	$(CD)  $(FSL_GPUSDK_ROOT)/utility/fslutil; \
	$(MAKE) -f Makefile;

$(GLU_LIB):
	$(CD)  $(FSL_GPUSDK_ROOT)/utility/glu3; \
	$(MAKE) -f Makefile;

%_fb.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(DEL_FILE) $(OBJECTS) $(UTILOBJS)
	$(DEL_FILE) *~ core *.core

distclean: clean
	$(DEL_FILE) $(DESTDIR)/$(APPNAME)
	-@$(RMDIR) $(DESTDIR)

check_platform:
ifdef FSL_FAIL_PLATFORM
	@echo "Chosen platform not supported within this sample"
	@exit 2
endif

