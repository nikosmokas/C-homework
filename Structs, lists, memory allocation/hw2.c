#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Dhlwsh twn struct

typedef struct Node  //node = kathe ma8hma sthn aplh lista ma8hmatwn
{ 
	short unsigned int subjectID; 
	struct Node *next; 
} node;


typedef struct student{ // student = foititis se mia dipli lista foititwn
	long unsigned int AEM;
	char name[64];
	short unsigned int failures;
	struct student *next; 
	struct student *previous;
	node *SubjectListHead; // head ths listas ma8imatw poy einai 
                           //eggegramenos o sugkekrimenos foititis
	
} data;

typedef struct {
	data **array_ptr; 
	int entries;
	int dbsize;
	
} data_array;


//Chapter 1: sunartiseis pou ftiaxnoun sentinels.
node *initSubjectList(); //Sunartish pou kaleitai ka8e fora pou kanoume add enan foititi
                         //wste na dhmiourghsoyme ton sentinel (head) gia tis lista ma8hmatwn tou (arxikopoihsh)
data *initStudent(); //Sunartisei p kaleitai gia dhmiourghsei sentinels se ka8e keli tou hash-table.
					//an px. o hashtable exei size 4 kelia, tote 8a exoume 4 sentinels.
void dynamic_array(int dbsize_input, data_array *ptr); //dhmiourgei ton hashtable kai edw mesa kaleitai h initStudent()
unsigned long hash(char *str);

//Chapter 2: Sunarthsh add kai oles oi voh8itikes sunarthseis	
int add(data_array *ptr, char name[], const long unsigned int AEM, const short unsigned int failures, node *SubjectListHead);	
void find(data_array *ptr, char name[]); //Elenxei mono an uparxei to onoma. Tipota allo. Xreisimopoiei thn apo katw
data *findStudentInBucket(data *Sentinel, char name[]); //H palia helper_find() alla gia lista (bucket tou hashtable). Epistrefei ton PROHGOUMENO komvo ap'oti psaxnoume. An den to vrei tote epistrefei to teleutaio stoixeio tis listas, ara current->next == NULL (gia elenxo. Vlepe add/rmv/mod ktlp)
int checkAEM(data_array *ptr, const long unsigned int AEM); //Kaleitai stis add. Ksexwristi sunarthsh giati alliws h add ginetai megalh kai periplokh sto diavasma
void ReHash(data_array *ptr); //vlepe ekfwnhsh, perissoterh ekshgh mesa sthn sunarthsh

//Chapter 3: Upoloipes leitourgeis. An katalaveis tis parapanw, autes einai paixnidaki.
int rmv(data_array *ptr, char name[]);
int mod(data_array *ptr, char name[], const short unsigned int failures);
void printStudentList(data *sentinel);
void print(data_array *ptr);

//Chapter 4: Clear sunartiseis, se kommatia gia na einai evanaugnwstes.

//Genika: prin diagrapsoume(free) kapoion FOITHTH, kanoume free thn lista ma8hmatwn kai meta pame ston epomeno foitith ths listas
void clearStudentList(data *sentinel); //kaleitai mesa sthn clear gia ka8e keli tous hash-table.
void clearSubjectList(node *head); //kaleitai mesa sthn clearStudentList (apo panw)
void quit(data_array *ptr);
int clear(data_array *ptr);

//Chaptaer 5: sunartiseis poy aforoun tis aplh lista me ta ma8hmata tou ka8e foitith
void printList(data_array *ptr, char name[]);
int isReg(data_array *ptr, char name[], short unsigned int val);
int destroySubject(data_array *ptr, char name[], short unsigned int val);
node *findSubject(node *head, short unsigned int val);
int addSubject(data_array *ptr, char name[], short unsigned int val);

