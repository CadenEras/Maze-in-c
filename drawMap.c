//
// Created by gries on 7/3/2022.
//
#include <stdio.h>
#include <SDL.h>
#include "map.h"
#include "drawMap.h"
#include "texture.h"
#include "maze.h"

void cleanRenderer(int red, int green, int blue, int alpha, SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
    SDL_RenderClear(renderer);
}

void drawMap(struct Map* map){
    cleanRenderer(0x5F, 0x38, 0x0D, 255, map->renderer);

    SDL_Rect srcRect;
    srcRect.w = SCREEN_WIDTH / map->columns;
    srcRect.h = SCREEN_HEIGHT / map->lines;

    int column, line, object;
    for (column = 0; column < map->columns; ++column){
        srcRect.x = column * srcRect.w;

        for(line = 0; line < map->lines; ++line){
            srcRect.y = line * srcRect.h;

            object = map->map[column][line];
            if(object != -1){
                if(SDL_RenderCopy(map->renderer, getTextureFromID(object), NULL, &srcRect) < 0){
                    printf("SDL RenderCopy Error: %s\n", SDL_GetError());
                }
            }
        }
    }

    srcRect.x = map->exit.column * srcRect.w;
    srcRect.y = map->exit.line * srcRect.h;
    SDL_RenderCopy(map->renderer, getTextureFromID(2), NULL, &srcRect);

    srcRect.x = map->player.column * srcRect.w;
    srcRect.y = map->player.line * srcRect.h;
    SDL_RenderCopy(map->renderer, getTextureFromID(1), NULL, &srcRect);

}