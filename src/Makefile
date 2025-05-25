CC = gcc
FLAGS = -Wall -Wextra -g -std=c11 -DDEBUG -DLOG_USE_COLOR -I./lib/

# TODO: Check system and add flags if required
LIBS = -lws2_32 -lpthread

SRC_DIR = ./
BUILD_DIR = ./build
BIN_DIR = ./bin

# Dirty, but it works in mingw environment
ALL_SRC := $(shell find $(SRC_DIR) | grep "\.c$$")

ALL_OBJ := $(patsubst ./%.c,$(BUILD_DIR)/%.o,$(ALL_SRC))

TARGET = $(BIN_DIR)/server.exe

all: prepare-dirs $(TARGET)

rebuild: cleanf all

prepare-dirs: $(BUILD_DIR) $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(FLAGS) -c $< -o $@

$(TARGET): $(ALL_OBJ) | prepare-dirs
	$(CC) $(FLAGS) $^ $(LIBS) -o $@

clean:
	rm -rf $(BUILD_DIR)/*

cleanf:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all rebuild clean cleanf