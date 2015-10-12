#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* original version */
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    struct __PHONE_BOOK_ENTRY *pNext;
} entry;
/*new smaller entey for recording lastname only*/
typedef struct __NAME_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    entry* data;
    struct __NAME_ENTRY *pNext;
} nameEntry;

entry *findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *e);

/*functions for new entry*/
nameEntry *newFindName(char lastname[], nameEntry *pHead);
nameEntry *newAppend(char lastName[], nameEntry *e);

/*hast table*/
typedef unsigned int hi;/*hash index*/
typedef struct __NAME_HASH_TABLE {
    unsigned int tableSize;  /* the size of the table */
    nameEntry **list;  /* the table elements */
} hashTable;

hashTable *createHashTable(int tableSize);
nameEntry* findNameHash(char *key, hashTable *ht);
int appendHash(char *key, hashTable *ht);
hi hash(char *key, hashTable *ht);
#endif
