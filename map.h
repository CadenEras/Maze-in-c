//
// Created by gries on 7/3/2022.
//

#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <stdint.h>

struct Coordinate {
    int16_t column, line;
};

struct Map {
    int16_t columns, lines;
    int size;
    struct Coordinate player, exit;
    int8_t **map;

    struct Coordinate *_update;
    SDL_Renderer *renderer;
};

#endif
