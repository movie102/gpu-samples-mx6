# Copyright Freescale 2010
# This file contains a set of system variables needed to build samples and demos in this GPU SDK
# Modify as nessecary to build on your system

#set an absolute path the the SDK root here 
#if not set, individual makefiles will try a relative guess
FSL_GPUSDK_ROOT = .
LTIB_ROOTFS=/home/rogerio/ltib/nov2011/ltib/rootfs

ifndef FSL_GPUSDK_ROOT
	echo "WARNING: FSL_GPUSDK_ROOT not defined!"
endif

#FSL_PLATFORM = MX51
#FSL_PLATFORM = MX31
#FSL_PLATFORM = MX35
FSL_PLATFORM = MX6X

#if building on an LTIB system, set CROSS_COMPILE as below
CROSS_COMPILE = /opt/freescale/usr/local/gcc-4.4.4-glibc-2.11.1-multilib-1.0/arm-fsl-linux-gnueabi/bin/arm-fsl-linux-gnueabi-
#if building on an EVK
#CROSS_COMPILE = 

#directory with GLES, VG, and EGL headers
FSL_GPU_INC =  $(LTIB_ROOTFS)/usr/include
#if building on an EVK
#FSL_GPU_INC =  /usr/include

#all other system headers
FSL_PLATFORM_INC = $(LTIB_ROOTFS)/usr/include
#if building on an EVK
#FSL_PLATFORM_INC =  /usr/include

#location of libEGL.so, etc.
FSL_GPU_LIB = $(LTIB_ROOTFS)/usr/lib
#if building on an EVK
#FSL_GPU_LIB =  /usr/lib

#location of other system libraries
FSL_PLATFORM_LIB = $(LTIB_ROOTFS)/usr/lib
#if building on an EVK
#FSL_PLATFORM_LIB =  /usr/lib

ARCH = arm
CD = cd
DEL_FILE = rm -f
MKDIR = mkdir -p
RMDIR = rmdir
CC = $(CROSS_COMPILE)g++
AR = $(CROSS_COMPILE)ar
LD = $(CROSS_COMPILE)g++
CP = cp
MAKE = make

CFLAGS = -DDEBUG -D_DEBUG -D_GNU_SOURCE -D_LINUX -mfloat-abi=softfp -mfpu=vfp -fPIC -O3 -fno-strict-aliasing -fno-optimize-sibling-calls -g -O2 -mcpu=arm1136jf-s -mapcs-frame -fPIC -Wall -W -Wno-unused-parameter

CFLAGS += -I$(FSL_GPUSDK_ROOT)/include -I$(FSL_GPU_INC) -I$(FSL_PLATFORM_INC)

LFLAGS = -Wl,--library-path=$(FSL_GPU_LIB),--library-path=$(FSL_PLATFORM_LIB),-rpath-link=$(FSL_GPU_LIB),-rpath-link=$(FSL_PLATFORM_LIB) -ldl


EGL_FLAGS = -lEGL

ES11_FLAGS = -lGLESv1_CM

ES20_FLAGS = -lGLESv2 

VG11_FLAGS = -lOpenVG

# There are two C2D API 2D libraries on i.MX.  One for the Z160 GPU and one for the Z430
# The default bewlow is Z160, which is present on MX35 and all MX5x chips
# The Z430 is the 3D core, which is only present on MX51 and MX53

C2D_FLAGS = -l2dz160
#C2D_FLAGS = -l2dz430


#$(FSLUTIL_LIB):
#	$(CD)  $(FSL_GPUSDK_ROOT)/utility/fslutil; \
#	$(MAKE) -f Makefile;

#$(GLU_LIB):
#	$(CD)  $(FSL_GPUSDK_ROOT)/utility/glu3; \
#	$(MAKE) -f Makefile;


