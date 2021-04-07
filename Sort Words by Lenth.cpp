#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>

char** read_text(size_t* text_size);
int Cmp_Word_Lenth(const void* a, const void* b);

char** read_text(size_t* text_size);
void remove_duplicates(char** text, size_t* text_size);
void user_interaction(char** text, size_t text_size);
void free_text(char** text, size_t text_size);
void write_text(char** text, size_t text_size);
void func_new(char** text, size_t* text_size);
size_t func_Sort_Words_by_Lenth(char* str);
size_t count_symbols_sent(char* sentence);

/*
	������� �����, ���������� ������������ � ������ � ����������� � ������ ���������� ��������
*/

int main(void) {

	setlocale(LC_ALL, "Rus");
	char** text; // ��������� ������ � �������� �������
	size_t text_size; // ���������� ����������� � ������

	text = read_text(&text_size);

	remove_duplicates(text, &text_size);

	/*for (size_t sent_num = 0; sent_num < text_size; sent_num++)
		func_Sort_Words_by_Lenth(text[sent_num]);*/
	for (size_t sent_num = 0; sent_num < text_size; sent_num++) {
		text[sent_num] = (char*)func_Sort_Words_by_Lenth((char*)text[sent_num]);
	}
	free_text(text, text_size);

	return 0;
}


////////////////////////////////////////////////////
// ������� ��� �����-������ � ������� ������

void add_sentence_into_text(char*** text, size_t* text_size, size_t* text_capacity, char* sentence, size_t sentence_size) {
	sentence_size++;
	sentence[sentence_size - 1] = 0; // ��������� ������������ ������ � ����� �����������

	sentence = (char*)realloc(sentence, sizeof(char) * sentence_size);

	// ��������� ����������� � ����� ������ (���� ����� ���������, ����������� ������ �������)
	if (*text_size == (*text_capacity - 1)) {
		*text_capacity *= 2;
		*text = (char**)realloc(*text, *text_capacity * (sizeof(char*)));
	}
	(*text_size)++;
	(*text)[*text_size - 1] = sentence;

	// �������� � ������ ����������� ������� �����������, �������������� �������� ��� ������ � cur_sentence_capacity �� ��������� cur_sentence_size
	(*text)[*text_size - 1] = (char*)realloc(sentence, sizeof(char) * sentence_size);

	return;
}

char** read_text(size_t* text_size) {
	printf(" \n�������, ����������, �����:\n");

	*text_size = 0;
	size_t text_capacity = 100;
	char** text = (char**)malloc(sizeof(char*) * text_capacity);

	size_t cur_sentence_size = 0;
	size_t cur_sentence_capacity = 100;
	char* cur_sentence = (char*)malloc(sizeof(char) * cur_sentence_capacity);

	for (int cur_symbol = getchar(); ; cur_symbol = getchar()) {

		if ((cur_symbol == '\r') || (cur_symbol == '\0') || (cur_symbol == '\n')) {
			if (cur_sentence_size > 0)
				add_sentence_into_text(&text, text_size, &text_capacity, cur_sentence, cur_sentence_size);
			else
				free(cur_sentence); // ����������� �� ����������� � text, � ������ �� ����� ������ �����������. ��� ��������� ������ ����������� ������
			break;
		}
		else {
			// ���������� ������� � ����� ����������� (���� ����� ���������, ����������� ������ �������)
			if (cur_sentence_size == (cur_sentence_capacity - 2)) {
				cur_sentence_capacity *= 2;
				cur_sentence = (char*)realloc(cur_sentence, (sizeof(char) * cur_sentence_capacity));
			}
			cur_sentence_size++;
			cur_sentence[cur_sentence_size - 1] = (char)cur_symbol;

			if (cur_symbol == '.') {
				add_sentence_into_text(&text, text_size, &text_capacity, cur_sentence, cur_sentence_size);

				// ������� ����� ������ �����������
				cur_sentence_size = 0;
				cur_sentence_capacity = 100;
				cur_sentence = (char*)malloc(sizeof(char) * cur_sentence_capacity);
			}

		}
	}


	return text;
}

void write_text(char** text, size_t text_size) {
	printf("\n�������� ��������� ��������� ������:\n");

	for (size_t i = 0; i < text_size; i++) {
		printf("%s", text[i]);
	}
	printf("\n����� ������ ��������.\n");

	return;
}

void free_text(char** text, size_t text_size)
{
	for (size_t i = 0; i < text_size; i++)
		free(text[i]);

	free(text);

	return;
}

////////////////////////////////////////////////////////////////////////

// ������� ��� ������������ ��������� ������

int check_equal_anycase(char* str1, char* str2) {
	int isEqual = 1; // ��� ���������� ����� �������� 1 ����������
	if (strlen(str1) == strlen(str2))// || (strstr(str1, str2) != NULL) || (strstr(str2, str1) != NULL))
	{
		for (const char* ptr1 = str1, *ptr2 = str2; *ptr1 != '\0'; ptr1++, ptr2++) {
			if (toupper(*ptr1) != toupper(*ptr2))
				isEqual = 0;

		}
	}
	else
		isEqual = 0;

	return isEqual;
}

