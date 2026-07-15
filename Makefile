GCC = gcc

GCC_FLAGS = -g

EMU_SRC = emulator

BUILD_DIR = build

OBJ_DIR = $(BUILD_DIR)/obj
EMU_OBJ_DIR = $(OBJ_DIR)/emulator

EMU_SRCS = $(wildcard $(EMU_SRC)/*.c)
EMU_OBJS = $(patsubst $(EMU_SRC)/%.c,$(EMU_OBJ_DIR)/%.o,$(EMU_SRCS))

EMU_EXEC = trk8-emu

all: emulator

emulator: $(BUILD_DIR)/$(EMU_EXEC)

$(BUILD_DIR)/$(EMU_EXEC): $(EMU_OBJS)
	$(GCC) $(EMU_OBJS) -o $@

$(EMU_OBJ_DIR)/%.o: $(EMU_SRC)/%.c | mkbuild
	$(GCC) $(GCC_FLAGS) -c $< -o $@

.SILENT: clean
.PHONY: clean clean_emu mkbuild all emulator

ifeq ($(OS), Windows_NT)
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

clean: clean_emu
	$(call RMFILE,$(BUILD_DIR))
	$(call RMDIR,$(OBJ_DIR))

clean_emu:
	$(call RMDIR,$(EMU_OBJ_DIR))

mkbuild:
	$(call MKDIR,$(BUILD_DIR))
	$(call MKDIR,$(OBJ_DIR))
	$(call MKDIR,$(EMU_OBJ_DIR))
