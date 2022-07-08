
// A simple C program for traversal of a linked list 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
  
typedef struct Node
{ 
	short unsigned int subjectID; 
	struct Node *next; 
} node; 
  
// This function prints contents of linked list starting from  
// the given node 

int addSubject(node *head, short unsigned int val);
void printList(node *head);
node *findSubject(node *head, short unsigned int val);
int destroySubject(node *head, int val);

int main(int argc, char *argv[]) {
	char input[64];
	char temp[64];
	node *head = NULL; 
	char operator;
	short unsigned int ID;
	int error_check;
	node *find = NULL;
	
	head  = (node*)malloc(sizeof(node));
	head->subjectID = 0;
	head->next = NULL;
	
	do {
		operator = getchar();
		
		switch(operator) {
			case 'r':
			{	
				scanf(" %hu", &ID);
				error_check = addSubject(head, ID);
				if (error_check == 0) {
					printf("Error allocating mem\n");
					return(0);
				}
				break;
			}
			
			case 'u':
			{
				scanf(" %hu", &ID);
				error_check = destroySubject(head, ID);
				
				if (error_check == 1) {
					printf("DESTROYED!\n");
				}
				break;
			}	
				
			case 'f':
			{
				scanf(" %hu", &ID);
				find = findSubject(head, ID);
				if (find == NULL) {
					printf("Subject not found, motherfucka'\n");
				}
				else {
					printf("Subject ID: %hu FOUND!\n", find->next->subjectID);
				}
				break;
			}
				
				
			case 'l':
			{
				printList(head);
				break;
			}
		}
	}while(1);
	
	return 0; 
}

void printList(node *head)	{
	node *current = head->next;
	while (current != NULL) 
	{ 
		printf("Subject ID: %hu\n", current->subjectID); 
		current = current->next; 
	} 
} 

node *findSubject(node *head, short unsigned int val){
	node *current = head;
	
	
	if (current->next == NULL) {
		return(NULL);
	}
	
	while (current->next->next != NULL && current->next->subjectID < val) {
		if (current->next->subjectID == val) {
			return (current);
		}
		current = current->next;
	}
	
	return(current);
}
	


int destroySubject(node *head, int val) {
	node *current = head;
	node *temp = NULL;
	
	temp = findSubject(head, val);
	current = temp->next;
	
	if (current->subjectID == val) {
		temp->next = current->next;
		free(current);
		return(1);
		
	}
	else {
		return(0);
	}
}
	

	


int addSubject(node *head, short unsigned int val) {
	node *current = head;
	node *temp = NULL;
	
	
	
	if (current->next == NULL) {
		current->next = (node*)malloc(sizeof(node));
		if (current->next == NULL) {
			return(0);
		}
		current->next->subjectID = val;
		current->next->next = NULL;
		return(1);
	}
	
	current = findSubject(head, val);
	printf("Curren: %hu\n", current->subjectID);
	
	if (current->next->subjectID == val) {
		return(0);
	}
	
	if (current->next->subjectID > val) {
		current = current;
	}
	else if (current->next->next == NULL) {
		current = current->next;
	}
	
	
	temp = (node*)malloc(sizeof(node));
	if (temp == NULL) {
		return(0);
	}
	temp->subjectID = val;
	temp->next = current->next;
	
	current->next = temp;
	
	return(1);
	
}