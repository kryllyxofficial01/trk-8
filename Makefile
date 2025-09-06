GPP = g++
GCC = gcc

GPP_FLAGS = -g -std=c++17
GCC_FLAGS = -g

ASM_SRC = assembler
EMU_SRC = emulator

BUILD_DIR = build

OBJ_DIR = $(BUILD_DIR)/obj
ASM_OBJ_DIR = $(OBJ_DIR)/assembler
EMU_OBJ_DIR = $(OBJ_DIR)/emulator

ASM_SRCS = $(wildcard $(ASM_SRC)/*.cpp)
ASM_OBJS = $(patsubst $(ASM_SRC)/%.cpp,$(ASM_OBJ_DIR)/%.o,$(ASM_SRCS))

EMU_SRCS = $(wildcard $(EMU_SRC)/*.c)
EMU_OBJS = $(patsubst $(EMU_SRC)/%.c,$(EMU_OBJ_DIR)/%.o,$(EMU_SRCS))

ASM_EXEC = trk8-asm
EMU_EXEC = trk8-emu

all: assembler emulator

assembler: $(BUILD_DIR)/$(ASM_EXEC)
emulator: $(BUILD_DIR)/$(EMU_EXEC)

$(BUILD_DIR)/$(ASM_EXEC): $(ASM_OBJS)
	$(GPP) $(ASM_OBJS) -o $@

$(ASM_OBJ_DIR)/%.o: $(ASM_SRC)/%.cpp | mkbuild
	$(GPP) $(GPP_FLAGS) -c $< -o $@

$(BUILD_DIR)/$(EMU_EXEC): $(EMU_OBJS)
	$(GCC) $(EMU_OBJS) -o $@

$(EMU_OBJ_DIR)/%.o: $(EMU_SRC)/%.c | mkbuild
	$(GCC) $(GCC_FLAGS) -c $< -o $@

.SILENT: clean
.PHONY: clean clean_asm clean_emu mkbuild all assembler emulator

ifeq ($(OS),Windows_NT)
    RMFILE = del /Q
    RMDIR = rmdir /S /Q
    MKDIR = if not exist "$(subst /,\,$1)" mkdir "$(subst /,\,$1)"
    SEP = \\
else
    RMFILE = find $1 -maxdepth 1 -type f -exec rm {} \;
    RMDIR = rm -rf $1/*
    MKDIR = mkdir -p $1
    SEP = /
endif

clean: clean_asm clean_emu
	$(call RMFILE,$(BUILD_DIR))
	$(call RMDIR,$(OBJ_DIR))

clean_asm:
	$(call RMDIR,$(ASM_OBJ_DIR))

clean_emu:
	$(call RMDIR,$(EMU_OBJ_DIR))

mkbuild:
	$(call MKDIR,$(BUILD_DIR))
	$(call MKDIR,$(OBJ_DIR))
	$(call MKDIR,$(ASM_OBJ_DIR))
	$(call MKDIR,$(EMU_OBJ_DIR))
