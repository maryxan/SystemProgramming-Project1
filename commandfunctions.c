#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashtable.h"
#include "comands.h"
#include "preprocessing.h"
#include "date.h"
#include "list.h"


void global_disease_stats(LinkedList* list){

	int count = 0;
	int num_of_nodes = 0;

	//arxizw apo to head tis listas	
	LinkedList * temp = list;
	count = get_node_count(list);

	while(temp->next!=NULL){
		
		//gia kathe komvo sti lista pou einai enas ios metraw posa nodes exei to dentro
		temp= temp->next;
		for (int i = 0; i < count -1; i++)
		{			

			num_of_nodes = get_tree_nodes_count(temp->root->root);
			
		}
		//printf("%s has: %d cases \n",temp->entryName,num_of_nodes);
		printf("%s %d\n",temp->entryName,num_of_nodes);
	}

}

void global_disease_stats_with_param(LinkedList* list , char *parameter1 , char* parameter2){

	int count = 0;
	int num_of_nodes = 0;

	//arxizw apo to head tis listas	
	LinkedList * temp = list;
	count = get_node_count(list);

	while(temp->next!=NULL){
		
		//gia kathe komvo sti lista pou einai enas ios metraw posa nodes exei to dentro se sigekrimeno range
		temp= temp->next;
		for (int i = 0; i < count - 1 ; i++)
		{			

			//metraw posa nodes einai mesa sto range pou thelw
			num_of_nodes = find_count_in_range(temp->root->root,parameter1,parameter2);

		}
		//printf("%s has: %d cases \n",temp->entryName,num_of_nodes);
		printf("%s %d\n",temp->entryName,num_of_nodes);
	}
}

void disease_frequency(LinkedList* list ,char *virus ,char *parameter1 , char* parameter2){


	int count = 0;
	int num_of_nodes = 0;

	//arxizw apo to head tis listas	
	LinkedList * temp = list;
	count = get_node_count(list);

	// printf(" node count is %d\n",count );
	while(temp->next!=NULL){
		
		//gia sigekrimeno io metraw posa nodes exei to dentro se diastima [date1,date2]
		temp= temp->next;
		for (int i = 0; i < count -1 ; i++)
		{			


			if( strcmp(virus,temp->entryName) == 0){	
			num_of_nodes = find_count_in_range(temp->root->root,parameter1,parameter2);

			} else continue;

		}			
		
	}
	//printf("%s has: %d cases \n",virus,num_of_nodes);
	printf("%s %d\n",virus,num_of_nodes);


}


void disease_frequency_with_param(LinkedList* diseaselist, LinkedList* countrylist ,char *virus ,char *parameter1 , char* parameter2 , char* vcountry){

	int count = 0;
	int num_of_nodes = 0;
	int sum = 0;


	//arxizw apo to head tis listas	
	LinkedList * temp = diseaselist;
	count = get_node_count(diseaselist);

	for (int i = 0; i < count ; i++){	
	// printf(" node count is %d\n",count );
		while(temp->next!=NULL){
			
			temp= temp->next;
				//vriskw tin arrwstia pou thelw	
				if(strcmp(virus,temp->entryName) == 0){


					//prepei na phgainw se olous tous komvous toy dentrou
					num_of_nodes = get_tree_nodes_count(temp->root->root);
					//printf("%d\n",num_of_nodes );

					for(int k=0; k < num_of_nodes ; k++){


						sum = find_count_in_range_for_country(temp->root->root,parameter1,parameter2,vcountry);


					} 	
					
				} 
			}			
			
	}
	//printf("%s has at %s: %d cases \n",virus,vcountry,sum);
	printf("%s %d\n",virus,sum);


 }

