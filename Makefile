GCC = gcc
GPP = g++

GCC_FLAGS = -g
GPP_FLAGS = -g -std=c++17

EMU_SRC = emulator
ASM_SRC = assembler

BUILD_DIR = build

OBJ_DIR = $(BUILD_DIR)/obj
EMU_OBJ_DIR = $(OBJ_DIR)/emulator
ASM_OBJ_DIR = $(OBJ_DIR)/assembler

EMU_SRCS = $(wildcard $(EMU_SRC)/*.c)
EMU_OBJS = $(subst $(EMU_SRC)/, $(EMU_OBJ_DIR)/, $(addsuffix .o, $(basename $(EMU_SRCS))))

ASM_SRCS = $(wildcard $(ASM_SRC)/*.cpp)
ASM_OBJS = $(subst $(ASM_SRC)/, $(ASM_OBJ_DIR)/, $(addsuffix .o, $(basename $(ASM_SRCS))))

EMU_EXEC = trk8-emu
ASM_EXEC = trk8-asm

all: clean emulator assembler

emulator: $(BUILD_DIR)/$(EMU_EXEC)
assembler: $(BUILD_DIR)/$(ASM_EXEC)

$(BUILD_DIR)/$(EMU_EXEC): $(EMU_OBJS)
	$(GCC) $(EMU_OBJS) -o $@

$(EMU_OBJ_DIR)/%.o: $(EMU_SRC)/%.c
	$(GCC) $(GCC_FLAGS) -c $< -o $@

$(BUILD_DIR)/$(ASM_EXEC): $(ASM_OBJS)
	$(GPP) $(ASM_OBJS) -o $@

$(ASM_OBJ_DIR)/%.o: $(ASM_SRC)/%.cpp
	$(GPP) $(GPP_FLAGS) -c $< -o $@

ifeq ($(OS), Windows_NT)
.SILENT: clean
endif

.PHONY: clean
clean: mkbuild
ifeq ($(OS), Windows_NT)
	del /Q /S $(BUILD_DIR)\*
else ifeq ($(shell uname), Linux)
	find $(BUILD_DIR) -maxdepth 1 -type f -exec rm {} \;
	rm -rf $(OBJ_DIR)/*
endif

mkbuild:
ifeq ($(OS), Windows_NT)
	if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"

	if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	if not exist "$(EMU_OBJ_DIR)" mkdir "$(EMU_OBJ_DIR)"
	if not exist "$(ASM_OBJ_DIR)" mkdir "$(ASM_OBJ_DIR)"
else ifeq ($(shell uname), Linux)
	mkdir -p $(BUILD_DIR)

	mkdir -p $(OBJ_DIR)
	mkdir -p $(EMU_OBJ_DIR)
	mkdir -p $(ASM_OBJ_DIR)
endif