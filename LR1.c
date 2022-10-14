#include <stdio.h>  
#include <stdint.h> 
#include <string.h> 
#include <math.h>   

// 5-3-2-1
//таблица соответствия 2-10 системах
uint8_t table[10] = { 
0b0000, // 0 
0b0001, // 1
0b0010, // 2
0b0100, // 3 
0b0101, // 4
0b1000, // 5
0b1001, // 6 
0b1010, // 7
0b1100, // 8
0b1101  // 9
}; 
void coder(char* argv);
void decoder(char* argv);

int main(int argc, char* argv[]) {
	uint8_t k = 4, M, n, d = 1, D, status = 1;
	char ch = '\0';
	n = k;
	M = pow(10, n/4);
	D = (1.0 - (log2(M) / log2(M))) * 100.0;
	printf("D = %d%% M = %d\nn = %d d = %d\n", D, M, n, d); // вывод параметров
	if (argc > 1) {
		ch = argv[1][0];
	}
	
	while (status) {
		if (ch == '\0') {
			printf("[C]oding or [D]ecoding? ");
			char str[10];
			scanf("%s", str);
			ch = str[0];
		}
		status = 0;

		switch(ch) {
		case 'C':				
			if (argc > 2) coder(argv[2]);
			else coder("");
			break;
		case 'D':
			if (argc > 2) decoder(argv[2]);
			else decoder("");
			break;
		default:
			status = 1;
		}
		if (status) ch = '\0';
	}
}

void coder(char* argv) {
	uint8_t a;
	char str[30];
	if (strcmp(argv, "")) strcpy(str, argv);
	else scanf("%s", str);
	a = atof(str);
	if (a > 9) printf("N/A");
	else {
		for(int8_t i = 3; i >= 0; i--) 
			if (table[a] & (1 << i)) printf("1");
			else printf("0");
	}
}

void decoder(char* argv) {
	uint8_t a = 0, b, c = 0;
	char str[30];
	if (strcmp(argv, "")) strcpy(str, argv);
	else scanf("%s", str);
	for (uint8_t i = 0; i < strlen(str); i++) {
		b = strlen(str) - 1 - i;
		if (str[b] == '1') a += 1 << i;
		if (str[b] != '1' && str[b] !='0') c++;
	}
	b = 1;
	
	for (uint8_t i = 0; i < 10; i++)
		if (table[i] == a && c == 0) {
			printf("%d\n", i);
			b = 0;
		}
	if (b) printf("N/A\n");
}
