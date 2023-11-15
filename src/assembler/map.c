#include "include/map.h"

map_t* map_init() {
    map_t* map = calloc(1, sizeof(struct MAP));

    map->size = 0;

    return map;
}

int map_get_key_index(map_t* map, char* key) {
    for (int i = 0; i < map->size; i++) {
        if (strcmp(map->keys[i], key) == 0) {
            return i;
        }
    }

    return -1;
}

void map_insert(map_t* map, char* key, int value) {
    int index = map_get_key_index(map, key);

    if (index == -1) {
        strcpy(map->keys[map->size], key);
        map->values[map->size] = value;

        map->size++;
    }

    map->values[index] = value;
}

int map_get(map_t* map, char* key) {
    int index = map_get_key_index(map, key);

    if (index == -1) {
        printf("No value assigned to key: '%s'\n", key);
        exit(-1);
    }

    return map->values[index];
}