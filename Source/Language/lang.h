#include "../List/SmartList.h"

#ifndef LANGMANAGER_H
#define LANGMANAGER_H

typedef struct {
    list *binds;
    char **(*getTradById)(char *idToGet);
    void (*loadLang)(char *langId);
    void (*clear)(void);
} langManager;

typedef struct {
    char *id;
    char **trad;
} langBind;

langManager *initLanguageManager();

#endif