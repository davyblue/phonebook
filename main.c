#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>

#include IMPL

#define DICT_FILE "./dictionary/words.txt"

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

    /* build the entry */
    /*entry *pHead, *e;
    pHead = (entry *) malloc(sizeof(entry));
    printf("size of entry : %lu bytes\n", sizeof(entry));
    e = pHead;
    e->pNext = NULL;*/
    int tableSize = 32749;
    hashTable *ht = createHashTable(tableSize);
    printf("hash table size (prime number) : %d\n", tableSize);
    nameEntry *pHead;//, *e;
    pHead = (nameEntry *) malloc(sizeof(nameEntry));
    printf("size of entry : %lu bytes\n", sizeof(nameEntry));
    //e = pHead;
    //e->pNext = NULL;

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(nameEntry));
#endif
    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
        if(appendHash(line, ht) == 2){
	    printf("append data fail!");
	}
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);

    /* close file as soon as possible */
    fclose(fp);

    //e = pHead;

    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = "zyxel";
    //e = pHead;

    assert(findNameHash(input, ht) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findNameHash(input, ht)->lastName, "zyxel"));

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(nameEntry));
#endif
    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    findNameHash(input, ht);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);
    printf("execution time of appendHash() : %lf sec\n", cpu_time1);
    printf("execution time of findNameHash() : %lf micro sec\n", cpu_time2*1000);
    printf("pid = %d\n" , getpid());

    /* FIXME: release all allocated entries */
    free(pHead);

    return 0;
}
