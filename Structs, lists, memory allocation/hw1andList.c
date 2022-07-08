/* IMPORTANT!!!!!!!!!!
 * PROBLEMS WITH THIS VERSION:
 * 		1) O pinakas apo data (*ptr->array_ptr) den euksanetai me th realloc. PAIKSE ME TIS ENTOLES EKEI
 * 			To segmentation fault ginetai giati den exei ftiaxtei extra xwros gia to 2o stoixeio typou data (to opoio 8a eprepe
 * 			na eixe kanei h realloc.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
typedef struct Node
{ 
	short unsigned int subjectID; 
	struct Node *next; 
} node; 

typedef struct {
	long unsigned int AEM;
	char name[64];
	short unsigned int failures;
	node *head;
	
} data;

typedef struct {
	data **array_ptr; 
	int entries;
	int dbentries;
	
} data_array;


node *initSubjectList();
int addSubject(data_array *ptr, const char name[], short unsigned int val);
void printList(data_array *ptr, const char name[]);
node *findSubject(node *head, short unsigned int val);
int destroySubject(data_array *ptr, const char name[], short unsigned int val);
int isReg(data_array *ptr, const char name[], short unsigned int val);

int helper_find(data_array *ptr, const char name[]);
void find(data_array *ptr, const char name[]);
int add(data_array *ptr, const char name[], const long unsigned int AEM, const short unsigned int failures);
int rmv(data_array *ptr, const char name[]);
int mod(data_array *ptr, const char name[], short unsigned int failures);
int sort(data_array *ptr);
void print(data_array *ptr);
int clear(data_array *ptr);
void quit(data_array *ptr);
int dynamic_array(int entries_input, data_array *ptr);

int main(int argc, char *argv[]) 
{
	char operator;
	char trash[64];
	char seperator;
	data_array var;	/* prepei na mh to kanoume pointer giati 8eloume mono gia ta pedia tou na kanoume malloc */ 
	long unsigned int AEM;
	short unsigned int ID;
	char name[64];
	short unsigned int failures;
	int dbsize_input = 0;
	int error_check = 0;
	
	
	if(argc == 2) 
	{
		dbsize_input=atoi(argv[1]);
	}
	
	dynamic_array(dbsize_input, &var);
	
	do
	{
		scanf("%s%c", trash, &seperator);	
		operator = trash[0];
		
		
		
		switch(operator)
		{	
			case 'g': {
				scanf("%s%c%hu", name, &seperator, &ID);
				error_check = addSubject(&var, strupr(name), ID);
				if (error_check == 0) {
					break;
				}
				else {
					printf("G-OK\n");
					break;
				}
			}
				
			case 'l': {
				scanf("%s", name);
				printList(&var, strupr(name));
				break;
			}
			
			case 'u': {
				scanf("%s%c%hu", name, &seperator, &ID);
				error_check = destroySubject(&var, strupr(name), ID);
				if (error_check == 0) {
					break;
				}
				else {
					printf("U-OK\n");
					break;
				}
			}
			
			case 'i': {
				scanf("%s%c%hu", name, &seperator, &ID);
				error_check = isReg(&var, strupr(name), ID);
				break;
			}
				
			case 'a':
			{
				scanf("%lu%c%s%hu", &AEM, &seperator, name, &failures);
				
				error_check = add(&var, strupr(name), AEM, failures);
				if (error_check == 0) {
					printf("\nA-NOK %s\n", name);
				}
				else if (error_check == -1) {
					printf("\nA-NOK %lu\n", AEM);
				}
				else {
					printf("\nA-OK\n");
				}
				break;
			}
			
			case 'r':
			{
				scanf("%s", name);
				error_check = rmv(&var, strupr(name));
				if (error_check == 0) {
					printf("\nR-NOK %s\n", name);
				}
				else {
					printf("\nR-OK\n");
				}
				break;
			}
			
			case 'm':
			{
				scanf("%s%c%hu", name, &seperator, &failures);
				error_check = mod(&var, strupr(name), failures);
				if (error_check == 0) {
					printf("\nM-NOK %s\n", name);
				}
				else {
					printf("\nM-OK\n");
				}
				break;
			}
			
			case 'f':
			{
				scanf("%s", name);
				find(&var, strupr(name));
				break;
			}
			
			case 's':
			{
				error_check = sort(&var);
				if (error_check == 1) {
					printf("\nS-OK\n");
				}
				break;
			}
			
			case 'p':
			{
				print(&var);
				break;
			}
			
			case 'c': 
			{
				error_check = clear(&var);
				if (error_check == 1) {
					printf("\nC-OK\n");
				}
				break;
			}
			
			case 'q':
			{
				quit(&var);
				return(0);
			}
				
		}
	}while(1);
	
	return(0);
}

