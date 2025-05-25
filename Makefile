CC = gcc
FLAGS = -Wall -Wextra -g -std=c11 -DDEBUG -DLOG_USE_COLOR -D_GNU_SOURCE -D_POSIX_C_SOURCE=199309L -I./lib/ -I./include/
EXTRA_FLAGS = 

ifeq ($(shell uname -o),Msys)
	EXTRA_FLAGS += -lws2_32 -lpthread
endif

SRC_DIR = ./
BUILD_DIR = ./build
BIN_DIR = ./bin

ALL_SRC := $(shell find $(SRC_DIR) | grep "\.c$$")

ALL_OBJ := $(patsubst ./%.c,$(BUILD_DIR)/%.o,$(ALL_SRC))

TARGET = $(BIN_DIR)/server

all: prepare-dirs $(TARGET)

rebuild: cleanf all

prepare-dirs: $(BUILD_DIR) $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(FLAGS) $(EXTRA_FLAGS) -c $< -o $@

$(TARGET): $(ALL_OBJ) | prepare-dirs
	$(CC) $(FLAGS) $^ $(EXTRA_FLAGS) -o $@

clean:
	rm -rf $(BUILD_DIR)/*

cleanf:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all rebuild clean cleanf