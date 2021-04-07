#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>

//////////////////
/*
������ ����� ������� ����� - "�������" �� ������� ������ ���� char**
�� ������ ���������� ������, ������ ����������� ����������� �������� '\0'
/////////////////////

��� ��������� �������
--
���� char** ������1 ������ ������ ����, ���-�� ���� ������� ����� ���-�� ����������� � ������
���� char** ������1 ������ ����� ����, ���-�� ���� ������� ����� ���-�� ����������� � ������
--
����� ������������� ����� ��� ���������� ����� ����������� ����� � ������ ��� ���������������� �����
//////////////////////////////
���� int ������ �3 ���-�� ��������� � ���������� ����� 0
���� 2 �������, ��������� ������ �����, ��������� 1 ���� � ������ �3

���� int ������� ������������� ������� ����� - �������� ������� �3. ����� ��������� � � ������� �3
������ ����� ����� �������� ��������� ������ �������� (������������ �+1 ��������� ���� int � ������ �3)
--
� ����� �� ������ ��� ������� �� ���� �������� ������� free(mass_1);
/////////////////

for(){

}

*/



void func_new(char** text, size_t* text_size)
{
	printf(" \n�������� func_new, ������� ������ �� �������� ����������� ����: :\n\n");
	
	/*

	��� ��������� �������
	--
	���� char** ������1 ������ ������ ����, ���-�� ���� ������� ����� ���-�� ����������� � ������
	���� char** ������2 ������ ����� ����, ���-�� ���� ������� ����� ���-�� ����������� � ������
	����� ������������� ����� ��� ���������� ����� ����������� ����� � ������ ��� ���������������� �����
	*/


	for (size_t sent_num = 0; sent_num < (*text_size); sent_num++) {
		size_t cnt_Words = 0;
		char** mass_1_start, ** mass_2_finish;
		int isWord = 0;
		for (char* symb = text[sent_num]; *symb != '\0'; symb++) {

			
			//1 isWord == 0 ��� ���� �������� ���������������� ������
			//2 isWord == 1 ��� ���� �������� ���������������� ������
			//3 isWord == 0 ��� ���� �������� �������������� ������
			//4 isWord == 1 ��� ���� �������� �������������� ������
			

			// ��������� �����������
			int is_symb_separator = (int)((*symb == ' ') || (*symb == ',') || (*symb == '.'));
			// is_symb_separator == 0, ������, ��������� �����/�����

			//1 ����
			if (isWord == 0 && is_symb_separator == 0) {
				// �������� ��������� �����
				cnt_Words++;
				//���������� ��������� �� ������ ���������� ����� � ����� ������� �����
				mass_1_start[cnt_Words] = (char*)realloc(mass_1_start, sizeof(char) * (cnt_Words));
				mass_1_start[cnt_Words] = symb;
				continue;
			}
			//2 ����
			else if (isWord == 1 && is_symb_separator == 0) {
				continue;
			}

			//3 ����
			else if (isWord == 0 && is_symb_separator == 1) {
				continue;
			}

			//4 ����
			else if (isWord == 1 && is_symb_separator == 1) {
				// ��������� ��������� �����
				//���������� ��������� �� ������ ���������� ����� � ����� ������� ������
				mass_2_finish[cnt_Words] = (char*)realloc(mass_1_start, sizeof(char) * (cnt_Words));
				mass_2_finish[cnt_Words] = symb;
				continue;
			}

			// ����� ������ ����� � ������ ������ ������������
			// ������� ������������� ������� �����

			size_t number_of_the_Word = 0;
			size_t Word_Len = 0;
			char** Word_Dict = (char**)malloc(sizeof(char*) * 1);
			size_t cnt_different_Words = 0;


			for (number_of_the_Word = 0; number_of_the_Word < cnt_Words; number_of_the_Word++)
			{
				// ����� ����� ��� ���������� ����� ����������� ����� � ������ ��� ���������������� �����
				Word_Len = mass_1_start[number_of_the_Word] - mass_2_finish[number_of_the_Word];

				char* New_Word = (char*)malloc(sizeof(char) * 1);

				for (size_t letter_num = 0; letter_num < Word_Len; letter_num++)
				{
					New_Word = (char*)realloc(New_Word, sizeof(char) * (letter_num+1));
					New_Word[letter_num] = text[sent_num][letter_num];

				}

				// ��������, ��� ����� �����
				for (size_t num_Word_for_check = 0; num_Word_for_check < cnt_different_Words; num_Word_for_check++)
				{
					if (strcmp((Word_Dict[cnt_different_Words]), New_Word) == 0)
					{
						cnt_different_Words++;
						break;

					}

				}
				for (size_t letter_num = 0; letter_num < Word_Len; letter_num++)
				{
					// �������� ��������� �����
					cnt_Words++;
					//���������� ��������� �� ������ ���������� ����� � ����� ������� �����
					mass_1_start[cnt_Words] = (char*)realloc(mass_1_start, sizeof(char) * (cnt_Words));
					mass_1_start[cnt_Words] = symb;
				}
			}


		}

	}

	printf("\n\n���������� ����� ������, ���������� �� �������� ����������� ����: \n\n");
	for (size_t i = 0; i < (*text_size); i++)
		printf("%s", (text[i]));
	return;

}




//////

int main()
{
	setlocale(LC_ALL, "Rus");
	char sent1[8] = { 'a', 'b', 'c', ' ', 'a', 'b', 'c', '.' };
	char sent2[8] = { 'a', 'b', 'c', ' ', 'a', 'b', 'k', '.' };
	char sent3[8] = { 'a', 'b', 'c', ' ', 'a', 'b', 'm', '.' };
	char* str1 = sent1;
	char* str2 = sent2;
	char* str3 = sent3;

	char** text[3][8] = { &str1, &str2, &str3 };
	size_t text_size = 3;
	func_new((char**)text, &text_size);

	return 0;
}

/////////////
/*

#include <stdio.h>

////

//////////////////
/*
������ ����� ������� ����� - "�������" �� ������� ������ ���� char**
�� ������ ���������� ������, ������ ����������� ����������� �������� '\0'
/////////////////////

��� ��������� �������
������� ������ ���������, �� ����� ������� ������� � ������� (��� ��������������)
--
���� char** ������1 ������ ������ ����, ���-�� ���� ������� ����� ���-�� ����������� � ������
���� char** ������1 ������ ����� ����, ���-�� ���� ������� ����� ���-�� ����������� � ������
--
� ����� ��� �� ��������� �������  ����� ������������� ����� ��� ���������� ����� ����������� ����� � ������ ��� ���������������� �����
//////////////////////////////
���� int ������ �3 ���-�� ��������� � ���������� ����� 0
���� 2 �������, ��������� ������ �����, ��������� 1 ���� � ������ �3

���� int ������� ������������� ������� ����� - �������� ������� �3. ����� ��������� � � ������� �3
������ ����� ����� �������� ��������� ������ �������� (������������ �+1 ��������� ���� int � ������ �3)
--
� ����� �� ������ ��� ������� �� ���� �������� ������� free(mass_1);
/////////////////
*/


/*
void func_new(char** text, size_t* text_size)
{

	for (size_t i = 0; i < (*text_size); i++)
		printf("%s ", *(text[i]));

}




//////

int main()
{
	for (size_t i = 0; i < 3; i++)
		printf("%llu ", i);

	char** text[3][3] = { "abc", "1n3", "���" };
	size_t text_size = 3;
	func_new(text, &text_size);

	return 0;
}
