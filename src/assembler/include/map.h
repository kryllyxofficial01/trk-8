#ifndef __MAP_H
#define __MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MAP_SIZE 100

typedef struct MAP {
    char keys[MAX_MAP_SIZE][2048];
    int values[MAX_MAP_SIZE];

    int size;
} map_t;

map_t* map_init();

int map_get_key_index(map_t* map, const char* key);
void map_insert(map_t* map, const char* key, int value);
int map_get(map_t* map, const char* key);

#endif