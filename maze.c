//
// Created by gries on 7/3/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>
#include <SDL_events.h>

#include "maze.h"
#include "map.h"
#include "drawMap.h"
#include "texture.h"

void maze(struct Map* map){
    initObjects(map->renderer);

    drawMap(map);
    SDL_RenderPresent(map->renderer);

    SDL_Event event;
    int quit = 0;

    IAshortestPath(map);

    while (quit != 1) {
        SDL_PollEvent(&event);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        quit = 1;
                    } else {
                        onKeyPressed(event.key.keysym.scancode, map);
                    }
                    break;
            }
        }
        /*do {
            if(SDL_WaitEvent(&event) == 0){
                fprintf(stderr, "SDL Event Error: %s\n", SDL_GetError());
                break;
            }

            switch(event.type){
                case SDL_QUIT:
                    quit = 1;
                    break;

                case SDL_KEYDOWN:
                    onKeyPressed(event.key.keysym.scancode, map);
                    break;
            }
        } while(quit != 1);*/
    }
    freeObjects();
}

void onKeyPressed(SDL_Scancode scancode, struct Map* map){
    int move = 1;
    struct Coordinate coordinate;
    coordinate.column = map->player.column;
    coordinate.line = map->player.line;

    switch(scancode){
        case SDL_SCANCODE_UP:
            coordinate.line--;
            break;

        case SDL_SCANCODE_DOWN:
            coordinate.line++;
            break;

        case SDL_SCANCODE_LEFT:
            coordinate.column--;
            break;

        case SDL_SCANCODE_RIGHT:
            coordinate.column++;
            break;

        default:
            move = 0;
    }

    if(move == 1){
        movePlayerTo(&coordinate, map);
    }
}

int canPlayerMove(struct Coordinate* newPosition, struct Map* map){
    if(map->map[newPosition->column][newPosition->line] == -1){
        return 1;
    } else {
        return 0;
    }
}

void movePlayerTo(struct Coordinate* newPosition, struct Map* map){
    if(canPlayerMove(newPosition, map) == 1){
        map->player = *newPosition;
        drawMap(map);
        SDL_RenderPresent(map->renderer);
    }
}


void IAshortestPath(struct Map *map){
    int **tmp_map = calloc(map->columns, sizeof(int*));
    int i, j;

    for(i = 0; i < map->columns; ++i){
        tmp_map[i] = calloc(map->lines, sizeof(int));
        memset(tmp_map[i], -1, map->lines * sizeof(int));
    }


    struct Coordinate *next, *next_tmp;
    struct Coordinate nextTo[4];
    next = malloc(sizeof(struct Coordinate));
    next[0] = map->exit;

    int arraySize = 1, tmpArraySize, found = 0, step = 0;
    do {
        tmpArraySize = 0;
        next_tmp = malloc(0);

        for(i = 0; i < arraySize; ++i){
            tmp_map[next[i].column][next[i].line] = step;

            nextTo[0].column = next[i].column+1;
            nextTo[0].line = next[i].line;
            nextTo[1].column = next[i].column-1;
            nextTo[1].line = next[i].line;
            nextTo[2].column = next[i].column;
            nextTo[2].line = next[i].line+1;
            nextTo[3].column = next[i].column;
            nextTo[3].line = next[i].line-1;

            for(j = 0; j < 4; ++j){
                if(tmp_map[nextTo[j].column][nextTo[j].line] == -1
                   && canPlayerMove(&nextTo[j], map)){
                    next_tmp = realloc(next_tmp, ++tmpArraySize * sizeof(struct Coordinate));
                    next_tmp[tmpArraySize-1] = nextTo[j];

                    if(nextTo[j].column == map->player.column
                       && nextTo[j].line == map->player.line){
                        found = 1;
                    }
                }
            }
        }

        free(next);
        next = next_tmp;
        arraySize = tmpArraySize;
        step++;
    } while(arraySize > 0 && found == 0);
    free(next);

    if(found == 1){
        struct Coordinate coordinate = map->player;
        do {
            step--;

            nextTo[0].column = coordinate.column+1;
            nextTo[0].line = coordinate.line;
            nextTo[1].column = coordinate.column-1;
            nextTo[1].line = coordinate.line;
            nextTo[2].column = coordinate.column;
            nextTo[2].line = coordinate.line+1;
            nextTo[3].column = coordinate.column;
            nextTo[3].line = coordinate.line-1;

            for(j = 0; j < 4; ++j){
                if(tmp_map[nextTo[j].column][nextTo[j].line] == step){
                    SDL_Delay(100);
                    coordinate = nextTo[j];
                    movePlayerTo(&coordinate, map);
                    break;
                }
            }
        } while(coordinate.column != map->exit.column || coordinate.line != map->exit.line);
    } else {
        printf("No path found\n");
    }

    for(i = 0; i < map->columns; ++i){
        free(tmp_map[i]);
    }
    free(tmp_map);
}
