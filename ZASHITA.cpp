#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>

//////////////////
/*
первым делом заводим текст - "нулевой" по порядку массив типа char**
он хранит предложени текста, каждое предложение завершается символом '\0'
/////////////////////

два двумерных массива
--
типа char** массив№1 хранит НАЧАЛА слов, кол-во элем массива равно кол-ву предложений в тексте
типа char** массив№1 хранит КОНЦЫ слов, кол-во элем массива равно кол-ву предложений в тексте
--
будем рассматривать слова как расстояние между указателями конца и начала для соответствующего слова
//////////////////////////////
типа int массив №3 кол-во элементов Х изначально равно 0
имея 2 массива, вычленяем каждое слово, добавляем 1 элем в массив №3

типа int счтчики встречаемости каждого слова - элементы массива №3. Таких элементов Х в массиве №3
каждое новое слово означает заведение нового счетчика (реаллоцируем Х+1 элементов типа int в массив №3)
--
в конце не забыть для каждого из трех массивов сделать free(mass_1);
/////////////////

for(){

}

*/



void func_new(char** text, size_t* text_size)
{
	printf(" \nЗапущена func_new, очистка текста от наиболее встречаемых слов: :\n\n");
	
	/*

	два двумерных массива
	--
	типа char** массив№1 хранит НАЧАЛА слов, кол-во элем массива равно кол-ву предложений в тексте
	типа char** массив№2 хранит КОНЦЫ слов, кол-во элем массива равно кол-ву предложений в тексте
	будем рассматривать слова как расстояние между указателями конца и начала для соответствующего слова
	*/


	for (size_t sent_num = 0; sent_num < (*text_size); sent_num++) {
		size_t cnt_Words = 0;
		char** mass_1_start, ** mass_2_finish;
		int isWord = 0;
		for (char* symb = text[sent_num]; *symb != '\0'; symb++) {

			
			//1 isWord == 0 при этом встречен НЕразделительный символ
			//2 isWord == 1 при этом встречен НЕразделительный символ
			//3 isWord == 0 при этом встречен разделительный символ
			//4 isWord == 1 при этом встречен разделительный символ
			

			// индикатор разделителя
			int is_symb_separator = (int)((*symb == ' ') || (*symb == ',') || (*symb == '.'));
			// is_symb_separator == 0, значит, встречена буква/цифра

			//1 случ
			if (isWord == 0 && is_symb_separator == 0) {
				// началось очередное слово
				cnt_Words++;
				//добавление указателя на начало очередного слова в конец массива начал
				mass_1_start[cnt_Words] = (char*)realloc(mass_1_start, sizeof(char) * (cnt_Words));
				mass_1_start[cnt_Words] = symb;
				continue;
			}
			//2 случ
			else if (isWord == 1 && is_symb_separator == 0) {
				continue;
			}

			//3 случ
			else if (isWord == 0 && is_symb_separator == 1) {
				continue;
			}

			//4 случ
			else if (isWord == 1 && is_symb_separator == 1) {
				// кончилось очередное слово
				//добавление указателя на начало очередного слова в конец массива концов
				mass_2_finish[cnt_Words] = (char*)realloc(mass_1_start, sizeof(char) * (cnt_Words));
				mass_2_finish[cnt_Words] = symb;
				continue;
			}

			// имеем массив начал и массив концов заполненными
			// считаем встречаемость каждого слова

			size_t number_of_the_Word = 0;
			size_t Word_Len = 0;
			char** Word_Dict = (char**)malloc(sizeof(char*) * 1);
			size_t cnt_different_Words = 0;


			for (number_of_the_Word = 0; number_of_the_Word < cnt_Words; number_of_the_Word++)
			{
				// имеем слова как расстояние между указателями конца и начала для соответствующего слова
				Word_Len = mass_1_start[number_of_the_Word] - mass_2_finish[number_of_the_Word];

				char* New_Word = (char*)malloc(sizeof(char) * 1);

				for (size_t letter_num = 0; letter_num < Word_Len; letter_num++)
				{
					New_Word = (char*)realloc(New_Word, sizeof(char) * (letter_num+1));
					New_Word[letter_num] = text[sent_num][letter_num];

				}

				// проверка, что слово новое
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
					// началось очередное слово
					cnt_Words++;
					//добавление указателя на начало очередного слова в конец массива начал
					mass_1_start[cnt_Words] = (char*)realloc(mass_1_start, sizeof(char) * (cnt_Words));
					mass_1_start[cnt_Words] = symb;
				}
			}


		}

	}

	printf("\n\nНачинается вывод текста, очищенного от наиболее встречаемых слов: \n\n");
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
первым делом заводим текст - "нулевой" по порядку массив типа char**
он хранит предложени текста, каждое предложение завершается символом '\0'
/////////////////////

два двумерных массива
заводим массив четвертый, он будет хранить пробелы и запятые (как разделительные)
--
типа char** массив№1 хранит НАЧАЛА слов, кол-во элем массива равно кол-ву предложений в тексте
типа char** массив№1 хранит КОНЦЫ слов, кол-во элем массива равно кол-ву предложений в тексте
--
в цкиле фор по основному массиву  будем рассматривать слова как расстояние между указателями конца и начала для соответствующего слова
//////////////////////////////
типа int массив №3 кол-во элементов Х изначально равно 0
имея 2 массива, вычленяем каждое слово, добавляем 1 элем в массив №3

типа int счтчики встречаемости каждого слова - элементы массива №3. Таких элементов Х в массиве №3
каждое новое слово означает заведение нового счетчика (реаллоцируем Х+1 элементов типа int в массив №3)
--
в конце не забыть для каждого из трех массивов сделать free(mass_1);
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

	char** text[3][3] = { "abc", "1n3", "юдж" };
	size_t text_size = 3;
	func_new(text, &text_size);

	return 0;
}
