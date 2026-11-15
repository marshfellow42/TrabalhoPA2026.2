PROJ_NAME := tabuleiro

BUILD_DIR := build

CC ?= gcc

CFLAGS := -std=c23 -Wall -Wextra -Wpedantic -Werror
LDLIBS := -lm

TARGET := $(BUILD_DIR)/$(PROJ_NAME).out

.SILENT:

build:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) main.c -o $(TARGET) $(LDLIBS)

run:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) main.c -o $(TARGET) $(LDLIBS)
	$(TARGET)

clean:
ifeq ($(OS),Windows_NT)
	cmd /C rmdir /S /Q $(subst /,\,$(BUILD_DIR))
else
	rm -rf $(BUILD_DIR)
endif