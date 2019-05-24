#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Thes.h"
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <locale>
#include <windows.h>
using namespace std;

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	Thesaurus thes;
	printf("\nWeclome to Thesaurus\n");
	char* c = (char*)malloc(sizeof(char) * 256);
LOOP:
	while (strcmp(c, "exit") != 0) {
		printf("\nWhat would like to do?\n");
		printf("Add a word - 'add'\n");
		printf("Add a translation - 'add_t'\n");
		printf("See a translation for a word - 'tr'\n");
		printf("Copy thesaurus into a file - 'cp'\n");
		printf("Show thesaurus on a screen - 'show'\n");
		printf("Delete a word (for admins) - 'del'\n>");
		printf("Scan a thesaurus from file - 'read'\n>");
		(void)scanf("%s", c);
		if (strcmp(c, "add") == 0) { //done
			addw(thes);
		}
		if (strcmp(c, "cp") == 0) { //done but not for Russian
			cpf(thes);
		}
		if (strcmp(c, "add_t") == 0) {  //done
			addt(thes);
		}
		if (strcmp(c, "show") == 0) {  //done
			print(thes);
		}
		if (strcmp(c, "tr") == 0) {  //done
			tr(thes);
		}
		if (strcmp(c, "del") == 0) {  //done
			del(thes);
		}
		if (strcmp(c, "read") == 0) {   //TODO
			read(thes);
		}
		goto LOOP;
	}
	free(c);
	return 0;
}