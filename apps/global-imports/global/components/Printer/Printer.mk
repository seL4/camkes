Printer_GLOBAL := 1

CURRENT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

Printer_CFILES := $(wildcard $(CURRENT_DIR)src/*.c)
Printer_HFILES := $(wildcard $(CURRENT_DIR)include/*.h)
