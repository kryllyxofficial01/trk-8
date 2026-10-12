GCC = gcc

GCC_FLAGS = -g

ASM_SRC = assembler
EMU_SRC = emulator

BUILD_DIR = build

OBJ_DIR = $(BUILD_DIR)/obj
ASM_OBJ_DIR = $(OBJ_DIR)/assembler
EMU_OBJ_DIR = $(OBJ_DIR)/emulator

ASM_SRCS = $(wildcard $(ASM_SRC)/*.c)
ASM_OBJS = $(patsubst $(ASM_SRC)/%.c, $(ASM_OBJ_DIR)/%.o, $(ASM_SRCS))

EMU_SRCS = $(wildcard $(EMU_SRC)/*.c)
EMU_OBJS = $(patsubst $(EMU_SRC)/%.c, $(EMU_OBJ_DIR)/%.o, $(EMU_SRCS))

ASM_EXEC = trk8-asm
EMU_EXEC = trk8-emu

.PHONY: clean mkbuild all assembler emulator

all: assembler emulator

assembler: $(BUILD_DIR)/$(ASM_EXEC)

$(BUILD_DIR)/$(ASM_EXEC): $(ASM_OBJS)
	$(GCC) $(ASM_OBJS) -o $@

$(ASM_OBJ_DIR)/%.o: $(ASM_SRC)/%.c | mkbuild
	$(GCC) $(GCC_FLAGS) -c $< -o $@

emulator: $(BUILD_DIR)/$(EMU_EXEC)

$(BUILD_DIR)/$(EMU_EXEC): $(EMU_OBJS)
	$(GCC) $(EMU_OBJS) -o $@

$(EMU_OBJ_DIR)/%.o: $(EMU_SRC)/%.c | mkbuild
	$(GCC) $(GCC_FLAGS) -c $< -o $@

.SILENT: clean

clean:
ifeq ($(OS), Windows_NT)
	if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"
else ifeq ($(shell uname), Linux)
	rm -rf $(OBJ_DIR)/*
endif

mkbuild:
ifeq ($(OS), Windows_NT)
	if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	if not exist "$(EMU_OBJ_DIR)" mkdir "$(EMU_OBJ_DIR)"
	if not exist "$(ASM_OBJ_DIR)" mkdir "$(ASM_OBJ_DIR)"
else ifeq ($(shell uname), Linux)
	mkdir -p $(EMU_OBJ_DIR)
	mkdir -p $(ASM_OBJ_DIR)
endif