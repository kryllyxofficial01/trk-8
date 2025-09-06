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
ASM_OBJS = $(subst $(ASM_SRC)/, $(ASM_OBJ_DIR)/, $(addsuffix .o, $(basename $(ASM_SRCS))))

EMU_SRCS = $(wildcard $(EMU_SRC)/*.c)
EMU_OBJS = $(subst $(EMU_SRC)/, $(EMU_OBJ_DIR)/, $(addsuffix .o, $(basename $(EMU_SRCS))))

ASM_EXEC = trk8-asm
EMU_EXEC = trk8-emu

all: assembler emulator

assembler: clean_asm $(BUILD_DIR)/$(ASM_EXEC)
emulator: clean_emu $(BUILD_DIR)/$(EMU_EXEC)

$(BUILD_DIR)/$(ASM_EXEC): $(ASM_OBJS)
	$(GPP) $(ASM_OBJS) -o $@

$(ASM_OBJ_DIR)/%.o: $(ASM_SRC)/%.cpp
	$(GPP) $(GPP_FLAGS) -c $< -o $@

$(BUILD_DIR)/$(EMU_EXEC): $(EMU_OBJS)
	$(GCC) $(EMU_OBJS) -o $@

$(EMU_OBJ_DIR)/%.o: $(EMU_SRC)/%.c
	$(GCC) $(GCC_FLAGS) -c $< -o $@

.SILENT: clean
.PHONY: clean

clean: clean_asm clean_emu
	if exist "$(subst /,\,$(BUILD_DIR))" del /Q "$(subst /,\,$(BUILD_DIR))\*.*"

clean_asm: mkbuild
	if exist "$(subst /,\,$(ASM_OBJ_DIR))" del /Q /S "$(subst /,\,$(ASM_OBJ_DIR))\*"

clean_emu: mkbuild
	if exist "$(subst /,\,$(EMU_OBJ_DIR))" del /Q /S "$(subst /,\,$(EMU_OBJ_DIR))\*"

mkbuild:
	if not exist "$(subst /,\,$(BUILD_DIR))" mkdir "$(subst /,\,$(BUILD_DIR))"

	if not exist "$(subst /,\,$(OBJ_DIR))" mkdir "$(subst /,\,$(OBJ_DIR))"
	if not exist "$(subst /,\,$(ASM_OBJ_DIR))" mkdir "$(subst /,\,$(ASM_OBJ_DIR))"
	if not exist "$(subst /,\,$(EMU_OBJ_DIR))" mkdir "$(subst /,\,$(EMU_OBJ_DIR))"