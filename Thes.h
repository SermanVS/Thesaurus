#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
using namespace std;

struct Word {
	char* word;
	char* tr; //key change
	int num = 0;
	Word();
	Word(char*, char*);

};
struct Thesaurus {
	vector<Word> eng;
	vector<Word> rus;
};
void print_word(Word);
void cpf(Thesaurus);
void fprint_word(Word, FILE*);
void addw(Thesaurus&);
void addt(Thesaurus&);
void print(Thesaurus&);
void tr(Thesaurus&);
void del(Thesaurus&);
void read(Thesaurus&);