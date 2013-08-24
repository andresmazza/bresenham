BOARD       ?= uno
TARGET      ?= main
SOURCES     ?= src/$(TARGET).cc
ROOT        ?= $(CURDIR)
#LIBRARYPATH := $(ROOT)/libs
LIBRARIES   ?= Stepper

include $(ROOT)/arduino.mk
