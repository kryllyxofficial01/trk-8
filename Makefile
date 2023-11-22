GXX=gcc
GXX_FLAGS=-g -Wno-discarded-qualifiers

ASM_SRC=$(wildcard src/assembler/*.c)
EMU_SRC=$(wildcard src/emulator/*.c)

BUILD=build

all: clean assemble emulate

assemble:
	$(GXX) $(GXX_FLAGS) $(ASM_SRC) -o $(BUILD)/assembler

emulate:
	$(GXX) $(GXX_FLAGS) $(EMU_SRC) -o $(BUILD)/emulator

clean: mkbuild
	rm -rf $(BUILD)/*

mkbuild:
	mkdir -p $(BUILD)