void insert_patient_record(HashTableBucket** diseaseHashtable,HashTableBucket** countryHashtable,
	 LinkedList* diseaselist, LinkedList* countrylist,
	  char* ID, char* FirstName, char* LastName, char* virus, char* vcountry, char* parameter1, char* parameter2 ,
	  unsigned long int diseaseHashtableNumOfEntries,unsigned long int countryHashtableNumOfEntries,unsigned long int bucketSize){

	entry *ref1 , *ref2;
       
	entry* info = malloc (sizeof(entry)); // ftiaxnw ena struct me ta stoixeia tis kathe eggrafis

		strcpy(info->recordID,ID);
        strcpy(info->patientFirstName,FirstName);
        strcpy(info->patientLastName,LastName);
        strcpy(info->diseaseID,virus);
        strcpy(info->country,vcountry);
        strcpy(info->entryDate,parameter1);
        strcpy(info->exitDate,parameter2);


        if(!check_record_id(diseaseHashtable,ID,diseaseHashtableNumOfEntries)){

	    ref1 = info;
        ref2 = info;

        unsigned long int disease_index = hash_function(ID,diseaseHashtableNumOfEntries);
        unsigned long int country_index = hash_function(vcountry,countryHashtableNumOfEntries);


        // //insert the values to the ht
        insert_to_ht(diseaseHashtable, ref1 , bucketSize , diseaseHashtableNumOfEntries ,disease_index); 
        insert_to_ht(countryHashtable, ref2 , bucketSize , countryHashtableNumOfEntries ,country_index);


        //init kai eisagwgi stin lista 
        linkedlist_insert(diseaselist,ref1,0); 
        linkedlist_insert(countrylist,ref2,1);
        printf("record added\n");
    }
    else{

    	 printf("Patient with that recordID was found.Exiting..\n");
         exit(0);
    }


}

int record_patient_exit(HashTableBucket** diseaseHashtable,unsigned long int diseaseHashtableNumOfEntries,char* ID , char* parameter2){

	//tha psaknw kathe thesi sto ht kai sta bucket gia to record ID

    Bucket* bucket;

    for (int i=0; i<diseaseHashtableNumOfEntries; i++) {

        if (diseaseHashtable[i]->bucket != NULL) {
              
             bucket = diseaseHashtable[i]->bucket;

             while(bucket!=NULL){
   
                for(int i=0; i<bucket->currRecords ; i++){

                	if(strcmp(bucket-> records[i]->recordID,ID) ==0){

                		//printf("Previous exitDate was :%s\n",bucket-> records[i]-> exitDate);
                		if(to_seconds(bucket-> records[i]-> entryDate) <= to_seconds(parameter2) ){


                		strcpy(bucket-> records[i]-> exitDate,parameter2);
                		printf("record updated\n");
                		//printf("Current exitDate is :%s\n",bucket-> records[i]-> exitDate);

                		return 0;
                		} else //printf("Invalid: exitDate cannot be greater than entryDate\n");
                			printf("error\n");
                			return 0;	
                		break;

                	}

                }   
                bucket = bucket->next;

            }
            
        }
    }
    
    return 1;
}


void num_current_patients(HashTableBucket** diseaseHashtable, LinkedList * list,unsigned long int diseaseHashtableNumOfEntries){


	//tha paw stin lista kai gia kathe io pou exw tha kanw tin katw diadikasia

	int count = 0;
	unsigned long hash;
	int num_of_nodes = 0;
	int sum = 0;
	

	//arxizw apo to head tis listas
	LinkedList *temp = list;	
	count = get_node_count(list);


	Bucket* bucket;
	for (int i = 0; i < count - 1 ; i++){	

		while(temp->next!=NULL){
			
			//gia kathe komvo sti lista pou einai mia arrwstia vriskw poses arrwsties einai me exitdate -
			temp= temp->next;
					
				hash = hash_function(temp->entryName,diseaseHashtableNumOfEntries);

				if(diseaseHashtable[hash]->bucket != NULL){

					bucket = diseaseHashtable[hash]->bucket;

			            while(bucket!=NULL){

			             	for(int j=0; j< bucket->currRecords ; j++){

					           	if(strcmp(bucket->records[j]->exitDate,"-") == 0){

					           		sum++;
					           	} 

			            	} 
			             	bucket = bucket->next;

			            }
			    		//printf("Number of patients having %s with no exitDate is: %d \n",temp->entryName,sum);
			    		printf("%s %d\n",temp->entryName,sum);

       	
				}
				sum = 0;
				
		}
	}




}

