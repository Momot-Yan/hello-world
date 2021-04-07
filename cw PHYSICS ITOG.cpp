#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>

////////////////////////////////////////////////////////////////////////

char** read_text(size_t* text_size);
void remove_duplicates(char** text, size_t* text_size);
char** user_interaction(char** text, size_t* text_size);
void free_text(char** text, size_t text_size);
void write_text(char** text, size_t text_size);
//void func_new(char** text, size_t* text_size);

////////////////////////////////////////////////////////////////////////

int main() {

	setlocale(LC_ALL, "Rus");
	char** text;		 // ��������� ������ � �������� �������
	size_t text_size;    // ���������� ����������� � ������

	text = read_text(&text_size);

	remove_duplicates(text, &text_size);

	text = user_interaction(text, &text_size);

	//func_new(text, &text_size);

	write_text(text, text_size);

	free_text(text, text_size);

	system("pause");
	return 0;
}

////////////////////////////////////////////////////////////////////////

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
	printf("\n���� ��������� ������:\n");

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

	if (text_size > 0)
		free(text);

	return;
}

////////////////////////////////////////////////////////////////////////

// ������� ��� ������������ ��������� ������

int check_equal_anycase(char* str1, char* str2) {
	if (strlen(str1) != strlen(str2))
		return 0;

	for (const char* ptr1 = str1, *ptr2 = str2; *ptr1 != '\0'; ptr1++, ptr2++) {
		if (toupper(*ptr1) != toupper(*ptr2))
			return 0;
	}

	return 1;
}

void remove_duplicates(char** text, size_t* text_size)
{

	//printf("\n�������� ������� remove_duplicates, ��������� ���������� ����������� � ������. \n");

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
	//printf("\n�������� ���������� ���������� ���������.\n");

	return;
}

////////////////////////////////////////////////////////////////////////

// ������� ��� ������������ ��������� ������

// �������, ��������� ������ ���� ���� � ������ � ������� ����
void func1_search_numbers(char** text, size_t text_size) {

	printf("\n�������� �������, ��������� ������ ���� ����, ����������� �� ���� ������ � ������� ����. \n");

	size_t count_numbers[10];
	for (size_t k = 0; k < 10; k++)
		count_numbers[k] = 0;

	for (size_t sent_num = 0; sent_num < text_size; sent_num++)
		for (char* symb = text[sent_num]; *symb != '\0'; symb++)
			for (size_t digit = 0; digit < 10; digit++)
				if (*symb == ('0' + digit))
					count_numbers[digit]++;

	//������ ���� ����, ����������� �� ���� ������
	printf("������ ���� ����, ����������� �� ���� ������: ");
	for (size_t k = 0; k < 10; k++) {
		if (count_numbers[k] != 0)
			printf("%llu ", k);
	}
	printf("\n");

	//������� ���� ����, ����������� �� ���� ������ 
	for (size_t k = 0; k < 10; k++) {
		if (count_numbers[k] != 0)
			printf("����� %llu ������� � ������ %llu ���.\n", k, count_numbers[k]);
	}

	return;
};

// ������� �������������� ������� ����������� ���, ����� �������, ����� ��������������, ��� � �������� �������
void func2_reverse_words(char** text, size_t text_size) {

	printf("\n�������� ������� �������������� ������� ����������� ���, ����� �������, ����� ��������������, ��� � �������� �������. \n");

	for (size_t sent_num = 0; sent_num < text_size; sent_num++) {
		for (char* i1 = text[sent_num], *i2 = text[sent_num] + strlen(text[sent_num]) - 1; i1 < i2; ) {
			const bool i1_is_separator = (*i1 == ' ') || (*i1 == ',') || (*i1 == '.');
			const bool i2_is_separator = (*i2 == ' ') || (*i2 == ',') || (*i2 == '.');
			//printf("[%d], [%d]\n", i1_is_separator, i2_is_separator);
			if ((!i1_is_separator) && (!i2_is_separator)) {
				const char tmp = *i1;
				*i1 = *i2;
				*i2 = tmp;
				i1++;
				i2--;
			}
			else {
				if (i1_is_separator)
					i1++;
				if (i2_is_separator)
					i2--;
			}
		}

	}

	return;

}

void print_debug(char** text, size_t text_size) {
	printf("Sentences [%p]:\n", text);
	for (size_t i = 0; i < text_size; i++) {
		printf("Sent%llu [%p]: ", i, text[i]);
		printf("%s\n", text[i]);
	}
}

