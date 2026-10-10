program = bytes([
    0b10000001, 0b00000101,             # mov %a, 5
    0b10000011, 0b00000101,             # mov %b, 5
    0b00000110,                         # cmp
    0b11000000, 0b00010000, 0b00000000, # lda 0x0010
    0b00001010,                         # bze
    0b10000001, 0b01100011,             # mov %a, 99
    0b00001011,                         # hlt
    0b00000001,                         # nop
    0b00000001,                         # nop
    0b00000001,                         # nop
    0b00000001,                         # nop
    0b10000001, 0b00000001,             # mov %a, 1
    0b00001011                          # hlt
])

with open("program.trk8", "wb") as f:
    f.write(program)