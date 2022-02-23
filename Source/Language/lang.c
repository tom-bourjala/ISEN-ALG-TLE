#include "lang.h"
#include "../Game/game.h"

langManager *LANG_MANAGER = NULL;

int compareTradId(void *data1, void *data2){
    langBind *A = data1;
    langBind *B = data2;
    return strcmp(A->id, B->id);
}

char **getTradById(char *idToGet)
{
    langBind *request = malloc(sizeof(langBind));
    request->id = idToGet;
    langBind *result = searchDataInList(*LANG_MANAGER->binds, request);
    if(result == NULL)
    {
        request->id = malloc(sizeof(char)*(strlen(idToGet)+1));
        strcpy(request->id, idToGet);
        request->trad = malloc(sizeof(char *));
        *request->trad = malloc(sizeof(char)*(strlen(idToGet)+1));
        strcpy(*request->trad, request->id);
        appendInList(LANG_MANAGER->binds, request);
        return getTradById(idToGet);
    }
    free(request);
    return result->trad;
}

void loadLang(char *langId)
{
    char path[255];
    char strId[255];
    char strTrad[4096];
    char line_cache[4096];
    sprintf(path, "./assets/localisation/%s.csv", langId);
    FILE *csv_file = fopen(path,"r");
    if(!csv_file){
        printf("\033[1;31mLANG ERROR : %s not found.\033[0m\n", path);
    }
    while(fgets(line_cache,4096,csv_file) != NULL)
    {
        sscanf(line_cache,"%[^;];%[^\n]", strId, strTrad);
        char **trad = getTradById(strId);

        *trad = realloc(*trad,sizeof(char)*(strlen(strTrad)+1));
        strcpy(*trad, strTrad);
    }
    fclose(csv_file);
}

void langClear(){
    for(int index = 0; index < LANG_MANAGER->binds->length; index++){
        langBind *b = getDataAtIndex(*LANG_MANAGER->binds, index);
        free(*b->trad);
        free(b->trad);
        free(b->id);
        free(b);
    }
    freeList(LANG_MANAGER->binds);
}

langManager *initLanguageManager() {
    LANG_MANAGER = malloc(sizeof(langManager));
    LANG_MANAGER->binds = newList(compareTradId);
    LANG_MANAGER->getTradById = getTradById;
    LANG_MANAGER->loadLang = loadLang;
    LANG_MANAGER->clear = langClear;
    LANG_MANAGER->loadLang("en_US");
    return LANG_MANAGER;
}