// ������� �������� ��� �����������, ������� �������� "physics"
char** func3_rem__substr(char** text, size_t* text_size, const char* substr)
{
	printf("\n�������� ������� �������� ��� �����������, ������� �������� 'physics'.\n");

	for (size_t sent_num = 0; sent_num < *text_size; sent_num++) {
		//���� ����������� �������� "physics", �� ������� ��� �������
		if (strstr(text[sent_num], substr) != NULL)
		{
			//printf("\n Sentence which has subsring 'physics'  is: \n%s\n", text[sent_num]);
			free(text[sent_num]);
			// ������� ����������� �������� ������� text
			(*text_size)--;
			memcpy(&text[sent_num], &text[sent_num + 1], sizeof(char*) * (*text_size - sent_num));
			text = (char**)realloc(text, *text_size * sizeof(char*));
			sent_num--;

		}
	}

	return text;
}

//void* copy_memory(void* source, size_t bytes_to_copy) {
//	void* destination = malloc(bytes_to_copy);
//	memcpy(destination, source, bytes_to_copy);
//	return destination;
//}

// ������� �������� ���������� 3-���������� ���� � �������� �����������
int count_3_char_word_str(const char* sentence) {
	int count_3_char_word = 0;   // ������� ���� ����� 3 � �������� �����������
	int Word_Len = 0;            // ����� �������� �����
	int isWord = 0;              // ��������� ����� (isWord == 1 �������� ����������� �����, ����� - ����� �����)

	// ������ �� �������� ������
	for (const char* symb = sentence; *symb != '\0'; symb++) {
		if ((*symb == ' ') || (*symb == '.') || (*symb == ',')) {
			if ((isWord == 1) && (Word_Len == 3))
				count_3_char_word++;
			isWord = 0; // ����� �����������
			Word_Len = 0;
		}
		else
			Word_Len = 1;
		Word_Len++;
	}

	return count_3_char_word;
}

// ������� �����������, � ����� �� ���� �������� ����������� ������ 3-���������� ���� 
int compare_3_char_word_str(const char* a, const char* b) {
	const int cnt1 = count_3_char_word_str(a);
	const int cnt2 = count_3_char_word_str(b);

	if (cnt1 > cnt2)
		return 1;
	else if (cnt1 < cnt2)
		return -1;
	else
		return 0;

}

// ������� ���������� ����������� �� ���������� � ��� ����, ������� ����� 3
void func4_sort_3_char_word_str(char** text, size_t text_size) {

	printf("\n�������� ������� ���������� �����������, �� ���������� � ��� ����, ������� ����� 3. \n");

	int (*comparator) (const void*, const void*) = (int (*) (const void*, const void*)) compare_3_char_word_str;
	qsort(text, text_size, sizeof(char*), comparator);


	return;
}

char** user_interaction(char** text, size_t* text_size)
{
	if (text_size == 0) {
		printf("������ ���������� ������ 0.\nThe size of the text is 0.");
	}
	else
	{

		printf(" \n��������� ���������� ����� ������ �� ��������� ��������:\n");
		printf("1: ������� ������ ���� ����, ����������� �� ���� ������ � �� �������.\n");
		printf("2: ������������� ������ ����������� ���, ����� �������, ����� ��������������, ��� � �������� �������.\n");
		printf("3: ������� ��� ����������� � ������� ����������� ����� �physics�.\n");
		printf("4: ������������� ����������� �� ���������� ���������� ���� ����� ������� ��������� 3.\n");
		printf("����� ���� ������: ��� ����� ��������� ������� ������.\n");
		printf(" \n�������, ����������, ����� �� 1 �� 4 ��� ������ ������ �� ��������:\n");


		int option = 0;
		scanf_s("%d", &option, sizeof(option));

		printf("��������� ��������:\n%d\n", option);
		switch (option)
		{
		case 1:
			func1_search_numbers(text, *text_size);
			break;
		case 2:
			func2_reverse_words(text, *text_size);
			break;
		case 3: {
			//text = func3_rem_pattern_strs(text, &text_size);
			const char* substr = "physics";
			text = func3_rem__substr(text, text_size, substr);
			break;
		}
		case 4:
			func4_sort_3_char_word_str(text, *text_size);
			break;
		}
	}
return text;
}

////////////////////////////////////////////////////////////////////////