int dynamic_array(int dbsize_input, data_array *ptr)
{
	ptr->array_ptr = (data **)malloc(dbsize_input*sizeof(data *));
	ptr->entries = 0;
	ptr->dbentries = dbsize_input;
	return 0;
}

int helper_find(data_array *ptr, const char name[])
{
	int i, result;
	
	for(i = 0; i < ptr->entries; i++)
	{
		result = strcmp(name, ptr->array_ptr[i]->name);
		if(result==0)
			break;
	}
	return(i);
}

void find(data_array *ptr, const char name[])
{
	int pos;
	
	pos=helper_find(ptr, name);
	
	printf("\n#\n");
	
	if(pos < ptr->entries) { //the name exists my dear people
		printf("F-OK %lu %hu\n", ptr->array_ptr[pos]->AEM, ptr->array_ptr[pos]->failures);
	}
	else {
		printf("F-NOK %s\n", name);
	}
	
}

int add(data_array *ptr, const char name[], const long unsigned int AEM, const short unsigned int failures)
{
	int pos;
	int i;
	
	pos=helper_find(ptr, name);
	
	if(pos < ptr->entries) //Η θέση θα είναι μικρότερη τα entries το όνομα υπάρχει ήδη.
	{
		return(0); //failed
	}
	
	for (i = 0; i < ptr->entries; i++) {
		if (AEM == ptr->array_ptr[i]->AEM) {
			return(-1);
		}
	}
	
	
	
	if (ptr->dbentries < ptr->entries+1) {
		
		ptr->dbentries++;
		ptr->array_ptr = (data **)realloc(ptr->array_ptr, ptr->dbentries*sizeof(data *));
		
	}
	
	ptr->array_ptr[ptr->entries] = (data *)malloc(sizeof(data));
	
	if(ptr->array_ptr == NULL)
	{
		return(-2); //failed
	}
	strcpy(ptr->array_ptr[ptr->entries]->name, name);
	memcpy(&(ptr->array_ptr[ptr->entries]->AEM), &AEM, sizeof(AEM));
	memcpy(&(ptr->array_ptr[ptr->entries]->failures), &failures, sizeof(failures));
	ptr->array_ptr[ptr->entries]->head = initSubjectList();
	
	//printf("\ndbentries: %d\nEntries: %d\n", ptr->dbentries, ptr->entries+1);
	
	ptr->entries++;
	
	return(1); //succeded
	
}

int rmv(data_array *ptr, const char name[])
{
	int pos;
	
	pos=helper_find(ptr, name);
	
	if(pos >= ptr->entries) //Το όνομα δεν υπάρχει, καθώς έχω διατρέξει όλο τον πίνακα κ δεν το βρήκα. (Μεγαλύτερο δεν γίνεται να είναι ποτέ, απλά για έλεγχο)
	{
		return(0);
	}
	
	/*Παίρνω το τελευταίο στοιχείο του πίνακα με τα struct και τo κάνω ovewrite στη θέση που θέλω να αφαιρέσω.*/
	strcpy(ptr->array_ptr[pos]->name, ptr->array_ptr[ptr->entries-1]->name); 
	memcpy(&(ptr->array_ptr[pos]->AEM), &(ptr->array_ptr[ptr->entries-1]->AEM), sizeof(ptr->array_ptr[ptr->entries-1]->AEM));
	memcpy(&(ptr->array_ptr[pos]->failures), &(ptr->array_ptr[ptr->entries-1]->failures), sizeof(ptr->array_ptr[ptr->entries-1]->failures));
	
	
	/*Aποδεσμεύω τη μνήμη των τελευταίων στοιχείων.*/
	
	free(ptr->array_ptr[ptr->entries-1]);
	ptr->entries--;
	ptr->dbentries--;
	ptr->array_ptr = (data **)realloc(ptr->array_ptr, (ptr->dbentries)*sizeof(data *));
	
	//printf("\ndbentries: %d\nEntries: %d\n", ptr->dbentries, ptr->entries);
	
	
	
	if(ptr->array_ptr == NULL)
	{
		return(-1); //failed
	}
	
	return(1); //succeded
}

