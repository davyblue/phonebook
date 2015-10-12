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

typedef struct __NAME_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    entry* data;
    struct __NAME_ENTRY *pNext;
} nameEntry;

entry *findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *e);
nameEntry *newFindName(char lastname[], nameEntry *pHead);
nameEntry *newAppend(char lastName[], nameEntry *e);


#endif
