#include "preprocessing.h"

void preprocessing(char* inputfile, HashTableBucket** diseaseHashtable , HashTableBucket** countryHashtable ,unsigned long int bucketSize , unsigned long int diseaseHashtableNumOfEntries , unsigned long int countryHashtableNumOfEntries){

	char recordID[100];
	char patientFirstName[100];
    char patientLastName[100];
    char diseaseID[100];
    char country[100];
    char entryDate[100];
    char exitDate[100];

	//open the file to read it
	FILE* patientRecordsFile = fopen(inputfile,"r");

	if (patientRecordsFile == NULL) 
    { 
        printf("Could not open file"); 
    } 

    //Start reading the file line by line
    char* line = NULL;
    size_t len = 0;

    //allocate tous 2 prwtous komvous
    LinkedList* diseaselist = allocate_list();
    LinkedList* countrylist = allocate_list();

    while (getline(&line, &len, patientRecordsFile) != EOF) {


        entry* info = malloc (sizeof(entry)); // ftiaxnw ena struct me ta stoixeia tis kathe eggrafis
        sscanf(line, "%s %s %s %s %s %s %s", info->recordID, info->patientFirstName, info->patientLastName, info->diseaseID, info->country, info->entryDate, info->exitDate);        //recordID = strtok(line, " ");
        

        //------------------------ check if entry date, exit date and ID are valid -------------------------

        char date1[100];
        char date2[100];
        
        strcpy(date1,info->entryDate);
        strcpy(date2,info->exitDate);
        

        if(check_dates(date1,date2)){

            printf("Invalid dates.This line will be skipped\n");
            continue;
        } 
        
        if(check_record_id(diseaseHashtable,info->recordID,diseaseHashtableNumOfEntries)){

            printf("Duplicate recordID was found.Exiting..\n");
            exit(0);
        }

        //----------------------------------------------------------------------------------------------

        entry *ref1 , *ref2;
        ref1 = info;
        ref2 = info;

        
      
        //hash the values diseaseID and country 
        unsigned long int disease_index = hash_function(info->diseaseID,diseaseHashtableNumOfEntries);
        unsigned long int country_index = hash_function(info->country,countryHashtableNumOfEntries);


        //insert the values to the ht
        insert_to_ht(diseaseHashtable, ref1 , bucketSize , diseaseHashtableNumOfEntries ,disease_index);
        insert_to_ht(countryHashtable, ref2 , bucketSize , countryHashtableNumOfEntries ,country_index);


        //init list and insert the pointers to it
        linkedlist_insert(diseaselist,ref1,0);
        linkedlist_insert(countrylist,ref2,1);


            
         
    }

    //run commands
    comands(diseaseHashtable,countryHashtable,diseaselist,countrylist,diseaseHashtableNumOfEntries,countryHashtableNumOfEntries,bucketSize);
    fclose(patientRecordsFile);
    free(line);
}




//checks if a given record ID already exists
int check_record_id(HashTableBucket** diseaseHashtable, char* ID, unsigned long int diseaseHashtableNumOfEntries){

    Bucket* bucket;

    //gia oles tis theseis tou ht 
    for (int i = 0; i < diseaseHashtableNumOfEntries; i++) {


        if(diseaseHashtable[i]->bucket == NULL){

            continue;
        }
        else if(diseaseHashtable[i]->bucket != NULL) {
              
            bucket = diseaseHashtable[i]->bucket;

            while (bucket!=NULL){
   
                for(int i = 0; i < bucket->currRecords; i++){


                        if(bucket->records[i] == NULL){

                            continue;
                        }
                        if(strcmp(bucket->records[i]->recordID,ID)== 0){

                         return 1;

                        }
                }
                   
                bucket = bucket->next;

            }
        }

    }
    return 0;

}