int mod(data_array *ptr, const char name[], short unsigned int failures)
{
	int pos;
	
	pos=helper_find(ptr, name);
	
	if(pos == ptr->entries) //Το όνομα δεν βρέθηκε.
	{
		return(0);
	}
	memcpy(&(ptr->array_ptr[pos]->failures), &failures, sizeof(failures));
	
	if(!(ptr->array_ptr[pos]->failures == failures))
	{
		return(0);
	}
	
	return(1);
}

int sort(data_array *ptr) {
	int i;
	int j;
	data *temp;
	
	for (i = 1; i<ptr->entries; i++) {
		//temp = ptr->array_ptr[i];
		j = i - 1;
		while (j >= 0 && strcmp(ptr->array_ptr[j]->name, ptr->array_ptr[j+1]->name) > 0) {
			temp = ptr->array_ptr[j];
			ptr->array_ptr[j] = ptr->array_ptr[j+1];
			ptr->array_ptr[j+1] = temp;
			j--;
		}
	}
	
	return(1);
}

void print(data_array *ptr) {
	int i;
	
	printf("\n#\n");
	for (i = 0; i < ptr->entries; i++) {
		printf("%lu %s %hu\n", ptr->array_ptr[i]->AEM, ptr->array_ptr[i]->name, ptr->array_ptr[i]->failures);
	}
}

int clear(data_array *ptr) {
	int i;
	
	for (i = 0; i < ptr->entries; i++) {
		free(ptr->array_ptr[i]);
	}
	ptr->dbentries = 0;
	ptr->entries = 0;
	ptr->array_ptr = (data **)realloc(ptr->array_ptr, (ptr->dbentries)*sizeof(data *));

	
	return(1);
}

void quit(data_array *ptr) {
	
	clear(ptr);
	
}

void printList(data_array *ptr, const char name[])	{
	node *current = NULL;
	int pos;
	
	pos = helper_find(ptr, name);
	printf("Pos: %d PTR Entries: %d\n", pos, ptr->entries);
	
	if (pos < ptr->entries) {
		current = ptr->array_ptr[pos]->head->next;
		printf("#\n%s\n", name);
		while (current != NULL) 
		{ 
			printf("Subject ID: %hu\n", current->subjectID); 
			current = current->next; 
		} 
	}
	else {
		printf("L-NOK %s\n", name);
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

int isReg(data_array *ptr, const char name[], short unsigned int val) {
	node *temp = NULL;
	int pos;
	
	pos = helper_find(ptr, name);
	
	if (pos < ptr->entries) {
		temp = findSubject(ptr->array_ptr[pos]->head, val);
	}
	else {
		printf("I-NOK %s\n", name);
		return(0);
	}
	
	
	
	if (temp->next->subjectID == val) {
		printf("YES\n");
	}
	else {
		printf("NO\n");
	}
	return(1);
}


int destroySubject(data_array *ptr, const char name[], short unsigned int val) {
	node *current = NULL;
	node *temp = NULL;
	int pos;
	
	pos = helper_find(ptr, name);
	
	if (pos < ptr->entries) {
		current = ptr->array_ptr[pos]->head;
	}
	else {
		printf("U-NOK %s\n", name);
		return(0);
	}
	
	
	temp = findSubject(ptr->array_ptr[pos]->head, val);
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
	

int addSubject(data_array *ptr, const char name[], short unsigned int val) {
	node *current = NULL;
	node *temp = NULL;
	int pos;
	
	pos = helper_find(ptr, name);
	
	if (pos < ptr->entries) {
		current = ptr->array_ptr[pos]->head;
	}
	else {
		printf("G-NOK %s\n", name);
		return(0);
	}
	
	if (current->next == NULL) {
		current->next = (node*)malloc(sizeof(node));
		if (current->next == NULL) {
			return(0);
		}
		current->next->subjectID = val;
		current->next->next = NULL;
		return(1);
	}
	
	current = findSubject(ptr->array_ptr[pos]->head, val);
	printf("Curren: %hu\n", current->subjectID);
	
	if (current->next->subjectID == val) {
		printf("G-NOK %hu\n", val);
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

node *initSubjectList() {
	
	node *head = (node*)malloc(sizeof(node));
	head->subjectID = 0;
	head->next = NULL;
	
	return(head);
}
	