#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

void coder(char* argv) {
	uint32_t a = 0, b = 0, c = 0;
	char str[30];
	if (strcmp(argv, "")) strcpy(str, argv);
	else scanf("%s", str);
	b = atof(str);

	for (int8_t i = 0; i < 5; i++) {
		a += (b & 0b111) * (uint32_t)pow(10, i);
		b >>= 3;
	}
		
	for(int8_t i = 4; i >= 0; i--) {
        b = a / (int)pow(10, i) % 10;
        if (b != 0) c = 1;
        if (c) for (int8_t j = 2; j >= 0; j--) {
            if (b & (1 << j)) printf("1");
            else printf("0");
        } 
        if (c && i != 0) printf("_");
    } 
}

void decoder(char* argv) {
	uint32_t a = 0, b, c = 0;
	char str[30];
	if (strcmp(argv, "")) strcpy(str, argv);
	else scanf("%s", str);
	for (uint8_t i = 0; i < strlen(str); i++) {
        b = strlen(str) - 1 - i;
        if (str[b] == '_') {
            c++;
            continue;
        }
		if (str[b] == '1') a += 1 << (i - c);
	}
	
	printf("%d\n", a);
    /*c = 0;
    for (int8_t i = 4; i >= 0; i--) {
        b = (a & (0b111 << i * 3)) >> i * 3;
        if (b != 0) c = 1;
        if (c) printf("%c", 48 + b);
    }*/
}

int main(int argc, char* argv[]) {
	uint8_t k = 4, M, n, d = 1, D, message, status = 1;
	char ch = '\0';
	n = k;
	M = pow(10, n/4);
	D = (1.0 - (log2(M) / log2(pow(2, n)))) * 100.0;
	if (argc > 1) {
		ch = argv[1][0];
	}
	//printf("%d\n%d\n", D, M);
	
	while (status) {
		if (ch == '\0') {
			printf("[C]oding or [D]ecoding? ");
			char str[10];
			scanf("%s", str);
			ch = str[0];
		}
		status = 0;

		switch(ch) {
		case 'c':		
			printf("coder\n");
			if (argc > 2) coder(argv[2]);
			else coder("");
			break;
		case 'd':
			printf("decoder\n");
			if (argc > 2) decoder(argv[2]);
			else decoder("");
			break;
        case 'C':		
			printf("coder\n");
			if (argc > 2) coder(argv[2]);
			else coder("");
			break;
		case 'D':
			printf("decoder\n");
			if (argc > 2) decoder(argv[2]);
			else decoder("");
			break;
		default:
			status = 1;
		}
		if (status) ch = '\0';
	}
}
