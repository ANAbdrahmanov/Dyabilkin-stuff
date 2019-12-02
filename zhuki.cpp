#include <iostream>
#include <math.h>

int& minRef(int& a, int& b) {
	return a < b ? a : b;
}


int main() {
	int x, y;
	std::cin >> x >> y;									//�� ������ � ����� ���� ����, ������ ������ ���������������� 2 ����� ���� ��� ��������
	
	int center = x / 2 - 1 + (x & 1);					//������ �������� �� �������� � ��������, ��� � ����������
	bool even = x % 2 == 0;								//��� ������ ��� ��������� ��������
	int currentDepth = 0;								//������� ����
	int exponent = 0;									//������� "������"
	for (int i = 0; i < y; i++) {
		if (currentDepth < pow(2, exponent)) {
			currentDepth++;
		}
		else {
			currentDepth = 1;							//����� ����������
			exponent++;
			x = center;
			center = x / 2 - 1 + (x & 1);
		}
	}
	int firstOutput = center;
	int secondOutput = x - center - 1;
	if (x > 0 && currentDepth == 1 && exponent > 0 && even) {
		minRef(firstOutput, secondOutput)++;
	}

	std::cout << firstOutput << " " << secondOutput << "\n";	//������� �� ����� ��������
	system("pause");
	return 0;
}