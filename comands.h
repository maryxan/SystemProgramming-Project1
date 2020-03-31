#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "hashtable.h"
#include "commandfunctions.h"
#include "list.h"


#ifndef COMANDS_H
#define COMANDS_H

void comands(HashTableBucket** diseaseHashtable , HashTableBucket** countryHashtable , LinkedList* diseaselist , LinkedList* countrylist,unsigned long int diseaseHashtableNumOfEntries,unsigned long int countryHashtableNumOfEntries,unsigned long int bucketSize);




#endif