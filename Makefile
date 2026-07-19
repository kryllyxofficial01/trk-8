GCC = gcc

GCC_FLAGS = -g

EMU_SRC = emulator

BUILD_DIR = build

OBJ_DIR = $(BUILD_DIR)/obj
EMU_OBJ_DIR = $(OBJ_DIR)/emulator

EMU_SRCS = $(wildcard $(EMU_SRC)/*.c)
EMU_OBJS = $(patsubst $(EMU_SRC)/%.c, $(EMU_OBJ_DIR)/%.o, $(EMU_SRCS))

EMU_EXEC = trk8-emu

all: emulator

emulator: $(BUILD_DIR)/$(EMU_EXEC)

$(BUILD_DIR)/$(EMU_EXEC): $(EMU_OBJS)
	$(GCC) $(EMU_OBJS) -o $@

$(EMU_OBJ_DIR)/%.o: $(EMU_SRC)/%.c | mkbuild
	$(GCC) $(GCC_FLAGS) -c $< -o $@

.SILENT: clean
.PHONY: clean mkbuild all emulator

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
else ifeq ($(shell uname), Linux)
	mkdir -p $(EMU_OBJ_DIR)
endif