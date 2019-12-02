#include <iostream>
#include <math.h>

int& minRef(int& a, int& b) {
	return a < b ? a : b;
}


int main() {
	int x, y;
	std::cin >> x >> y;									//не уверен в каком виде ввод, сделал просто последовательные 2 числа себе для удобства
	
	int center = x / 2 - 1 + (x & 1);					//вместо проверки на четность с условием, все в вычислении
	bool even = x % 2 == 0;								//это только для финальной проверки
	int currentDepth = 0;								//глубина шага
	int exponent = 0;									//глубина "дерева"
	for (int i = 0; i < y; i++) {
		if (currentDepth < pow(2, exponent)) {
			currentDepth++;
		}
		else {
			currentDepth = 1;							//сразу закидываем
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

	std::cout << firstOutput << " " << secondOutput << "\n";	//порядок не имеет значения
	system("pause");
	return 0;
}