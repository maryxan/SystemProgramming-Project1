#include "list.h"


#ifndef COMANDFUNCTIONS_H
#define COMANDFUNCTIONS_H

void global_disease_stats(LinkedList* list);
void global_disease_stats_with_param(LinkedList* list , char* parameter1 , char* parameter2);

void disease_frequency(LinkedList* list ,char *virus ,char *parameter1 , char* parameter2);
void disease_frequency_with_param(LinkedList* diseaselist, LinkedList* countrylist ,char *virus ,char *parameter1 , char* parameter2 , char* vcountry);

void insert_patient_record(HashTableBucket** diseaseHashtable,HashTableBucket** countryHashtable,LinkedList* diseaselist, LinkedList* countrylist, char* ID, char* FirstName, char* LastName, char* virus, char* vcountry, char* parameter1, char* parameter2 ,unsigned long int diseaseHashtableNumOfEntries,unsigned long int countryHashtableNumOfEntries,unsigned long int bucketSize);

void num_current_patients(HashTableBucket** diseaseHashtable,LinkedList * list,unsigned long int diseaseHashtableNumOfEntries);
int num_current_patients_with_param(HashTableBucket** diseaseHashtable,char* virus,unsigned long int diseaseHashtableNumOfEntries);

int record_patient_exit(HashTableBucket** diseaseHashtable,unsigned long int diseaseHashtableNumOfEntries,char* ID , char* parameter2);


//--------------------- voithitikes--------------------------------
int get_node_count(LinkedList* head); 
int get_tree_nodes_count(avltreenode *root); 
int find_count_in_range(avltreenode *root, char* d1, char* d2);
int find_count_in_range_for_country(avltreenode *node, char *date1, char *date2, char *country);
	
#endif