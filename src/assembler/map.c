#include "include/map.h"

map_t* map_init() {
    map_t* map = calloc(1, sizeof(struct MAP));

    map->current_index = 0;

    return map;
}

int map_get_key_index(map_t* map, char* key) {
    for (int i = 0; i < MAX_MAP_SIZE; i++) {
        if (strcmp(map->keys[i], key)) {
            return i;
        }
    }

    return -1;
}

void map_insert(map_t* map, char* key, int value) {
    int index = map_get_key_index(map, key);

    if (index >= 0) {
        map->values[index] = value;
    }
    else {
        strcpy(map->keys[map->current_index], key);
        map->values[map->current_index] = value;
    }

    map->current_index++;
}

int map_get(map_t* map, char* key) {
    int index = map_get_key_index(map, key);

    if (index >= 0) {
        return map->values[index];
    }
    else {
        printf("No value assigned to key: '%s'\n", key);
        exit(-1);
    }
}