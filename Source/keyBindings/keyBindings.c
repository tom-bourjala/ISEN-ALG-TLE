#include "keyBindings.h"
#include "../Game/game.h"

/*
 * Global variables needed for the project
 */

static list *bindings = NULL;
static list* keyCodeTextureAsso = NULL;

/*
 * Search function for the library to work properly
 */

int Comparator(void *needle, void *data) {
    keyBinding *n1 = needle;
    keyBinding *n2 = data;
    if (n1->key == n2->key && n1->input == n2->input) {
        return 0;
    }
    return 1;
}

/*
 * Functions required for the library
 */

int getKBEnumFromString(char *string)
{
    if(!strcmp(string,"GA_UP")){return GA_UP;}
    if(!strcmp(string,"GA_DOWN")){return GA_DOWN;}
    if(!strcmp(string,"GA_LEFT")){return GA_LEFT;}
    if(!strcmp(string,"GA_RIGHT")){return GA_RIGHT;}
    if(!strcmp(string,"GA_PAUSE")){return GA_PAUSE;}
    if(!strcmp(string,"GA_UPGRADE")){return GA_UPGRADE;}
    if(!strcmp(string,"GA_SELL")){return GA_SELL;}
    if(!strcmp(string,"GA_ZOOMIN")){return GA_ZOOMIN;}
    if(!strcmp(string,"GA_ZOOMOUT")){return GA_ZOOMOUT;}
    if(!strcmp(string,"GA_TURRET1")){return GA_TURRET1;}
    if(!strcmp(string,"GA_TURRET2")){return GA_TURRET2;}
    if(!strcmp(string,"GA_TURRET3")){return GA_TURRET3;}
}

list *KB_init(void *self) {
    Game *game = self;
    bindings = newList(Comparator);
    FILE *keys_file = fopen("keybindings.kb","r");
    int count_input = 1;
    char *line = malloc(sizeof(char)*255);
    while(fgets(line,255,keys_file)!=NULL)
    {
        
        char *action = malloc(sizeof(char)*255);
        char *char_sdlk = malloc(sizeof(char)*255);
        sscanf(line,"%[^ ] %[^\n]",action,char_sdlk);
        int int_sdlk = atoi(char_sdlk);
        int kbEnum = getKBEnumFromString(action);
        KB_add(int_sdlk,count_input);
        free(action);
        free(char_sdlk);
        count_input++;
    }
    free(line);
    fclose(keys_file);

    keyTexture *temp = NULL;
    keyCodeTextureAsso = newList(COMPARE_PTR);
    temp = malloc(sizeof(keyTexture));
    *temp = (keyTexture){SDLK_UP,game->textureManager->getTexture("UI_icon_key_move_up.png")};
    appendInList(keyCodeTextureAsso,temp);
    temp = malloc(sizeof(keyTexture));
    *temp = (keyTexture){SDLK_DOWN,game->textureManager->getTexture("UI_icon_key_move_down.png")};
    appendInList(keyCodeTextureAsso,temp);
    temp = malloc(sizeof(keyTexture));
    *temp = (keyTexture){SDLK_LEFT,game->textureManager->getTexture("UI_icon_key_move_left.png")};
    appendInList(keyCodeTextureAsso,temp);
    temp = malloc(sizeof(keyTexture));
    *temp = (keyTexture){SDLK_RIGHT,game->textureManager->getTexture("UI_icon_key_move_right.png")};
    appendInList(keyCodeTextureAsso,temp);

    return bindings;
}

void saveKeysInFile(void *self)
{
    keyBinding *k = self;
    FILE *keys_file = fopen("keybindings.kb","a");
    char *string = malloc(sizeof(char)*255);
    switch(k->input)
    {
        case GA_UP:
            strcpy(string,"GA_UP");
            break;
        case GA_DOWN:
            strcpy(string,"GA_DOWN");
            break;
        case GA_LEFT:
            strcpy(string,"GA_LEFT");
            break;
        case GA_RIGHT:
            strcpy(string,"GA_RIGHT");
            break;
        case GA_PAUSE:
            strcpy(string,"GA_PAUSE");
            break;
        case GA_SELL:
            strcpy(string,"GA_SELL");
            break;
        case GA_UPGRADE:
            strcpy(string,"GA_UPGRADE");
            break;
        case GA_ZOOMIN:
            strcpy(string,"GA_ZOOMIN");
            break;
        case GA_ZOOMOUT:
            strcpy(string,"GA_ZOOMOUT");
            break;
        case GA_TURRET1:
            strcpy(string,"GA_TURRET1");
            break;
        case GA_TURRET2:
            strcpy(string,"GA_TURRET2");
            break;
        case GA_TURRET3:
            strcpy(string,"GA_TURRET3");
            break;
    }
    fprintf(keys_file,"%s %d\n",string,k->key);
    fclose(keys_file);
}

void KB_free() {
    FILE *keys_file = fopen("keybindings.kb","w");
    fclose(keys_file);
    forEach(bindings, saveKeysInFile);
    
    forEach(bindings, free);
    freeList(bindings);
}

void KB_add(SDL_Keycode key, gameInput input) {
    keyBinding *kb = malloc(sizeof(keyBinding));
    kb->key = key;
    kb->input = input;
    appendInList(bindings, kb);
}

void KB_removeKeyBinding(keyBinding *kb) {
    deleteInList(bindings, kb);
}

list *KB_getInputs(SDL_Keycode key) {
    list *r = newList(COMPARE_PTR);
    void search(void *haystack) {
        keyBinding *d = haystack;
        if (d->key == key) {
            pushInList(r, &d->input);
        }
    }
    forEach(bindings, search);
    return r;
}

list *KB_getKeys(gameInput input) {
    list *r = newList(COMPARE_PTR);
    void search(void *haystack) {
        keyBinding *d = haystack;
        if (d->input == input) {
            pushInList(r, &d->key);
        }
    }
    forEach(bindings, search);
    return r;
}

keyBinding *KB_getKeyBinding(SDL_Keycode key, gameInput input) {
    keyBinding *kb = malloc(sizeof(keyBinding));
    kb->key = key;
    kb->input = input;
    printf("\033[1;31mSmartList_DEBUG : ITEM DATA %p\n\033[0m", (void*)kb);
    keyBinding *r = searchDataInList(*bindings, kb);
    if (r != NULL) {
        return r;
    } else {
        return NULL;
    }
}

static void printing(void *kb) {
    keyBinding *this = kb;
    if (kb != NULL) {
        printf("%d %d\n", this->key, this->input);
    } else {
        printf("KB is null\n");
    }
}

void printList(list *r) {
    forEach(r, printing);
}

void printed() {
    printList(bindings);
}

static void (*callback)(SDL_Keycode code,void *data) = NULL;
static void *data = NULL;

void KB_getInput(void (*cb)(SDL_Keycode code,void *data),void *d)
{
    if(callback) callback(-1,data);
    callback = cb;
    data = d;
}

void KB_handleKeyCode(SDL_Keycode code)
{
    
    if(callback)
    {
        callback(code,data);
        callback = NULL;
        data = NULL;
    }
}

list *KB_getKCTA()
{
    return keyCodeTextureAsso;
}