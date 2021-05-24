#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = SoundBoard

# --------------------------------------------------------------
# Files to build

FILES_DSP = \
	SoundBoardPlugin.cpp

FILES_UI = \
	SoundBoardUI.cpp \
	widgets/src/Pad.cpp \
	fonts.cpp \

# --------------------------------------------------------------
# Do some magic

include ../../dpf/Makefile.plugins.mk
include ../../sfizz/dpf.mk

# --------------------------------------------------------------
# Extra flags
BUILD_C_FLAGS += $(SFIZZ_C_FLAGS)
BUILD_CXX_FLAGS += $(SFIZZ_CXX_FLAGS)
LINK_FLAGS += $(SFIZZ_LINK_FLAGS) 
BASE_FLAGS += -I. -I../../sfizz/external/filesystem/include/ghc \
				-I./widgets

	
# --------------------------------------------------------------
# Enable all possible plugin types

ifeq ($(HAVE_JACK),true)
ifeq ($(HAVE_OPENGL),true)
TARGETS += jack
endif
endif

ifeq ($(HAVE_OPENGL),true)
TARGETS += lv2_sep
else
TARGETS += lv2_dsp
endif

TARGETS += vst

all: $(TARGETS)

# --------------------------------------------------------------
