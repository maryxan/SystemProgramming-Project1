#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>


#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct
{
	char recordID[100];
	char patientFirstName[100];
    char patientLastName[100];
    char diseaseID[100];
    char country[100];
    char entryDate[100];
    char exitDate[100];

}entry;


typedef struct Bucket
{
	int currRecords;
	int recordsNum;
	struct Bucket *next;
	entry **records;

}Bucket;


typedef struct HashTableBucket{
	int recs;                       
    Bucket* bucket;                  
    unsigned long int size;
    struct HashTableBucket* next;
}HashTableBucket;



HashTableBucket** initializeHT(unsigned long int ht_size);
void insert_to_ht(HashTableBucket** ht, entry* ref ,unsigned long int bucketSize, unsigned long int size,unsigned long int index);
unsigned long hash_function(char* str, unsigned long int size);

Bucket* create_bucket(unsigned long int bucketSize, unsigned long int recs_per_bucket);
void insert_to_bucket(Bucket *bucket , entry* ref);
int get_bucket_number_of_items(Bucket *bucket);

void free_hashtable(HashTableBucket** table, int deleteEntries,unsigned long int size);
void free_bucket(Bucket *bucket , int deleteEntries);

#endif 
