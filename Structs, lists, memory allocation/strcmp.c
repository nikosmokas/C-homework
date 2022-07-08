#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char str1[50];
	char str2[50];
	
	scanf("%s", str1);
	scanf("%s", str2);
	
	printf("Strcmp out: %d", strcmp(str1, str2));
}