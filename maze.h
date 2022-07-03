#ifndef MAZE_H
#define MAZE_H

#include <SDL.h>
#include "map.h"

#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480

void maze(struct Map*);
void onKeyPressed(SDL_Scancode, struct Map*);
int canPlayerMove(struct Coordinate* newPosition, struct Map* map);
void movePlayerTo(struct Coordinate*, struct Map*);
void IAshortestPath(struct Map *map);

#endif