int num_current_patients_with_param(HashTableBucket** diseaseHashtable, char* virus, unsigned long int diseaseHashtableNumOfEntries){

	int count = 0;
	unsigned long hash;
	Bucket* bucket;


	hash = hash_function(virus,diseaseHashtableNumOfEntries);

		if(diseaseHashtable[hash]->bucket != NULL){

			bucket = diseaseHashtable[hash]->bucket;

	             while(bucket!=NULL){

	             		for(int i=0; i<bucket->currRecords ; i++){

	             			if(strcmp(bucket->records[i]->diseaseID,virus) == 0 ){

				             	if(strcmp(bucket->records[i]->exitDate,"-") == 0){

				             		count++;
				             	}
			             	}
	            	 	} 
	             	    bucket = bucket->next;

	             }
	       		 //printf("Number of patients having %s with no exitDate is %d \n",virus,count);
	             printf("%s %d\n",virus,count);
	             return 0;
		}

		return 1;

}



// ------------------------------------------------voithitikes sinartiseis ---------------------------------------------------------	

// nodes of the list
int get_node_count(LinkedList* head) 
{ 
    int count = 0;   
    LinkedList* current = head;
    while (current != NULL) 
    { 
        count++; 
        current = current->next; 
    } 
    return count -1 ; 
} 

//nodes of the tree
int get_tree_nodes_count(avltreenode *root) 
{ 
    int count = 1;
    if (root->left != NULL) {
       count += get_tree_nodes_count(root->left);
    }
    if (root->right != NULL) {
        count += get_tree_nodes_count(root->right);
    }
    return count; 
} 

//nodes of the tree in range [d1,d2] 
int find_count_in_range(avltreenode *root, char* d1, char* d2) 
{ 
    if (root == NULL) return 0; 
  
    // if node is in range include it in count and recur for left and right children of it 
    if (to_seconds(root->data->entryDate) <= to_seconds(d2) && to_seconds(root->data->entryDate) >= to_seconds(d1)) 
        return 1 + find_count_in_range(root->left, d1, d2) + find_count_in_range(root->right, d1, d2); 
  
    // if current node is smaller than d1, then recur for right child 
    else if (to_seconds(root->data->entryDate) < to_seconds(d1)) 
        return find_count_in_range(root->right, d1, d2); 
  
    // else recur for left child 
    else return find_count_in_range(root->left, d1, d2); 
} 


int find_count_in_range_for_country(avltreenode *node, char *date1, char *date2, char *vcountry) {


    // an vrw to country pou thelw kai an d1<= entryDate <= d2 kai d1<= exitDate <= d2 
    int toReturn = 0;
    if((strcmp(node->data->country,vcountry) == 0 && 

		((to_seconds(node->data->entryDate) >= to_seconds(date1)) &&

		(to_seconds(node->data->entryDate) <= to_seconds(date2))) &&

		(to_seconds(node->data->exitDate) >= to_seconds(date1)) &&

		(to_seconds(node->data->exitDate) <= to_seconds(date2)))){


        toReturn = 1;
    } 
    if (node->right == NULL && node->left == NULL)
        return toReturn;


	else if (node->left == NULL)

        return toReturn + find_count_in_range_for_country(node->right, date1, date2, vcountry);

    else if (node->right == NULL)

        return toReturn + find_count_in_range_for_country(node->left, date1, date2, vcountry); 
    
    else
        return toReturn + find_count_in_range_for_country(node->right, date1, date2, vcountry) +

               find_count_in_range_for_country(node->left, date1, date2, vcountry);


}