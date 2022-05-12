#include "UI_keyBindings.h"

/*
 * Global variables needed for the project
 */

static list *bindings;

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

list *KB_init() {
    return bindings = newList(Comparator);
}

void KB_free() {
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
    void* search(void *haystack) {
        keyBinding *d = haystack;
        if (d->key == key) {
            pushInList(r, &d->input);
        }
        return r;
    }
    forEach(bindings, search);
    return r;
}

list *KB_getKeys(gameInput input) {
    list *r = newList(COMPARE_PTR);
    void* search(void *haystack) {
        keyBinding *d = haystack;
        if (d->input == input) {
            pushInList(r, &d->key);
        }
        return r;
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

static void printList(list *r) {
    forEach(r, printing);
}

void printed() {
    printList(bindings);
}