
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "date.h"
#include "list.h"
#include "avl.h"
#include "hashtable.h"
#include "comands.h"

void preprocessing(char* inputfile, HashTableBucket** diseaseHashtable , HashTableBucket** countryHashtable , unsigned long int bucketSize, unsigned long int diseaseHashtableNumOfEntries,unsigned long int countryHashtableNumOfEntries);
int check_record_id(HashTableBucket** diseaseHashtable, char* ID,unsigned long int diseaseHashtableNumOfEntries);