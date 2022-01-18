#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../List/SmartList.h"
#include "textureManager.h"

textureManager *TEXTURE_MANAGER = NULL;

int compareNames(void *data1, void *data2){
    char *str1 = ((texture*)data1)->name;
    char *str2 = ((texture*)data2)->name;
    return strcmp(str1, str2);
}

list *loadAllTextures(SDL_Renderer *renderer){
    list *textures = newList(compareNames);
    DIR* repertory = opendir("./assets/tex");
    struct dirent* readfile = NULL;
    if(!repertory)
        perror("\033[1;31mTextureManager_ERROR : Can't open texture directory\n\033[0m");
    while ((readfile = readdir(repertory)) != NULL)
    {
        if(strcmp(readfile->d_name, ".") && strcmp(readfile->d_name, "..")){
            printf("Loading Texture - '%s'...\n", readfile->d_name);
            
            texture *loaded_texture = malloc(sizeof(texture));
            loaded_texture->name = malloc(sizeof(char) * strlen(readfile->d_name) + 1);
            strcpy(loaded_texture->name, readfile->d_name);

            char texturePath[255];
            sprintf(texturePath, "./assets/tex/%s", loaded_texture->name);
            loaded_texture->texture = IMG_LoadTexture(renderer, texturePath);
            if(!loaded_texture->texture) printf("\033[1;31m%s\n\033[0m", SDL_GetError());
            appendInList(textures, loaded_texture);
        }
    }
    return textures;
}

SDL_Texture *getTexture(char *name, int modifier){
    texture *request = malloc(sizeof(texture));
    request->name = name;
    texture *data = searchDataInList(*TEXTURE_MANAGER->texList, request);
    return data->texture;
    // if(!modifier) return data->texture;
    // else{
    //  SDL_Texture *sprite=NULL;
    //  SDL_QueryTexture(texture_voulue, NULL, NULL, &image_tourelle->longueur,&image_tourelle->largeur);
    // }
}

void clearTexture(void *data){
    texture *texture = data;
    SDL_DestroyTexture(texture->texture);
    free(texture->name);
    free(texture);
}

void clearTextures(){
    forEach(TEXTURE_MANAGER->texList, clearTexture);
}

textureManager *initTexManager(SDL_Renderer *renderer){
    textureManager *newManager = malloc(sizeof(textureManager));
    TEXTURE_MANAGER = newManager;
    newManager->texList = loadAllTextures(renderer);
    newManager->getTexture = getTexture;
    newManager->empty = clearTextures;
    return newManager;
}