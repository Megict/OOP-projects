#include <iostream>
#include <string>

void ULLAsBitString(unsigned long long inp) //������� ���������� � ���� 64-�������� ���������. ������� �������������� (��������� ����������� ��� ��������������� �����, ��� ��� �� ��������)
{
	int i = 0;
	while (inp > 0)
	{
		i++;
		std::cout << inp % 2;
		inp /= 2;
	}
	while (i < 64) //���������� ���� � ����� (���� ����)
	{
		i++;
		printf("0");
	}
}

int CountUnarBitsInULL(unsigned long long a) //�������� ���-�� ��������� ����� � 64-������� ���������
{
	int counter = 0;
	while (a > 0)
	{
		if (a % 2 == 1)
		{
			counter++;
		}

		a /= 2;
	}
	return counter;
}

unsigned long long pw(unsigned long long a, unsigned long long b) //������� ���������� �������� � ������� unsighned long long (����������� pow �� ������� ������ ������� �����) 
{
	unsigned long long res = 1;
	for (int i = 0; i < b; i++)
	{
		res = res * a;
	}
	return res;
}