int main(int argc, char *argv[]) {
	char operator;
	char trash[64];
	char seperator;
	data_array var;	/* prepei na mh to kanoume pointer giati 8eloume mono gia ta pedia tou na kanoume malloc */ 
	long unsigned int AEM;
	short unsigned int ID;
	char name[64];
	short unsigned int failures;
	int dbsize_input = 1;
	int error_check = 0;
	
	if(argc == 2) 
	{
		dbsize_input=atoi(argv[1]);
	}
	
	dynamic_array(dbsize_input, &var);
		
	do {
		
		scanf("%s%c", trash, &seperator);
		operator = trash[0];
		
		switch(operator) {
			case 'a':
			{
				scanf("%lu%c%s%hu", &AEM, &seperator, name, &failures);
				
				error_check = add(&var, strupr(name), AEM, failures, NULL);
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
			
			
			case 'p':
			{
				print(&var);
				break;
			}
			
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
		}
	} while(1);
}


//CHAPTER 1:

data *initStudent() { //Praktika dhmiourgei ena sentinel sti lista twn ma8htwn. SE -MIA- 8esh tou hastable, oxi se oles
	data *sentinel = (data *)malloc(sizeof(data));
	if (sentinel == NULL) { //PANTA elenxos meta apo malloc. An ksexasa kanena pes m
		printf("initStudentList error in malloc!\n");
		return(NULL);
	}
	sentinel->AEM = 0; 
	strcpy(sentinel->name, "aaaaaaa"); //arxikopoiw me non-valid stoixeia. To onoma 8elw na einai to mikrotero
	sentinel->failures = 0; //Life-hack: xrisimopoiw thn failures tou sentinel gia na metraw poses egrafes uparxoun sthn sugkekrimenh lista (to zhtaei se kapoio printf h askhsh)
	sentinel->next = NULL;
	sentinel->previous = NULL;
	sentinel->SubjectListHead = NULL; //Prosoxh. NULL dioti o sentinel DEN exei lista ma8hmatwn
	return(sentinel);
}

node *initSubjectList() { //Dhmiourgeia sentinel gia thn lista MA8HMATWN se kainourgeia eggrafh foititi (mesa sthn add). Oloi oi foitites exoun tetoio head gia ta ma8hmata tous
	
	node *head = (node*)malloc(sizeof(node));
	if (head == NULL) { //PANTA elenxos meta apo malloc
		printf("initSubJectList error in malloc!\n");
		return(NULL);
	}
	head->subjectID = 0; //non-valid elaxisti timh gia na paramenei sentinel
	head->next = NULL;
	
	return(head);
}

void dynamic_array(int dbsize_input, data_array *ptr) { //dhmiourgeia has-table 
	int i;
	ptr->array_ptr = (data **)malloc(dbsize_input*sizeof(data *));
	for (i = 0; i<dbsize_input; i++) {
		ptr->array_ptr[i] = initStudent(); //dimiourgeia SENTINEL foititwn gia ka8e keli. Ka8e keli points to its respective sentinel
	}
	ptr->entries = 0; //sto initialization exeis 0 egrafes
	ptr->dbsize = dbsize_input;
}

unsigned long hash(char *str) { //dinetai
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}


//CHAPTER 2:

void find(data_array *ptr, char name[]) { //h palia sunarthsh find(). DEN EINAI H helper_find(). Vlepe parakatw gia helper_find()
	int pos;
	data *temp = NULL;
	
	pos = hash(name) % ptr->dbsize; //analoga me to onoma pairneis sugkekrimeno hash-key. Sto exw ekshghsei pws leitourgei
	
	temp = findStudentInBucket(ptr->array_ptr[pos], name); //kaloume thn helper_find
	
	//ta diadikastika tis find()
	
	printf("\n#\n");
	
	//an h lista einai adeia 8a epistrepsei null. Vlepe findStudentInBucket() (helper_find)
	if (temp == NULL) {
		printf("F-NOK %s\n", name);
	}
	//afou epistrefei to prohgoumeno, checkaroume an to epomeno einai auto poy 8eloyme
	else if (strcmp(temp->next->name, name) == 0) {
		printf("F-OK %lu %hu\n", temp->next->AEM, temp->next->failures);
	}
	else {
		printf("F-NOK %s\n", name);
	}
}

data *findStudentInBucket(data *Sentinel, char name[]) { //h helper_find() (me pio eustoxo onoma :P) epistrefei to prohgoumeno apo auto p 8eloume
	data *current = Sentinel;
	
	//current = sentinel. Ara an sentinel->next == NULL tote einai adeia h lista
	if (current->next == NULL) {
		return (NULL);
	}
	
	
	//oso to next tou next (Confusing, I know, but get used to it) kai h timi einai mikroterh apo auth p psaxnoume tote sunexise na trexeis thn lista
	while (current->next->next != NULL && strcmp(current->next->name, name) < 0) {
		//an ston epomeno komvo einai auto poy 8eloyme, epistrepse to current (dld to prohgoumeno apo auto p 8eloyme)
		if (strcmp(current->next->name, name) == 0) {
			return (current);
		}
		//to vhma
		current = current->next;
	}
	//an ftasei edw shmenei oti exei treksei olh thn lista ->H<- auto p psaxnoume einai to teleutaio (ginetai elenxos sthn add/rmv/mod ktlp). Se ka8e periptwsh isxyei oti current->next = NULL
	//PSOXOXH:  AN EXOUME PERASEI THN TIMI P PSAXNOUME, An px h lista exei ta onomata: Alex, Bob, Zebra kai psaxnoume to Julia 8a epistrepsei ton -Bob-
	return(current);
}

int add(data_array *ptr, char name[], const long unsigned int AEM, const short unsigned int failures, node *SubjectListHead) {
	//welcome to hell
	//epistrefei 0 sthn APOTUXIA (otan yparxei o foititis h to aem) kai 1 sthn epituxeia
	int pos;
	data *temp = NULL; //temp struct.. san to "new" p eixes ftiaksei esu.
	data *current = NULL;
	
	if (ptr->dbsize == 0) { //elenxei o array_ptr exei kelia. Meta apo clear() o pinakas exei 0 kelia, p shmenei oti prepei na ton ftiakseis pali
		dynamic_array(1, ptr); //an isxyei, dhmioyrgeis ksana ton pinaka opws sthn arxh ths main. To orisma prepei na einai 8(kelia) anti gia 1 otan einai paradwseis
	}
	
	pos = hash(name) % ptr->dbsize; //hash-key
	
	if (checkAEM(ptr, AEM)) { //elenxos gia AEM (vlepe checkAEM. Ksexwristi sunarthsh giati einai hdh mpourdelo h add
		return(0);
	}
	
	current = ptr->array_ptr[pos]; //elenxos gia to an h lista einai adeia, 8etontas current = sentinel (dld ptr->array[pos])
	
	if (current->next == NULL) { //an einai adeia tote sentinel->next = null. Dhmiourgei komvo an alh8euei
		current->next = (data *)malloc(sizeof(data));
		if (current->next == NULL) {
			return(0);
		}
		strcpy(current->next->name, name);
		current->next->AEM = AEM;
		current->next->failures = failures;
		if (SubjectListHead == NULL) {
			current->next->SubjectListHead = initSubjectList(); //dimiourgeia sentinel/head gia thn lista ma8hmatwn
		}
		else {
			current->next->SubjectListHead = SubjectListHead; //auto einai gia to re-hash. 8a sto eksighsw apo konta otan er8ei h wra
		}
		current->next->next = NULL; //afou einai adeia h lista kai auto einai to 1o stoixeio (meta to sentinel fusika) tote to next = null;
		current->next->previous = current; //previous einai to current opou einai to sentinel.
		ptr->entries++; //afksanoume entries
		ptr->array_ptr[pos]->failures++; //panw anaferw oti oi sentinel tou ka8e BUCKET xrhshmopoioun ta failures tous gia na katagrapsoun posous foitites exei to bucket tous
		return(1); //teleiwsame.
	}
	
	//an dn einai adeia h lista...
	current = findStudentInBucket(ptr->array_ptr[pos], name); //elenxos gia to an uparxei to onoma. Ksanalew, epistrefei to prohgoumeno an uparxei ->H<- an exei perasei thn timi p psaxnoume, kai an dn uparxei to teleutaio keli 
	
	if (strcmp(current->next->name, name) == 0) { //elenxw an to onoma uparxei
		return(0);
	}
	
	if (strcmp(current->next->name, name) > 0) { //elenxw an eimaste sto telos ths listas. To be honest, oute egw katalava GIATI to ekana auto
		current = current;
	}
	else if (current->next->next == NULL) { //if it works, it works
		current = current->next;
	}
	
	
	//kanw ta idia me ta parapanw (stis periptwsh p einai adeia) apo edw kai pera. Apla dhmiourgw ton komvo
	temp = (data *)malloc(sizeof(data));
	if (temp == NULL) {
		return (0);
	}
	strcpy(temp->name, name);
	temp->AEM = AEM;
	temp->failures = failures;
	if (SubjectListHead == NULL) {
		temp->SubjectListHead = initSubjectList(); 
	}
	else {
		temp->SubjectListHead = SubjectListHead;
	}
	temp->next = current->next;
	if (temp->next != NULL) { //ama dn einai sto telos ths listas o kainourgios komvos, 8etw to previous to epomeno ston idio ton komvo. Sto xarti mporw na sto eksighsw kalutera
		temp->next->previous = temp;
	}
	temp->previous = current; 
	current->next = temp; //dafuq
	
	ptr->entries++;
	ptr->array_ptr[pos]->failures++;
	if (((double)ptr->entries/ptr->dbsize >= 4)) { //elenxos gia to an prepei na kanw re-hash
		ReHash(ptr);
	}
	
	return(1);
}

int checkAEM(data_array *ptr, const long unsigned int AEM) { //elenxos uparkshs AEM. einai sxetika aplh
	int i;
	data *current = NULL;
	
	//epistrefei 1 an uparxei, 0 an den uparxei
	//Opws eixe pei kai h Vana, distuxws gia to AEM prepei na prospelasoume OLO ton pinaka. Ola ta bucket dld. Opote gia ka8e keli checkarw olous tous komvous
	for (i = 0; i < ptr->dbsize; i++) { //gia ka8e keli
		if (ptr->array_ptr[i]->next != NULL) { //an DEN einai adeia. An einai adeia h lista tote sentinel(ptr->array[pos])->next = NULL
			current = ptr->array_ptr[i]->next; //an DEN einai adeia kannoume current ton sentinel
			while(current != NULL) { //prospelasoume olh thn lista. 8umizw auto ginetai gia KA8E lista
				if (current->AEM == AEM) { //that's fucking obvious
					return(1); 
				}
				current = current->next; //to step gia thn trexousa lista
			}
		}
	}
	return(0);  //ama ftasei edw tote exei treksei olo ton pinaka kai den to vrike
}

void ReHash(data_array *ptr) {
	data_array *tempArray = (data_array *)malloc(sizeof(data_array));
	int i, j;
	data *current = NULL;
	
	tempArray->array_ptr = (data **)malloc(ptr->dbsize*sizeof(data *));
	tempArray->dbsize = ptr->dbsize;
	tempArray->entries = ptr->entries;
	
	for (i = 0; i < tempArray->dbsize; i++) {
		tempArray->array_ptr[i] = ptr->array_ptr[i];
	}
	
	if ((double)ptr->entries/ptr->dbsize >= 4) {
		ptr->dbsize = ptr->dbsize * 2;
		
	}
	else {
		ptr->dbsize = ptr->dbsize / 2;
	}
	
	
	free(ptr->array_ptr);
	dynamic_array(ptr->dbsize, ptr);
	
	for (i = 0; i < tempArray->dbsize; i++) {
		current = tempArray->array_ptr[i];
		while (current->next != NULL) {
			add(ptr, current->next->name, current->next->AEM, current->next->failures, current->next->SubjectListHead);
			print(ptr);
			current = current->next;
		}
		clearStudentList(tempArray->array_ptr[i]);
	}
	
	free(tempArray->array_ptr);
	free(tempArray);
}


//CHAPTER 3:
	
int mod(data_array *ptr, char name[], const short unsigned int failures) {
	int pos;
	data *current = NULL;
	
	pos = hash(name) % ptr->dbsize;
	
	current = findStudentInBucket(ptr->array_ptr[pos], name);
	
	if (current->next != NULL) {
		current = current->next;
		if (strcmp(current->name, name) == 0) {
			current->failures = failures;
			return(1);
		}
		return(0);
	}
	return(0);
}

int rmv(data_array *ptr, char name[]) {
	int pos;
	data *current = NULL;
	
	pos = hash(name) % ptr->dbsize;
	
	current = findStudentInBucket(ptr->array_ptr[pos], name);
	
	if(current->next != NULL) {
		current = current->next;
		if(strcmp(current->name, name) != 0) {
			return(0);
		}
	}
	else {
		return(0);
	}
	
	current->previous->next = current->next;
	if (current->next != NULL) {
		current->next->previous = current->previous;
	}
	free(current);
	ptr->entries--;
	ptr->array_ptr[pos]->failures++;
	if (((double)ptr->entries/ptr->dbsize < 1)) {
		ReHash(ptr);
	}
	return(1);
}

void printStudentList(data *sentinel) {
	data *current = sentinel->next;
	while (current != NULL) {
		printf(" [%lu, %s, %hu]", current->AEM, current->name, current->failures);
		current = current->next;
	}
}

void print(data_array *ptr) {
	int i;
	
	printf("\n#\n");
	printf("%d, %d\n", ptr->dbsize, ptr->entries);
	for (i = 0; i<ptr->dbsize; i++) {
		if (ptr->array_ptr[i]->next != NULL) {
			printStudentList(ptr->array_ptr[i]);
		}
		printf("\n");
	}
}

//CHAPTER 4:

void clearSubjectList(node *head) {
	node *prev = head;
	node *current = NULL;
	
	if (head->next != NULL) {
		current = head->next;
		while (current != NULL) {
			free(prev);
			prev = current;
			current = current->next;
		}
		free(prev);
	}
	else {
		free(prev);
	}
}

void clearStudentList(data *sentinel) {
	data *current = sentinel;
	
	if (current->next != NULL) {
		current = current->next;
		while (current != NULL) {
			if (current->previous->SubjectListHead != NULL) {
				clearSubjectList(current->previous->SubjectListHead);
			}
			free(current->previous);
			if (current->next != NULL) {
				current = current->next;
			}
			else {
				if (current->SubjectListHead != NULL) {
					clearSubjectList(current->SubjectListHead);
				}
				free(current);
				break;
			}
		}
	}
	else {
		free(current);
	}
}

int clear(data_array *ptr) {
	int i;
	
	for (i = 0; i < ptr->dbsize; i++) {
		clearStudentList(ptr->array_ptr[i]);
	}
	ptr->dbsize = 0;
	ptr->entries = 0;
	
	ptr->array_ptr = (data **)malloc((ptr->dbsize)*sizeof(data *));
	
	return(1);
}

void quit(data_array *ptr) {
	
	clear(ptr);
}

//CHAPTER 5:


node *findSubject(node *head, short unsigned int val) {
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

void printList(data_array *ptr, char name[])	{
	node *current = NULL;
	data *stud = NULL;
	int pos;
	
	pos = hash(name) % ptr->dbsize;
	stud = findStudentInBucket(ptr->array_ptr[pos], name);
	
	
	
	if (stud->next != NULL) {
		stud = stud->next;
		if (strcmp(stud->name, name) == 0) {
			current = stud->SubjectListHead->next;
			printf("#\n%s\n", name);
			while (current != NULL) 
			{ 
				printf("Subject ID: %hu\n", current->subjectID); 
				current = current->next; 
			} 
		}
	}
	else {
		printf("L-NOK %s\n", name);
	}
} 

int isReg(data_array *ptr, char name[], short unsigned int val) {
	node *temp = NULL;
	data *tempStud = NULL;
	int pos;
	
	pos = hash(name) % ptr->dbsize;
	
	tempStud = findStudentInBucket(ptr->array_ptr[pos], name);
	
	if (tempStud->next != NULL) {
		tempStud = tempStud->next;
		if (strcmp(tempStud->name, name) == 0) {
			temp = findSubject(tempStud->SubjectListHead, val);
		}
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

int destroySubject(data_array *ptr, char name[], short unsigned int val) {
	node *current = NULL;
	node *temp = NULL;
	data *tempStud = NULL;
	int pos;
	
	pos = hash(name) % ptr->dbsize;
	
	tempStud = findStudentInBucket(ptr->array_ptr[pos], name);
	
	if (tempStud->next != NULL) {
		tempStud = tempStud->next;
		if (strcmp(tempStud->name, name) == 0) {
			temp = findSubject(tempStud->SubjectListHead, val);
		}
	}
	else {
		printf("U-NOK %s\n", name);
		return(0);
	}
	
	
	temp = findSubject(tempStud->SubjectListHead, val);
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

int addSubject(data_array *ptr, char name[], short unsigned int val) {
	node *current = NULL;
	node *tempNode = NULL;
	data *tempStud = NULL;
	int pos;
	
	pos = hash(name) % ptr->dbsize;
	
	tempStud = findStudentInBucket(ptr->array_ptr[pos], name);
	
	if (tempStud->next != NULL) {
		tempStud = tempStud->next;
		if (strcmp(tempStud->name, name) == 0) {
			current = tempStud->SubjectListHead;
		}
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
	
	current = findSubject(tempStud->SubjectListHead, val);
	
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
	
	
	tempNode = (node*)malloc(sizeof(node));
	if (tempNode == NULL) {
		return(0);
	}
	tempNode->subjectID = val;
	tempNode->next = current->next;
	
	current->next = tempNode;
	
	return(1);
	
}
