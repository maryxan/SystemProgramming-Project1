#include "hashtable.h"
#include <stdio.h>

// ------------------------------- functions to init and insert into a HT ---------------------------------------------------------


//a simple hash function, that sums the ASCII value of the string.
unsigned long hash_function(char* str , unsigned long int size) {
    unsigned long i = 0;
    for (int j=0; str[j]; j++)
        i += str[j];
    return i % size;
}



HashTableBucket** initializeHT(unsigned long int ht_size){

    HashTableBucket** ht = malloc(ht_size*sizeof(HashTableBucket*));

    for(int i=0; i<ht_size; i++){
        ht[i] = malloc(sizeof(HashTableBucket));
        ht[i]->recs = 0;
        ht[i]->next = NULL;
        ht[i]->bucket = NULL;
    }

    return ht;
}


void insert_to_ht(HashTableBucket** ht, entry* ref,unsigned long int bucketSize, unsigned long int size , unsigned long int index){
	Bucket* bucket;
    Bucket* current;
    int recs_per_bucket = bucketSize/sizeof(entry);
    int position;
    


    //an den uparxei kanena record se auth th thesh tou hash table
	if(ht[index]->bucket == NULL){
        ht[index]->bucket = create_bucket(bucketSize,recs_per_bucket);// create and init bucket
       insert_to_bucket(ht[index]->bucket , ref);
    }
    //an uparxei record
    else{
    	//koitaw an uparxei xwros sto bucke
    	if( get_bucket_number_of_items(ht[index]->bucket) < recs_per_bucket){	
            insert_to_bucket(ht[index]->bucket , ref);
        }
    	//an oxi,ftiaxnw neo bucket
    	else {
            current=ht[index]->bucket;
            while (current->next!=NULL){
                current = current->next;
            }
            if ( get_bucket_number_of_items(current) < recs_per_bucket ){
                insert_to_bucket(current , ref);
            }
            else {
                current->next = create_bucket(bucketSize,recs_per_bucket);
                insert_to_bucket(current->next, ref);
            }
		}

    }
}

//----------------------------------------functions to create and init a bucket-----------------------------------------------------

//creates and inits a bucket
Bucket* create_bucket(unsigned long int bucketSize, unsigned long int recs_per_bucket){
    Bucket* bucket = malloc(sizeof(Bucket));
    entry ** records = malloc(sizeof(entry*)*recs_per_bucket);

    bucket-> currRecords = 0;
    bucket-> recordsNum = recs_per_bucket;
    bucket-> next = NULL;
    bucket-> records = records;

    return bucket;
}

void insert_to_bucket(Bucket *bucket , entry* ref){
    
    bucket->records[bucket->currRecords] = ref;
    bucket->currRecords++;
}

int get_bucket_number_of_items(Bucket *bucket){

    return (bucket-> currRecords);
}


//---------------------------------------- functions to free the hashtables and the buckets-----------------------------------------------

void free_bucket(Bucket *bucket , int deleteEntries) {

    if(bucket!=NULL){

        if (deleteEntries)
        {
            for (int i = 0; i < bucket->currRecords; i++)
            {
                free(bucket->records[i]);
            }
        }
        free_bucket(bucket->next,deleteEntries);
        free(bucket->records);
        free(bucket);
    }

}

void free_hashtable(HashTableBucket** table, int deleteEntries , unsigned long int size) {

    for (int i=0; i < size; i++) {

        Bucket* bucket = table[i]->bucket;
        if (bucket != NULL)
            free_bucket(bucket,deleteEntries);
        free(table[i]);
    }
    free(table);
}