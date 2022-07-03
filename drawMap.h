//
// Created by gries on 7/3/2022.
//
#ifndef DRAWMAP_H
#define DRAWMAP_H

#include <SDL.h>
#include "map.h"

void drawMap(struct Map*);
void cleanRenderer(int red, int green, int blue, int alpha, SDL_Renderer* renderer);

#endif
