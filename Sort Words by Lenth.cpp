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
	вывести слово, содержащее максимальное в строке и минимальное в строке количество символов
*/

int main(void) {

	setlocale(LC_ALL, "Rus");
	char** text; // двумерный массив с вводимым текстом
	size_t text_size; // количество предложений в тексте

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
// Функции для ввода-вывода и очистки памяти

void add_sentence_into_text(char*** text, size_t* text_size, size_t* text_capacity, char* sentence, size_t sentence_size) {
	sentence_size++;
	sentence[sentence_size - 1] = 0; // добавляем терминальный символ в конец предложения

	sentence = (char*)realloc(sentence, sizeof(char) * sentence_size);

	// добавляем предложение в конец текста (если место кончилось, увеличиваем размер массива)
	if (*text_size == (*text_capacity - 1)) {
		*text_capacity *= 2;
		*text = (char**)realloc(*text, *text_capacity * (sizeof(char*)));
	}
	(*text_size)++;
	(*text)[*text_size - 1] = sentence;

	// помещаем в массив предложений текущее предложение, предварительно уменьшив его размер с cur_sentence_capacity до истинного cur_sentence_size
	(*text)[*text_size - 1] = (char*)realloc(sentence, sizeof(char) * sentence_size);

	return;
}

char** read_text(size_t* text_size) {
	printf(" \nВведите, пожалуйста, текст:\n");

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
				free(cur_sentence); // предложение не добавляется в text, а значит не будет память освобождена. для избежания утечки освобождаем сейчас
			break;
		}
		else {
			// добавление символа в конец предложения (если место кончилось, увеличиваем размер массива)
			if (cur_sentence_size == (cur_sentence_capacity - 2)) {
				cur_sentence_capacity *= 2;
				cur_sentence = (char*)realloc(cur_sentence, (sizeof(char) * cur_sentence_capacity));
			}
			cur_sentence_size++;
			cur_sentence[cur_sentence_size - 1] = (char)cur_symbol;

			if (cur_symbol == '.') {
				add_sentence_into_text(&text, text_size, &text_capacity, cur_sentence, cur_sentence_size);

				// создаем новое пустое предложение
				cur_sentence_size = 0;
				cur_sentence_capacity = 100;
				cur_sentence = (char*)malloc(sizeof(char) * cur_sentence_capacity);
			}

		}
	}


	return text;
}

void write_text(char** text, size_t text_size) {
	printf("\nКонечный результат обработки текста:\n");

	for (size_t i = 0; i < text_size; i++) {
		printf("%s", text[i]);
	}
	printf("\nВывод текста завершен.\n");

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

// Функции для обязательной обработки текста

int check_equal_anycase(char* str1, char* str2) {
	int isEqual = 1; // при совпадении строк значение 1 сохранится
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

	printf("\nЗапущена функция remove_duplicates, удаляющая одинаковые предложения в тексте. \n");

	size_t count_Duplicates = 0;
	int* toRemove = (int*)malloc((*text_size) * sizeof(int));
	//массив будет хранить 1 для номеров тех предложений, которые являются повторами и подлежат удалению

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

// На вход подается предложение. Требуется отсортировать его слова по убыванию длины

// Функция сравнения строк по длине 
int Cmp_Word_Lenth(const void* a, const void* b) {
	return strlen((char*)b) - strlen((char*)a);
}

// Функция подсчета символов в предложении, за вычетом повторных разделительных символов (запятых и пробелов)
size_t count_symbols_sent(char* sentence) {
	//добавляем терминальный символ в конец предложения
	if (strstr(sentence, "\0") == NULL) {
		size_t sentence_size = strlen(sentence);
		sentence_size++;
		char* sentence = (char*)malloc(sizeof(char) * sentence_size);
		sentence[sentence_size - 1] = '\0';
	}

	int count_symb_words = 0;		// счетчик символов слов (латинских букв и цифр)
	int count_symb_separators = 0;  // счетчик разделительных символов
	int isWord = 0;					// индикатор слова (1 означает продолжение слова, 0 - конец слова)
	int Word_Len = 0;				// длина текущего слова

	char* pre_last_separator_symb = sentence;
	// пробег по символам строки
	for (const char* symb = sentence; *symb != '\0'; symb++) {
		if ((*symb == ' ') || (*symb == '.') || (*symb == ',')) {
			if (isWord == 1) {
				pre_last_separator_symb = (char*)(symb - Word_Len);
			}

			else {
				pre_last_separator_symb = (char*)symb;
			}

			// ind_space_comma - индикатор "подходящего" двойного разделительного символа 
			// равен 1 в случае, когда предыдущий символ был разделительным, но был запятой, а текущий символ - пробел 

			int ind_space_comma = 0;
			if ((*pre_last_separator_symb != *symb) && (*pre_last_separator_symb == ' ') && (*symb == ','))
				ind_space_comma = 1;

			// добавляем 1 к счетчику разд. символов только в случае, если предыдущий символ был в составе слова 
			// или текущий разделитель "подходящий" (иначе - текущий символ - лишний разделительный)
			if ((isWord == 1) && (ind_space_comma == 1))
				count_symb_separators++;
			isWord = 0; // слово закончилось
		}
		else {
			Word_Len++;
			count_symb_words++;
			isWord = 1;
		}
	}

	return count_symb_words + count_symb_separators;
}

// Функция заполнения массива слов в предложении
void fill_in_the_Words_Massive(char* sentence, char** words_massive, size_t words_cnt) {

	int Word_Len = 0;				// длина текущего слова
	int isWord = 0;					// индикатор слова (1 означает продолжение слова, 0 - конец слова)
	size_t word_num = 0;			// счетчик слов для заполнения массива words_massive 

	size_t symb_num = 0;
	// пробег по символам строки
	for (const char* symb = sentence; *symb != '\0'; symb++) {
		symb_num++;

		if ((*symb == ' ') || (*symb == '.') || (*symb == ',')) {
			if (isWord == 1) {

				isWord = 0; // слово закончилось
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

// функция сортировки слов в строке по длине  
char* func_Sort_Words_by_Lenth(char* str) {
	if (str == 0)
		return 0;

	// находим количество слов
	size_t words_cnt = count_symbols_sent(str);
	char** words_massive = (char**)malloc(sizeof(char*) * words_cnt);
	fill_in_the_Words_Massive(str, words_massive, words_cnt);


	if (words_cnt == 0) {
		printf("can't find any words!\n");
		return 0;
	}



	// сортировка массива слов 
	qsort(words_massive, words_cnt, sizeof(char*), Cmp_Word_Lenth);

	char* new_Sorted_str = (char*)malloc(sizeof(char) * words_cnt);

	// запись слов от самого длинного до самого короткого
	for (size_t word_num = 0; word_num < words_cnt; ++word_num)
		new_Sorted_str[word_num] = *(words_massive[word_num]);

	return new_Sorted_str;
}
