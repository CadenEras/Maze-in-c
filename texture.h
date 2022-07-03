#ifndef TEXTURES_H
#define TEXTURES_H

#define OBJECTS_COUNT 3

int initObjects(SDL_Renderer* renderer);
void freeObjects(void);

SDL_Texture* getTextureFromID(int);

#endif
