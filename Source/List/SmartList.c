/**
 * @file SmartList.c
 * @brief Functions for the management of lists
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include "SmartList.h"

/**
 * @brief init chain item
 * 
 * @param[in] data pointer to data to stock in item
 * @return chainItem pointer to allocated memory for intialized chain item 
 */
chainItem *newChainItem(void *data){
    chainItem *newItem = malloc(sizeof(chainItem));
    newItem->data = data;
    newItem->previous = NULL;
    newItem->next = NULL;
    return newItem;
}

list *newList(compareTwoPointersFunction comparatorFunction){
    list *theNewList = malloc(sizeof(list));
    theNewList->first = NULL;
    theNewList->last = NULL;
    theNewList->length = 0;
    theNewList->comparator = comparatorFunction;
    return theNewList;
}

chainItem *getItemAtIndex(list list, int index){
    if(index < 0 || index > list.length - 1) return NULL;
    chainItem *target = list.first;
    int n = 0;
    while(target != NULL && n < index){
        target = target->next;
        n++;
    }
    return target;
}

void *getDataAtIndex(list list, int index){
    if(index < 0)
        printf("\033[1;31mSmartList_ERROR : Get Data at negative index\n\033[0m");
    void *data = getItemAtIndex(list, index)->data;
    return data;
}

/**
 * @brief Put an item at specified index and update the list architecture to support it
 * 
 * @param[in] list 
 * @param[in] item 
 * @param[in] index 
 */
void putItemAtIndex(list *list, chainItem *item, int index){
    if(index < 0)
        printf("\033[1;31mSmartList_ERROR : Put Item at negative index\n\033[0m");
    if(item == NULL || list->length < index) return;
    item->previous = getItemAtIndex(*list, index-1);
    item->next = getItemAtIndex(*list, index);
    item->index = index;

    if(item->previous != NULL)
        item->previous->next = item;
    if(item->next != NULL)
        item->next->previous = item;

    if(index == 0) list->first = item;
    if(index == list->length-1) list->last = item;
    list->length++;
}

void deleteItemAtIndex(list *list, int index){
    if(index < 0)
        printf("\033[1;31mSmartList_ERROR : Delete Item at negative index (%d)\n\033[0m", index);
    if(list->length < index) return;
    chainItem *item = getItemAtIndex(*list, index);
    if(item->previous)
        item->previous->next = item->next;
    if(item->next)
        item->next->previous = item->previous;
    if(index == 0) list->first = item->next;
    if(index == list->length-1) list->last = item->previous;
    list->length--;
    free(item);
}

void pushInList(list *list, void *data){
    chainItem *newItem = newChainItem(data);
    putItemAtIndex(list, newItem, 0);
}

void appendInList(list *list, void *data){
    chainItem *newItem = newChainItem(data);
    putItemAtIndex(list, newItem, list->length);
}

void appendAtInList(list *list, void *data, int index){
    chainItem *newItem = newChainItem(data);
    putItemAtIndex(list, newItem, index);
}

chainItem *searchItemInList(list list, void *data){
    chainItem *item = list.first; 
    while(item != NULL){
        if(list.comparator(item->data, data) == 0) return item;
        item = item->next;
    }
    return NULL;
}

int searchIndexInList(list list, void *data){
    chainItem *result = searchItemInList(list, data);
    if(result == NULL) return -404;
    chainItem *item = list.first; 
    int index = 0;
    while(item != NULL){
        if(list.comparator(item->data, data) == 0) return index;
        item = item->next;
    }
    printf("\033[1;31mSmartList_ERROR : Inconsistant search results between searchItemInList and searchIndexInList(%p)\n\033[0m", data);
    return -404;
}

void *searchDataInList(list list, void *data){
    chainItem *result = searchItemInList(list, data);
    if(result == NULL) return NULL;
    return searchItemInList(list, data)->data;
}

void deleteInList(list *list, void *data){
    int index = searchIndexInList(*list, data);
    if(index != -404) deleteItemAtIndex(list, index);
    else printf("\033[1;31mSmartList_ERROR : Item to Delete not found (%p)\n\033[0m", data);
}

void emptyList(list *list){
    while(list->length > 0) deleteItemAtIndex(list, 0);
}

void forEach(list *list, void (*function)(void *data)){
    chainItem *item = list->first; 
    while(item != NULL){
        function(item->data);
        item = item->next;
    }
}