void remove_duplicates(char** text, size_t* text_size)
{

	printf("\n�������� ������� remove_duplicates, ��������� ���������� ����������� � ������. \n");

	size_t count_Duplicates = 0;
	int* toRemove = (int*)malloc((*text_size) * sizeof(int));
	//������ ����� ������� 1 ��� ������� ��� �����������, ������� �������� ��������� � �������� ��������

	for (size_t i = 0; i < *text_size; i++)
		toRemove[i] = 0;

	for (size_t i = 0; i < (*text_size); i++) {
		for (size_t j = 0; j < (*text_size); j++) {
			if ((i != j) && (check_equal_anycase(text[i], text[j]) == 1)) {
				toRemove[j] = 1;
				count_Duplicates += 1;
				break;
			}
		}
	}

	for (size_t i = 0, unique_Sentences = 0; i < *text_size; i++) {
		if ((toRemove[i] == 0)) {
			text[unique_Sentences] = text[i];
			unique_Sentences++;
		}
		else free(text[i]);
	}

	*text_size -= count_Duplicates;
	realloc(text, sizeof(char*) * *text_size);


	return;
}

////////////////////////////////////////////////////////////////////////

// �� ���� �������� �����������. ��������� ������������� ��� ����� �� �������� �����

// ������� ��������� ����� �� ����� 
int Cmp_Word_Lenth(const void* a, const void* b) {
	return strlen((char*)b) - strlen((char*)a);
}

// ������� �������� �������� � �����������, �� ������� ��������� �������������� �������� (������� � ��������)
size_t count_symbols_sent(char* sentence) {
	//��������� ������������ ������ � ����� �����������
	if (strstr(sentence, "\0") == NULL) {
		size_t sentence_size = strlen(sentence);
		sentence_size++;
		char* sentence = (char*)malloc(sizeof(char) * sentence_size);
		sentence[sentence_size - 1] = '\0';
	}

	int count_symb_words = 0;		// ������� �������� ���� (��������� ���� � ����)
	int count_symb_separators = 0;  // ������� �������������� ��������
	int isWord = 0;					// ��������� ����� (1 �������� ����������� �����, 0 - ����� �����)
	int Word_Len = 0;				// ����� �������� �����

	char* pre_last_separator_symb = sentence;
	// ������ �� �������� ������
	for (const char* symb = sentence; *symb != '\0'; symb++) {
		if ((*symb == ' ') || (*symb == '.') || (*symb == ',')) {
			if (isWord == 1) {
				pre_last_separator_symb = (char*)(symb - Word_Len);
			}

			else {
				pre_last_separator_symb = (char*)symb;
			}

			// ind_space_comma - ��������� "�����������" �������� ��������������� ������� 
			// ����� 1 � ������, ����� ���������� ������ ��� ��������������, �� ��� �������, � ������� ������ - ������ 

			int ind_space_comma = 0;
			if ((*pre_last_separator_symb != *symb) && (*pre_last_separator_symb == ' ') && (*symb == ','))
				ind_space_comma = 1;

			// ��������� 1 � �������� ����. �������� ������ � ������, ���� ���������� ������ ��� � ������� ����� 
			// ��� ������� ����������� "����������" (����� - ������� ������ - ������ ��������������)
			if ((isWord == 1) && (ind_space_comma == 1))
				count_symb_separators++;
			isWord = 0; // ����� �����������
		}
		else {
			Word_Len++;
			count_symb_words++;
			isWord = 1;
		}
	}

	return count_symb_words + count_symb_separators;
}

// ������� ���������� ������� ���� � �����������
void fill_in_the_Words_Massive(char* sentence, char** words_massive, size_t words_cnt) {

	int Word_Len = 0;				// ����� �������� �����
	int isWord = 0;					// ��������� ����� (1 �������� ����������� �����, 0 - ����� �����)
	size_t word_num = 0;			// ������� ���� ��� ���������� ������� words_massive 

	size_t symb_num = 0;
	// ������ �� �������� ������
	for (const char* symb = sentence; *symb != '\0'; symb++) {
		symb_num++;

		if ((*symb == ' ') || (*symb == '.') || (*symb == ',')) {
			if (isWord == 1) {

				isWord = 0; // ����� �����������
				char* Word = (char*)malloc(sizeof(char) * Word_Len);
				for (size_t letter_num = 0; letter_num < Word_Len; letter_num++) {
					Word[letter_num] = sentence[symb_num - Word_Len + Word_Len];
				}
				words_massive[word_num] = (char* )Word;
				word_num++;
			}
			Word_Len = 0;

			if (word_num == words_cnt)
				break;
		}
		else
			Word_Len++;
	}

	return;
}

// ������� ���������� ���� � ������ �� �����  
char* func_Sort_Words_by_Lenth(char* str) {
	if (str == 0)
		return 0;

	// ������� ���������� ����
	size_t words_cnt = count_symbols_sent(str);
	char** words_massive = (char**)malloc(sizeof(char*) * words_cnt);
	fill_in_the_Words_Massive(str, words_massive, words_cnt);


	if (words_cnt == 0) {
		printf("can't find any words!\n");
		return 0;
	}



	// ���������� ������� ���� 
	qsort(words_massive, words_cnt, sizeof(char*), Cmp_Word_Lenth);

	char* new_Sorted_str = (char*)malloc(sizeof(char) * words_cnt);

	// ������ ���� �� ������ �������� �� ������ ���������
	for (size_t word_num = 0; word_num < words_cnt; ++word_num)
		new_Sorted_str[word_num] = *(words_massive[word_num]);

	return new_Sorted_str;
}
