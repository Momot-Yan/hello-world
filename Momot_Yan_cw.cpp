//#include <stdio.h>
//#include <string.h>
//#include <ctype.h>
//#include <stdlib.h>
//#include <locale.h>
//
//////////////////////////////////////////////////////////////////////////
//
//char** read_text(size_t* text_size);
//void remove_duplicates(char** text, size_t* text_size);
//void user_interaction(char** text, size_t text_size);
//void free_text(char** text, size_t text_size);
//void write_text(char** text, size_t text_size);
//
//////////////////////////////////////////////////////////////////////////
//
//int main() {
//
//	setlocale(LC_ALL, "Rus");
//	char** text; // двумерный массив с вводимым текстом
//	size_t text_size; // количество предложений в тексте
//
//	text = read_text(&text_size);
//
//	remove_duplicates(text, &text_size);
//
//	user_interaction(text, text_size);
//
//	write_text(text, text_size);
//
//	free_text(text, text_size);
//
//	return 0;
//}
//
//////////////////////////////////////////////////////////////////////////
//
//// Функции для ввода-вывода и очистки памяти
//
//void add_sentence_into_text(char*** text, size_t* text_size, size_t* text_capacity, char* sentence, size_t sentence_size) {
//	sentence_size++;
//	sentence[sentence_size - 1] = 0; // добавляем терминальный символ в конец предложения
//
//	sentence = (char*)realloc(sentence, sizeof(char) * sentence_size);
//
//	// добавляем предложение в конец текста (если место кончилось, увеличиваем размер массива)
//	if (*text_size == (*text_capacity - 1)) {
//		*text_capacity *= 2;
//		*text = (char**)realloc(*text, *text_capacity * (sizeof(char*)));
//	}
//	(*text_size)++;
//	(*text)[*text_size - 1] = sentence;
//
//	// помещаем в массив предложений текущее предложение, предварительно уменьшив его размер с cur_sentence_capacity до истинного cur_sentence_size
//	(*text)[*text_size - 1] = (char*)realloc(sentence, sizeof(char) * sentence_size);
//
//	return;
//}
//
//char** read_text(size_t* text_size) {
//	printf(" \nВведите, пожалуйста, текст:\n");
//
//	*text_size = 0;
//	size_t text_capacity = 100;
//	char** text = (char**)malloc(sizeof(char*) * text_capacity);
//
//	size_t cur_sentence_size = 0;
//	size_t cur_sentence_capacity = 100;
//	char* cur_sentence = (char*)malloc(sizeof(char) * cur_sentence_capacity);
//
//	for (int cur_symbol = getchar(); ; cur_symbol = getchar()) {
//
//		if ((cur_symbol == '\r') || (cur_symbol == '\0') || (cur_symbol == '\n')) {
//			if (cur_sentence_size > 0)
//				add_sentence_into_text(&text, text_size, &text_capacity, cur_sentence, cur_sentence_size);
//			else
//				free(cur_sentence); // предложение не добавляется в text, а значит не будет память освобождена. для избежания утечки освобождаем сейчас
//			break;
//		}
//		else {
//			// добавление символа в конец предложения (если место кончилось, увеличиваем размер массива)
//			if (cur_sentence_size == (cur_sentence_capacity - 2)) {
//				cur_sentence_capacity *= 2;
//				cur_sentence = (char*)realloc(cur_sentence, (sizeof(char) * cur_sentence_capacity));
//			}
//			cur_sentence_size++;
//			cur_sentence[cur_sentence_size - 1] = (char)cur_symbol;
//
//			if (cur_symbol == '.') {
//				add_sentence_into_text(&text, text_size, &text_capacity, cur_sentence, cur_sentence_size);
//
//				// создаем новое пустое предложение
//				cur_sentence_size = 0;
//				cur_sentence_capacity = 100;
//				cur_sentence = (char*)malloc(sizeof(char) * cur_sentence_capacity);
//			}
//
//		}
//	}
//
//
//	return text;
//}
//
//void write_text(char** text, size_t text_size) {
//	printf("\nИтог обработки текста:\n");
//
//	for (size_t i = 0; i < text_size; i++)
//		printf("%s", text[i]);
//
//	return;
//}
//
//void free_text(char** text, size_t text_size)
//{
//	for (size_t i = 0; i < text_size; i++)
//		free(text[i]);
//
//	free(text);
//
//	return;
//}
//
//////////////////////////////////////////////////////////////////////////
//
//// Функции для обязательной обработки текста
//
//// Возвращает 1, если равны, и 0 в противнм случае
//int check_equal_anycase(char* str1, char* str2) {
//	if (strlen(str1) != strlen(str2))
//		return 0;
//
//	for (const char* ptr1 = str1, *ptr2 = str2; *ptr1 != '\0'; ptr1++, ptr2++) {
//		if (toupper(*ptr1) != toupper(*ptr2))
//			return 0;
//	}
//
//	return 1;
//}
//
//void remove_duplicates(char** text, size_t* text_size)
//{
//	printf("\nЗапущена функция remove_duplicates, удаляющая одинаковые предложения в тексте. \n");
//
//	size_t count_Duplicates = 0;
//	int* toRemove = (int*)malloc((*text_size) * sizeof(int));
//	//массив будет хранить 1 для номеров тех предложений, которые являются повторами и подлежат удалению
//
//	for (size_t i = 0; i < *text_size; i++)
//		toRemove[i] = 0;
//
//	for (size_t i = 0; i < (*text_size); i++) {
//		for (size_t j = 0; j < (*text_size); j++) {
//			if ((i != j) && (check_equal_anycase(text[i], text[j]) == 1)) {
//				toRemove[j] = 1;
//				count_Duplicates += 1;
//				break;
//			}
//		}
//	}
//
//	for (size_t i = 0, unique_Sentences = 0; i < *text_size; i++) {
//		if (toRemove[i] == 0) {
//			text[unique_Sentences] = text[i];
//			unique_Sentences++;
//		}
//		else free(text[i]);
//	}
//
//	*text_size -= count_Duplicates;
//	realloc(text, sizeof(char*) * *text_size);
//
//
//	return;
//}
//
//////////////////////////////////////////////////////////////////////////
//
//// Функции для опциональной обработки текста
//
//// Функция, выводящая список всех цифр в тексте и частоту цифр
//void func1_search_numbers(char** text, size_t text_size) {
//
//	printf("\nЗапущена функция, выводящая список всех цифр, встречаемых во всем тексте и частоту цифр. \n");
//
//	size_t count_numbers[10];
//	for (size_t k = 0; k < 10; k++)
//		count_numbers[k] = 0;
//
//	for (size_t sent_num = 0; sent_num < text_size; sent_num++)
//		for (char* symb = text[sent_num]; *symb != '\0'; symb++)
//			for (size_t digit = 0; digit < 10; digit++)
//				if (*symb == ('0' + digit))
//					count_numbers[digit]++;
//
//	//Список всех цифр, встречаемых во всем тексте
//	printf("Список всех цифр, встречаемых во всем тексте: ");
//	for (size_t k = 0; k < 10; k++) {
//		if (count_numbers[k] != 0)
//			printf("%llu ", k);
//	}
//	printf("\n");
//
//	//частота всех цифр, встречаемых во всем тексте 
//	for (size_t k = 0; k < 10; k++) {
//		if (count_numbers[k] != 0)
//			printf("Цифра %llu найдена в тексте %llu раз.\n", k, count_numbers[k]);
//	}
//
//	return;
//};
//
//// Функция преобразования каждого предложения так, чтобы символы, кроме разделительных, шли в обратном порядке
//void func2_reverse_words(char** text, size_t text_size) {
//
//	printf("\nЗапущена функция преобразования каждого предложения так, чтобы символы, кроме разделительных, шли в обратном порядке. \n");
//
//	for (size_t sent_num = 0; sent_num < text_size; sent_num++) {
//		for (char* i1 = text[sent_num], *i2 = text[sent_num] + strlen(text[sent_num]) - 1; i1 < i2; ) {
//			const bool i1_is_separator = (*i1 == ' ') || (*i1 == ',') || (*i1 == '.');
//			const bool i2_is_separator = (*i2 == ' ') || (*i2 == ',') || (*i2 == '.');
//
//			if ((!i1_is_separator) && (!i1_is_separator)) {
//				const char tmp = *i1;
//				*i1 = *i2;
//				*i2 = tmp;
//				i1++;
//				i2--;
//			}
//			else {
//				if (i1_is_separator)
//					i1++;
//				if (i2_is_separator)
//					i2--;
//			}
//		}
//
//	}
//
//	return;
//}
//
//void print_debug(char** text, size_t text_size) {
//	printf("Sentences:\n");
//	for (size_t i = 0; i < text_size; i++)
//		printf("Sent%llu [%p]: %s\n", i, text[i], text[i]);
//}
//
//// Функция удаления тех предложений, которые содержат "physics"
//void func3_rem_physics(char** text, size_t* text_size, const char* substr) {
//
//	printf("\nЗапущена функция удаления тех предложений, которые содержат 'physics'. \n");
//
//	print_debug(text, *text_size);
//	size_t place_To_Insert = 0;
//	for (size_t i = 0; i < *text_size; i++) {
//		if (strstr(text[i], substr) == NULL) {
//			text[place_To_Insert] = text[i];
//			place_To_Insert++;
//			print_debug(text, *text_size);
//		}
//		else {
//			free(text[i]);
//			print_debug(text, *text_size);
//		}
//	}
//
//	*text_size = place_To_Insert;
//
//	return;
//}
//
//// Функция подсчета количества 3-символьных слов в заданном предложении
//int count_3_char_word_str(const char* sentence) {
//	int count_3_char_word = 0;   // счетчик слов длины 3 в заданном предложении
//	int Word_Len = 0;            // длина текущего слова
//	int isWord = 0;              // индикатор слова (isWord == 1 означает продолжение слова, иначе - конец слова)
//
//	// пробег по символам строки
//	for (const char* symb = sentence; *symb != '\0'; symb++) {
//		if ((*symb == ' ') || (*symb == '.') || (*symb == ',')) {
//			if ((isWord == 1) && (Word_Len == 3))
//				count_3_char_word++;
//			isWord = 0; // слово закончилось
//			Word_Len = 0;
//		}
//		else
//			Word_Len = 1;
//		Word_Len++;
//	}
//
//	return count_3_char_word;
//}
//
//// Функция определения, в каком из двух заданных предложений больше 3-символьных слов 
//int compare_3_char_word_str(const char* a, const char* b) {
//	const int cnt1 = count_3_char_word_str(a);
//	const int cnt2 = count_3_char_word_str(b);
//
//	if (cnt1 > cnt2)
//		return 1;
//	else if (cnt1 < cnt2)
//		return -1;
//	else
//		return 0;
//}
//
//// Функция сортировки предложений по количеству в них слов, имеющих длину 3
//void func4_sort_3_char_word_str(char** text, size_t text_size) {
//
//	printf("\nЗапущена функция сортировки предложений, по количеству в них слов, имеющих длину 3. \n");
//
//	int (*comparator) (const void*, const void*) = (int (*) (const void*, const void*)) compare_3_char_word_str;
//	qsort(text, text_size, sizeof(char*), comparator);
//
//	return;
//}
//
//void user_interaction(char** text, size_t text_size)
//{
//
//	printf(" \nПрограмма предлагает выбор одного из следующих действий:\n");
//	printf("1: Вывести список всех цифр, встречаемых во всем тексте и их частоту.\n");
//	printf("2: Преобразовать каждое предложение так, чтобы символы, кроме разделительных, шли в обратном порядке.\n");
//	printf("3: Удалить все предложения в которых встречается слово “physics”.\n");
//	printf("4: Отсортировать предложения по уменьшению количества слов длина которых равняется 3.\n");
//	printf("Любой иной символ: при вводе программа заверит работу.\n");
//	printf(" \nВведите, пожалуйста, цифру от 1 до 4 для выбора одного из действий:\n");
//
//	int option = 0;
//	scanf_s("%d", &option, sizeof(option));
//
//	printf("Выбранное действие:\n%d\n", option);
//	switch (option)
//	{
//	case 1:
//		func1_search_numbers(text, text_size);
//		break;
//	case 2:
//		func2_reverse_words(text, text_size);
//		break;
//	case 3: {
//		//text = func3_rem_pattern_strs(text, &text_size);
//		const char substr[8] = "physics";
//		func3_rem_physics(text, &text_size, *substr);
//		break;
//	}
//	case 4:
//		func4_sort_3_char_word_str(text, text_size);
//		break;
//	}
//	return;
//}
//
//////////////////////////////////////////////////////////////////////////