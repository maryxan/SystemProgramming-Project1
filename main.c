#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h"
#include "comands.h"
#include "preprocessing.h"

int main(int argc, char* argv[]) {


    char* patientRecordsFile = NULL;
    unsigned long int diseaseHashtableNumOfEntries = 0;
    unsigned long int countryHashtableNumOfEntries = 0;
    unsigned long int bucketSize = 0;
   
    //Parse arguments from command line
    for(int i = 0; i < argc; i++)
    {
        // Get Records File
        if(strcmp(argv[i], "-p") == 0)
        {
            i++;
            patientRecordsFile = malloc(strlen(argv[i]) * sizeof(char) + 5); // for '\0'
            strcpy(patientRecordsFile, argv[i]);
        }
        
        //Get h1
        else if(strcmp(argv[i], "-h1") == 0)
        {
            i++;
            diseaseHashtableNumOfEntries = strtoul(argv[i], NULL, 10);
        }

        //Get h2
        else if(strcmp(argv[i], "-h2") == 0)
        {
            i++;
            countryHashtableNumOfEntries = strtoul(argv[i], NULL, 10);
        }

        // Get bucket size
        else if(strcmp(argv[i], "-b") == 0)
        {
            i++;
            bucketSize = strtoul(argv[i], NULL, 10);
        }
    } 

    //check if the inputs are valid
    if(!(patientRecordsFile != NULL && diseaseHashtableNumOfEntries != 0 && countryHashtableNumOfEntries != 0 && bucketSize != 0)){

        printf("Wrong inputs: inputs must be like './diseaseMonitor -p patientRecordsFile -h1 diseaseHashtableNumOfEntries -h2 countryHashtableNumOfEntries -b bucketSize' \n");  

    } else

        printf("Starting the program with the following inputs: diseaseHashtableNumOfEntries: %ld , countryHashtableNumOfEntries: %ld , bucketSize : %ld \n",diseaseHashtableNumOfEntries,countryHashtableNumOfEntries,bucketSize);


    //create and initialise hash tables    
    HashTableBucket** diseaseHashtable = initializeHT(diseaseHashtableNumOfEntries);
    HashTableBucket** countryHashtable = initializeHT(countryHashtableNumOfEntries);


    //read input file and set the hts, the lists and the trees
    preprocessing(patientRecordsFile, diseaseHashtable, countryHashtable , bucketSize , diseaseHashtableNumOfEntries, countryHashtableNumOfEntries );
    

    //free
    free(patientRecordsFile);
		
}