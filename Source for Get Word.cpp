
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <conio.h>

#define BLUE "\033[9;34m" // синий цвет
#define NONE "\033[0m" // белый цвет

///////////////////////////////////////
// main


char** read_text(size_t* text_size);
int remove_duplicated_sentences(char** text, size_t text_size);
void user_interaction(char** text, size_t text_size);
void free_text(char** text, size_t text_size);
void write_text(char** text, size_t text_size);
const char* get_the_Word_from_Sent(const char* sentence, size_t Word_Number);

int main()
{
	setlocale(LC_ALL, "Rus");

	size_t text_size = 0;
	size_t Word_Number = 2;
	const char* sent = "one two three ozero";

	const char* Word_start = get_the_Word_from_Sent(sent, Word_Number);
	const char* Word_fin = Word_start + strcspn(Word_start, " ,.");

	for (const char* ptr = Word_start; ptr < Word_fin; ptr++)
		printf("%c", *ptr);
	printf("\n\n");
	
	return 0;
}

//////////////////////////////////////
// Функции для опциональной обработки текста

//int* ptr;
//const int* ptr; // pointer to const (no change memory)
//int* const ptr; // const pointer (no change pointer)
//const int* const ptr; // const pointer to const (no change pointer and memory)

const char* get_the_Word_from_Sent(const char* sentence, size_t Word_Number) {
	size_t cnt_words = 0;
	int isWord = 0;					// индикатор слова (1 означает продолжение слова, 0 - конец слова)

	// пробег по символам строки
	for (const char* symb = sentence; *symb != '\0'; symb++) {
		if ((*symb == ' ') || (*symb == '.') || (*symb == ',')) {
			if (isWord == 1)
				cnt_words++;
			isWord = 0; // слово закончилось
		}
		else {
			if ((isWord == 0) && (cnt_words == (Word_Number)))
				return symb;
			isWord = 1;
		}
	}

	printf("No such word in the sentence\nВ предложении нет такого слова");
	return NULL;
}