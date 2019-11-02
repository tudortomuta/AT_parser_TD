#pragma once
#ifndef PARSE_CH_LIBRARY_H
#define PARSE_CH_LIBRARY_H
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_COUNT 1000
#define STR_SIZE 100

typedef struct {
	bool ok; // care returneaza ok sau err
	int line_count; // info pe care ulterior o trimitem la un alt nivel din stiva
	char str[MAX_LINE_COUNT][STR_SIZE + 1]; //+1 pentru terminatorul de sir care il punem noi -> matricea de cuvinte in care salvam informatia extrasa dupa parsare +COPN...
}AT_DATA;

uint8_t parse(char ch); //declararea functiei parse
extern AT_DATA at;
void tudor();

#endif // !PARSE_CH_LIBRARY_H