GXX=gcc
GXX_FLAGS=-g

EMU_SRC=$(wildcard src/emulator/*.c)

BUILD=build

all: emulate

emulate: clean
	$(GXX) $(GXX_FLAGS) $(EMU_SRC) -o $(BUILD)/emulator

clean: mkbuild
	rm -rf $(BUILD)/*

mkbuild:
	mkdir -p $(BUILD)