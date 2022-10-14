#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// Преобразует число number в строку в двочном виде
void btostr(uint16_t number, char* str) {
    for (uint8_t i = 0; i < 16; i++) {
        if (number & (1 << 15)) str[i] = '1';
        else str[i] = '0';
        number <<= 1;
    }
    str[16] = '\0';
}

// Преобразует строку str в число
uint16_t strtob(char* str) {
    uint16_t result = 0;
    for (uint8_t i = 0; str[i] != '\0'; i++) {
        result <<= 1;
        if (str[i] == '1') result |= 1;
    }
    return result;
}

uint16_t coder(uint16_t message) {
    uint16_t temp, temp2, result = 0;
    uint16_t k[4] = {
        0b0101010101010101,
        0b0110011001100110,
        0b0111100001111000,
        0b0111111110000000
    };

    // Вставляем биты message в свои разряды для закодированного сообщения
    for (uint8_t i = 0; i < 11; i++) {
        if (message & (1 << i)) {
            if (i == 0) temp = 2;
            else if (i > 0 && i < 4) temp = i + 3;
            else if (i > 3 && i < 11) temp = i + 4;
        }
        result |= 1 << temp;
    }
    
    for (uint8_t i = 0; i < 4; i++) {
        temp = result & k[i]; temp2 = 0;
        for(; temp; temp2++) temp &= temp - 1; // Подсчет количества единиц
        temp2 %= 2;
        if (!temp2) continue;
        if (i == 0 || i == 1) result |= 1 << i;
        else if (i == 2) result |= 1 << 3;
        else if (i == 3) result |= 1 << 7;
    }

    temp = result; temp2 = 0;
    for(; temp; temp2++) temp &= temp - 1;
    if (temp2 % 2) result |= 1 << 15;

    return result;
} 

uint16_t decoder(uint16_t message) {
    uint16_t temp, temp2, sindrom = 0, result = 0;
    uint16_t k[4] = {
        0b0101010101010101,
        0b0110011001100110,
        0b0111100001111000,
        0b0111111110000000
    };
    
    // Находим синдром
    for (uint8_t i = 0; i < 4; i++) {
        temp = message & k[i]; temp2 = 0;
        for(; temp; temp2++) temp &= temp - 1; // Подсчет количества единиц
        temp2 %= 2;
        if (!temp2) continue;
        sindrom |= 1 << i;
    }

    // Проверяем бит четности
    temp = message; temp2 = 0;
    for(; temp; temp2++) temp &= temp - 1;
    
    if ((temp2 % 2) && sindrom > 0) message ^= 1 << (sindrom - 1);
    else if ((temp % 2) == 0 && sindrom > 0) return 0xFFFF;

    // Читаем биты message в свои разряды для декодированного сообщения
    for (uint8_t i = 0; i < 16; i++) {
        if (message & (1 << i)) {
            if (i == 2) result |= 1;
            else if (i > 3 && i < 7) result |= 1 << (i - 3);
            else if (i > 7 && i < 15) result |= 1 << (i - 4);
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    char str[17];
    uint16_t message = 0xFFFF, result;
    char ch = 0;

    if (argc > 1) {
        if (argv[1][0] == 'c' || argv[1][0] == 'C') ch = 'c';
        else if (argv[1][0] == 'd' || argv[1][0] == 'D') ch = 'd';
        if (argc > 2) {
            if (ch == 'c') message = atof(argv[2]);
            else if (ch == 'd') message = strtob(argv[2]);
        }
    }

    if (!ch) {
        while (ch != 'c' && ch != 'C' && ch != 'd' && ch != 'D')
        {
            printf("[C]oding or [D]ecoding? ");
            scanf("%s", str);
            if (strlen(str)) ch = str[0];
            if (ch == 'C') ch = 'c';
            else if (ch == 'D') ch = 'd';
        }
    }

    if (message == 0xFFFF) {
        printf("Which message you want to ");
        if (ch == 'c') {
            printf("code? ");
            scanf("%s", str);
            message = atof(str);
        }
        else if (ch == 'd') {
            printf("decode? ");
            scanf("%s", str);
            message = strtob(str);
        }
    }

    if (ch == 'c') {
        btostr(coder(message), str);
        printf("%s\n", str);
    } else if (ch == 'd') {
        result = decoder(message);
        if (result != 0xFFFF)
            printf("%d\n", result);
        else 
            printf("Error\n");
    }

    return 0;
}