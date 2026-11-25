#ifndef __TRK8_PARSER_H
#define __TRK8_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>

#include "asm_line.h"
#include "utils.h"

bool parser_parse_file(const char* filepath, trk8_assembly_line_t** lines, uint16_t* line_count);

#endif