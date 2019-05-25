#define _CRT_SECURE_NO_WARNINGS
#include "Thes.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <ctype.h>
#include <vector>
#include <algorithm>
using namespace std;


bool Word::operator== (const Word& wrd) const {
	return !(strcmp(word, wrd.word));
}


Word::Word() {
	word = nullptr;
	tr = nullptr;
}
Word::Word(char* _word, char* _tr) {
	word = (char*)malloc(sizeof(char) * (strlen(_word) + 1));
	tr = (char*)malloc(sizeof(char) * (strlen(_tr) + 1));
	strcpy(word, _word);
	strcpy(tr, _tr);
	num++;
}
void addw(Thesaurus& thes) {
	char* word = (char*)malloc(sizeof(char) * 256);
	char* tr = (char*)malloc(sizeof(char) * 256);

	printf("Which word would you like to add?\n>");
	(void)scanf("%s", word);
	word = (char*)realloc(word, sizeof(char) * (strlen(word) + 1));

	if (word[0] > 'A' && word[0] < 'z') {
		char* tm = (char*)malloc(sizeof(char));
		strcpy(tm, "");
		Word t = Word(word, tm);
		auto it = find(thes.eng.begin(), thes.eng.end(), t);
		if (it != thes.eng.end() && thes.eng.size() > 0) {
			printf("\nThis word is already in Thesaurus. Use add_t function to add a translation.\n");
			return;
		}
		free(tm);
	}
	else {
		char* tm = (char*)malloc(sizeof(char));
		strcpy(tm, "");
		Word t = Word(word, tm);
		auto it = find(thes.rus.begin(), thes.rus.end(), t);
		if (it != thes.rus.end() && thes.rus.size() > 0) {
			printf("\nThis word is already in Thesaurus. Use add_t function to add a translation.\n");
			return;
		}
		free(tm);
	}

	printf("Add translation for %s: ", word);
	(void)scanf("%s", tr);
	tr = (char*)realloc(tr, sizeof(char) * (strlen(tr) + 1));
	if (word[0] > 'A' && word[0] < 'z') {
		Word word1 = Word(word, tr);
		Word word2 = Word(tr, word);
		thes.eng.push_back(word1);
		thes.rus.push_back(word2);
	}
	else {
		Word word1 = Word(word, tr);
		Word word2 = Word(tr, word);
		thes.rus.push_back(word1);
		thes.eng.push_back(word2);
	}
	free(word);
	free(tr);
}
void print(Thesaurus& thes) {
	printf("\n\nThesaurus 2.0\n\n");
	printf("%10s || %s\n", "Eng", "Rus");
	printf("-----------------------------\n");
	for (auto it = thes.eng.begin(); it != thes.eng.end(); ++it) {
		print_word(*it);
	}
	printf("\n\n");
	printf("%10s || %s\n", "Rus", "Eng");
	printf("-----------------------------\n");
	for (auto it = thes.rus.begin(); it != thes.rus.end(); ++it) {
		print_word(*it);
	}
	printf("\nThank for choosing us!\n");

}
void del(Thesaurus& thes) {
	char* word = (char*)malloc(sizeof(char) * 256);
	printf("Enter the word you want to delete\n");
	(void)scanf("%s", word);
	word = (char*)realloc(word, sizeof(char) * (strlen(word) + 1));
	if (word[0] > 'A' && word[0] < 'z') {
		for (auto it = thes.eng.begin(); it != thes.eng.end(); ++it) {
			if (strcmp((*it).word, word) == 0) {
				thes.eng.erase(it);
				break;
			}
		}
	}
	else {
		for (auto it = thes.rus.begin(); it != thes.rus.end(); ++it) {
			if (strcmp((*it).word, word) == 0) {
				thes.rus.erase(it);
				break;
			}
		}
	}
	free(word);
}
void read(Thesaurus& thes) {
	FILE* f;
	Word word;
	char* str = (char*)malloc(sizeof(char) * 256);
	char* istr = (char*)malloc(sizeof(char) * 256);
	char file_name[] = "ThesIn.txt";
	char sep[] = "|";
	if ((f = fopen(file_name, "r")) == NULL) printf("Reading file error\n");
	int strcount = 0;
	int i = 0;
	int k;
	while (!feof(f)) {
		fgets(str, 256, f);
		str = (char*)realloc(str, sizeof(char) * (strlen(str) + 1));
		istr = strtok(str, sep);
		k = 0;
		while (istr != NULL) {
			switch (k) {
			case 0:
				word.word = (char*)malloc(sizeof(char) * 256);
				strcpy(word.word, istr);
				word.word = (char*)realloc(word.word, sizeof(char) * (strlen(word.word) + 1));
				break;
			case 1:
				word.tr = (char*)malloc(sizeof(char) * 256);
				strcpy(word.tr, istr);
				word.tr = (char*)realloc(word.tr, sizeof(char) * (strlen(word.tr) + 1));
				break;
			}
			k++;
			istr = strtok(NULL, sep);
		}
		if (
			word.word[0] > 'A' && word.word[0] < 'z') {
			(thes).eng.push_back(word);
		}
		else {
			(thes).rus.push_back(word);
		}
		i++;
	}
	free(istr);
	free(str);
	fclose(f);
}
void print_word(Word wrd) {

	if (wrd.tr[strlen(wrd.tr) - 1] == '\n') {
		printf("%10s || %s", wrd.word, wrd.tr);
	}
	else printf("%10s || %s\n", wrd.word, wrd.tr);
}
void cpf(Thesaurus thes) {
	FILE* f;
	char file_name[] = "ThesOut.txt";
	if ((f = fopen(file_name, "w")) == NULL) printf("\nError opening file\n");
	for (auto it = thes.eng.begin(); it != thes.eng.end(); ++it) {
		fprint_word(*it, f);
	}
	for (auto it = thes.rus.begin(); it != thes.rus.end(); ++it) {
		fprint_word(*it, f);
	}
	fclose(f);
	printf("Your thesaurus was copied to ThesOut.txt!\n");
}
void fprint_word(Word wrd, FILE* f) {
	fprintf(f, "%s|%s\n", wrd.word, wrd.tr);
}
void tr(Thesaurus& thes) {
	char* word = (char*)malloc(sizeof(char) * 256);
	printf("Enter the word you want to see translation for\n");
	(void)scanf("%s", word);
	word = (char*)realloc(word, sizeof(char) * (strlen(word) + 1));



	if (word[0] > 'A' && word[0] < 'z') {
		for (auto it = thes.eng.begin(); it != thes.eng.end(); ++it) {
			if (strcmp((*it).word, word) == 0) {
				printf("%10s - %s\n", word, (*it).tr);
				break;
			}
		}
	}
	else {
		for (auto it = thes.rus.begin(); it != thes.rus.end(); ++it) {
			if (strcmp((*it).word, word) == 0) {
				printf("%10s - %s\n", word, (*it).tr);
				break;
			}
		}
	}

	free(word);
}
void addt(Thesaurus& thes) {
	char* _word = (char*)malloc(sizeof(char) * 256);
	char* _tr = (char*)malloc(sizeof(char) * 256);
	printf("Which word would you like to add translation for?\n");
	(void)scanf("%s", _word);
	printf("Enter your translation: ");
	(void)scanf("%s", _tr);

	if (_word[0] > 'A' && _word[0] < 'z') {
		for (auto it = thes.eng.begin(); it != thes.eng.end(); ++it) {
			if (strcmp((*it).word, _word) == 0) {
				if (isSubInStr((*it).tr, _tr)) {
					printf("\nThis translation is already there.\n");
					return;
				}
				Word tmp = Word(_tr, (*it).word);
				thes.rus.push_back(tmp);
				(*it).tr = (char*)realloc((*it).tr, sizeof(char) * (strlen((*it).tr) + strlen(_tr) + 3));
				(*it).tr = strcat((*it).tr, "; ");
				(*it).tr = strcat((*it).tr, _tr);
			}
		}
	}
	else {
		for (auto it = thes.rus.begin(); it != thes.rus.end(); ++it) {
			if (strcmp((*it).word, _word) == 0) {
				if (isSubInStr((*it).tr, _tr)) {
					printf("\nThis translation is already there.\n");
					return;
				}
				Word tmp = Word(_tr, (*it).word);
				thes.eng.push_back(tmp);
				(*it).tr = (char*)realloc((*it).tr, sizeof(char) * (strlen((*it).tr) + strlen(_tr) + 3));
				(*it).tr = strcat((*it).tr, "; ");
				(*it).tr = strcat((*it).tr, _tr);
			}
		}
	}
}
bool isSubInStr(const char * str, const char * fnd) {
	bool bExist = false;
	if (str && fnd)
		bExist = strstr(str, fnd) != 0;
	return bExist;
}
