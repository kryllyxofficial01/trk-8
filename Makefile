GXX = gcc

GXX_FLAGS = -g

EMU_SRC = emulator

BUILD = build
OBJ = $(BUILD)/obj

EMU_SRCS = $(wildcard $(EMU_SRC)/*.c)
EMU_OBJS = $(subst $(EMU_SRC)/, $(OBJ)/, $(addsuffix .o, $(basename $(EMU_SRCS))))

EMU_EXEC = trk8-emu

all: clean emulator

emulator: $(BUILD)/$(EMU_EXEC)

$(BUILD)/$(EMU_EXEC): $(EMU_OBJS)
	$(GXX) $(EMU_OBJS) -o $@

$(OBJ)/%.o: $(EMU_SRC)/%.c
	$(GXX) $(GXX_FLAGS) -c $< -o $@

ifeq ($(OS), Windows_NT)
.SILENT: clean
endif

.PHONY: clean
clean: mkbuild
ifeq ($(OS), Windows_NT)
	del /Q /S $(BUILD)\*
else ifeq ($(shell uname), Linux)
	find $(BUILD) -maxdepth 1 -type f -exec rm {} \;
	rm -rf $(OBJ)/*
endif

mkbuild:
ifeq ($(OS), Windows_NT)
	if not exist "$(BUILD)" mkdir "$(BUILD)"
	if not exist "$(OBJ)" mkdir "$(OBJ)"
else ifeq ($(shell uname), Linux)
	mkdir -p $(BUILD)
	mkdir -p $(OBJ)
endif