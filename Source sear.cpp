
/*
2.	������� ��� �����������, ��������� �� ������� ���������� ����.
int doTask2() (���������� ������� �������) ���������� �������:
������� ���������� ������ ����������� List � ��� ������ amount. int i, k � ���������� �������.
int old_amount � ������ ��������� ���������� �����������.
���������� ������ �������:
1. � ������� ����� ����������� ������� ��������������� �� �������.
1.	���� ���������� ����������� �����, ��� ��������� ����������� ���������� �� ����, ���������� ������. ������ amount ����������� �� ����.
2.	���������� ������ ���������� ������ (��� ��� ���������� ���������� �����������).
3.	������� ���������� amount.

*/
int func_for_Task2(char** List, int amount)
{
	int old_amount = amount; for (int i = 0; i < amount; i++)
	{
		if (count_words(List[i]) % 2 == 0)
		{
			{ if (i == amount - 1) amount--;
			else
			{
				for (int k = i; k < amount - 1; k++)
				{
					List[k] = List[k + 1];
				} amount--; i--;
			}
			}
		}
	}
	List = (char**)realloc(List, amount * sizeof(char*)); return amount;
}
