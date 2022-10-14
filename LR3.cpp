#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#define A massive[0]
#define B massive[1]
#define C massive[2]
#define D massive[3]

int main() {
	const int Size = 4;
	unsigned char massive[Size], i = 0;
	int num;
	for (i = 0; i < Size; i++)
	{
		std::cout << "massive[" << (int)i << "] = ";
		std::cin >> num;
		massive[i] = num;
	}
	std::cout << "Before changes\n A=" << (int)A << "\n B=" << (int)B << "\n C=" << (int)C << "\n D=" << (int)D << "\n";
	A = (A + (B++) + (C++) + (D++)) * 5;
	B = B % 5;
	C = C + (A++) + (B--);
	D = (B & 15) & ((C & 4) >> 2);
	std::cout << "After changes\n A=" << (int)A << "\n B=" << (int)B << "\n C=" << (int)C << "\n D=" << (int) D << "\n";
	return 0;
}
