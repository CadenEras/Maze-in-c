//
// Created by gries on 7/3/2022.
//

#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#include "maze.h"

int initialized = 0;

SDL_Texture **objectsTex;

SDL_Texture* getTextureFromID(int id){
    if(id >= OBJECTS_COUNT || id < 0){
        return NULL;
    }

    return objectsTex[id];
}

int initObjects(SDL_Renderer* renderer){
    if(initialized == 0){
        SDL_Surface *tmpSurf;
        objectsTex = calloc(OBJECTS_COUNT, sizeof(SDL_Texture*));

        tmpSurf = IMG_Load("resources/brick_wall.png");
        objectsTex[0] = SDL_CreateTextureFromSurface(renderer, tmpSurf);
        SDL_FreeSurface(tmpSurf);

        tmpSurf = IMG_Load("resources/mario.png");
        objectsTex[1] = SDL_CreateTextureFromSurface(renderer, tmpSurf);
        SDL_FreeSurface(tmpSurf);

        tmpSurf = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 255);
        SDL_FillRect(tmpSurf, NULL, SDL_MapRGB(tmpSurf->format, 0, 255, 0));
        objectsTex[2] = SDL_CreateTextureFromSurface(renderer, tmpSurf);
        SDL_FreeSurface(tmpSurf);

        initialized = 1;
    }

    return initialized;
}

void freeObjects(void){
    int i;
    for (i = 0; i < OBJECTS_COUNT; ++i){
        SDL_DestroyTexture(objectsTex[i]);
    }

    free(objectsTex);

    initialized = 0;
}