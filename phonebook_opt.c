#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "phonebook_opt.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(lastname, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    /* allocate memory for the new entry and put lastName */
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;
    return e;
}

nameEntry *newFindName(char lastname[], nameEntry *pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(lastname, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

nameEntry *newAppend(char lastName[], nameEntry *e)
{
    /* allocate memory for the new entry and put lastName */
    e->pNext = (nameEntry *) malloc(sizeof(nameEntry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;
    return e;
}

hashTable *createHashTable(int tableSize)
{
    hashTable *ht = NULL;
    int i;

    if( tableSize < 1 ){
        return NULL;
    }

    /* Allocate the table itself. */
    if((ht = (hashTable *) malloc(sizeof(hashTable))) == NULL) {
        return NULL;
    }

    /* Allocate array of list. */
    if( (ht->list = (nameEntry **)malloc(sizeof(nameEntry *)*tableSize)) == NULL ) {
        return NULL;
    }

    /* Allocate list header */
    for( i = 0; i < tableSize; i++ ) {
        ht->list[i] = NULL;
    }

    ht->tableSize = tableSize;

    return ht;
}

nameEntry* findNameHash(char *key, hashTable *ht)
{
    nameEntry *ne;
    hi index = hash(key, ht);
    
    /* search the bucket */
    for(ne = ht->list[index]; ne != NULL; ne = ne->pNext){
        if ( strcasecmp(key, ne->lastName) == 0 ){
            return ne;
        }
    }
    return NULL;
}

int appendHash(char *key, hashTable *ht)
{
    hi index = hash(key, ht);
    nameEntry *newEntry;

    /* attempt to allocate memory for nameEntry */
    if ((newEntry = (nameEntry *) malloc(sizeof(nameEntry))) == NULL){
        return 2;
    }

    /* Insert into list */
    strcpy(newEntry->lastName, key);
    newEntry->pNext = ht->list[index];
    ht->list[index] = newEntry;

    return 0;
}

hi hash(char *key, hashTable *ht)
{
    unsigned int hashValue = 0;
    while(*key != '\0'){
        hashValue = (hashValue << 5) + *key++;
    }

    return hashValue % ht->tableSize;
}
