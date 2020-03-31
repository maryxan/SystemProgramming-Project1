#include "comands.h"
#include "hashtable.h"
#include "list.h"

void comands(HashTableBucket** diseaseHashtable , HashTableBucket** countryHashtable , LinkedList* diseaselist , LinkedList* countrylist ,unsigned long int diseaseHashtableNumOfEntries,unsigned long int countryHashtableNumOfEntries, unsigned long int bucketSize){

    char* command;
    char* parameter1;
    char* parameter2;
    char* virus;
    char* vcountry;
    char* ID;
    char* FirstName;
    char* LastName;


    char* line = NULL;
    size_t len = 0;

    putchar(' ');
    putchar('~');

    //read line and execute the given command
    while(getline(&line, & len, stdin) != EOF)
    {
         line = strtok(line, "\n");
         command = strtok(line, " ");

         if(command == NULL)
            {
                continue;
            }

         

        // /globalDiseaseStats [date1 date2]
        else if(strcmp(command, "/globalDiseaseStats") == 0)  
        {

            parameter1 = strtok(NULL," "); 
            parameter2 = strtok(NULL," ");

            if(parameter1 == NULL){
 
                global_disease_stats(diseaselist);

            }

            else if(parameter1 != NULL && parameter2 ==  NULL){

                printf("Parameter2 cannot be NULL\n");
        

            }
            else {

                global_disease_stats_with_param(diseaselist,parameter1,parameter2);

            }


        }

        // /diseaseFrequency virusName date1 date2 [country]
        else if(strcmp(command, "/diseaseFrequency") == 0) //
        {

            virus = strtok(NULL," ");
            parameter1 = strtok(NULL," "); 
            parameter2 = strtok(NULL," ");
            vcountry = strtok(NULL," ");


            if (vcountry == NULL)
            {
             disease_frequency(diseaselist,virus,parameter1,parameter2);

            } else {
   
             disease_frequency_with_param(diseaselist,countrylist,virus,parameter1,parameter2,vcountry);
            }

        }

        //insertPatientRecord recordID patientFirstName patientLastName diseaseID country entryDate [exitDate]
        else if(strcmp(command, "/insertPatientRecord") == 0) 
        {
            ID = strtok(NULL," ");
            FirstName = strtok(NULL," ");
            LastName = strtok(NULL," ");
            virus = strtok(NULL, " ");
            vcountry = strtok(NULL, " ");
            parameter1 = strtok(NULL, " ");
            parameter2 = strtok(NULL, " ");

            if(parameter2 == NULL){

                strcpy(parameter2,"-");
               insert_patient_record(diseaseHashtable,countryHashtable,diseaselist,countrylist,ID,FirstName,LastName,virus,vcountry,parameter1,parameter2,diseaseHashtableNumOfEntries,countryHashtableNumOfEntries,bucketSize);

            }else {

               insert_patient_record(diseaseHashtable,countryHashtable,diseaselist,countrylist,ID,FirstName,LastName,virus,vcountry,parameter1,parameter2,diseaseHashtableNumOfEntries,countryHashtableNumOfEntries,bucketSize);
            }
        }


        // /recordPatientExit recordID exitDate
        else if(strcmp(command, "/recordPatientExit") == 0) 
        {
             ID = strtok(NULL, " ");
             parameter2 = strtok(NULL, " ");
             int isfound;
             
             isfound = record_patient_exit(diseaseHashtable,diseaseHashtableNumOfEntries,ID,parameter2);

             if(isfound){

                printf("Not found\n");
             }   

        }   

        // /numCurrentPatients [disease]
        else if(strcmp(command, "/numCurrentPatients") == 0) 
        {
           
           virus = strtok(NULL, " ");
           int isfound;
           int count;

            if(virus == NULL){

               num_current_patients(diseaseHashtable,diseaselist,diseaseHashtableNumOfEntries);
            }
            else{

               isfound =  num_current_patients_with_param(diseaseHashtable,virus,diseaseHashtableNumOfEntries);

                if(isfound){

                    count = 0;
                    printf("%s %d\n",virus,count);
                }

            }

        }

        // /exit
        else if(strcmp(command, "/exit") == 0)
        {
            printf("exiting\n");
            free_linkedlist(diseaselist);
            free_linkedlist(countrylist);
            free_hashtable(diseaseHashtable,0,diseaseHashtableNumOfEntries);
            free_hashtable(countryHashtable,1,countryHashtableNumOfEntries);

            break;
        }
        else
        {
            //printf("Command doesn't exist. Please try another commad. \n");
            printf("error\n");
        }

        putchar(' ');
        putchar('~');
    }
    free(line);
}   