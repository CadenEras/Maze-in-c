// Created by Melissa Gries (CadenEras).
#include "maze.h"
#include "texture.h"
#include "map.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <malloc.h>
#include <windows.h>

struct Map* loadMap(const char* src, SDL_Renderer *renderer){
    int fd = open(src, O_RDONLY);
    if(fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct stat stat;
    if(fstat(fd, &stat) == -1){
        perror("stat");
        exit(EXIT_FAILURE);
    }

    if(stat.st_size < 14){
        fprintf(stderr, "Corrupted map file");
        exit(EXIT_FAILURE);
    }

    int16_t version, lines, columns;

    read(fd, &version, 2);
    if(version != 1){
        fprintf(stderr, "Incompatible/Corrupted map file");
        exit(EXIT_FAILURE);
    }

    struct Map *map;
    map = malloc(sizeof(struct Map));

    read(fd, &map->columns, 2);
    read(fd, &map->lines, 2);

    read(fd, &map->player.column, 2);
    read(fd, &map->player.line, 2);
    read(fd, &map->exit.column, 2);
    read(fd, &map->exit.line, 2);

    map->size = map->columns * map->lines;
    map->renderer = renderer;

    if(stat.st_size < (14 + map->size)){
        fprintf(stderr, "Corrupted map file");
        exit(EXIT_FAILURE);
    }

    int8_t* rawMap = calloc(map->size, sizeof(int8_t));
    read(fd, rawMap, map->size);

    map->map = calloc(map->columns, sizeof(int8_t*));

    int column, line;
    for(column = 0; column < map->columns; column++){
        map->map[column] = (int8_t*) calloc(map->lines, sizeof(int8_t));
        for(line = 0; line < map->lines; line++){
            map->map[column][line] = rawMap[(map->lines * column + line)];
        }
    }

    free(rawMap);

    return map;
}

void freeMap(struct Map* map){
    int i;
    for(i = 0; i < map->columns; i++){
        free(map->map[i]);
    }

    SDL_DestroyRenderer(map->renderer);

    free(map->map);
    free(map);
}

int main(int argc, char* argv[]){
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    int continu = 1;

    int img_flags = IMG_INIT_PNG;

    ////////////////////////////////////////////////
    //          Initializing the SDL              //
    ////////////////////////////////////////////////
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "SDL could not be initialized : %s\n", SDL_GetError()); //In case of an error
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        fprintf(stderr,"Window could not be created ! SDL_Error : %s\n", SDL_GetError()); //in case of an error : The return
        exit(EXIT_FAILURE);
    }

    int playerPos[2] = {1, 1}, exitPos[2] = {8, 8};
    struct Map *map = loadMap("./map", renderer);

    maze(map);

    while (continu) {
        SDL_PollEvent(&event);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    continu = 0;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        continu = 0;
                    }
                    break;
            }
        }
        SDL_UpdateWindowSurface(window);
    }

    freeMap(map);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return(EXIT_SUCCESS);
}
