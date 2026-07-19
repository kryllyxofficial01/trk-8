#ifndef __TRK8_REGISTERS_H
#define __TRK8_REGISTERS_H

#include <stdint.h>

#include "utils.h"

typedef struct _TRK8_REGISTERS {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t x;

    uint8_t sp;

    uint8_t f : 4;

    uint8_t al, ah;

    uint8_t pcl, pch;
} trk8_registers_t;

typedef enum _TRK8_REGISTER_ID {
    TRK8_REGISTER_A,
    TRK8_REGISTER_B,
    TRK8_REGISTER_C,
    TRK8_REGISTER_X,

    TRK8_REGISTER_SP,

    TRK8_REGISTER_F,

    TRK8_REGISTER_AL,
    TRK8_REGISTER_AH,

    TRK8_REGISTER_PCL,
    TRK8_REGISTER_PCH
} trk8_register_id_t;

trk8_registers_t registers_init(void);

uint16_t registers_get_pc_word(const trk8_registers_t registers);

void registers_increment_pc(trk8_registers_t* registers, uint16_t amount);

#endif
