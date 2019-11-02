#include <stdio.h>
#include <stdlib.h>
#include "my_parse.h"
#include <inttypes.h>

#define CR 0x0D
#define LF 0x0A

AT_DATA at;
uint8_t parse(char ch)
{
	static bool final;

	static uint8_t state = 0, count_final = 0;
	static uint32_t line_index = 0, string_index = 0;
	switch (state)
	{
		case 0:
		{
			if (ch == CR)
			{
				state = 1;
			}
			else
			{
				state = 0;
				return -1;
			}
			break;
		}
		case 1:
		{
			if (ch == LF)
			{
				state = 2;
			}
			else
			{
				state = 0;
				return 1;
			}
			break;
		}
		case 2:
		{
			if (ch == 'O')
			{
				state = 3;
			}
			else if (ch == 'E')
			{
				state = 7;
			}
			else if (ch == '+')
			{
				state = 14;
			}
			else
			{
				state = 1;
				return 2;
			}
			break;
		}
		case 3:
		{
			if (ch == 'K')
			{
				state = 4;
			}
			else
			{
				state = 2;
				return 3;
			}
			break;
		}
		case 4:
		{
			if (ch == CR)
			{
				state = 5;
			}
			else
			{
				state = 3;
				return 4;
			}
			break;
		}
		case 5:
		{
			if (ch == LF)
			{
				state = 6;
				final = true;
				count_final++;
				printf("Am ajuns la FINAL prin OK\n");
				return 6;
			}
			else
			{
				state = 4;
				return 5;
			}
			break;
		}
		case 6:
		{
			printf("Am ajuns la FINAL prin OK\n");
			return 6;
			break;
		}
		case 7:
		{
			if (ch == 'R')
			{
				state = 8;
			}
			else
			{
				state = 2;
				return 7;
			}
			break;
		}
		case 8:
		{
			if (ch == 'R')
			{
				state = 9;
			}
			else
			{
				state = 7;
				return 8;
			}
			break;
		}
		case 9:
		{
			if (ch == 'O')
			{
				state = 10;
			}
			else
			{
				state = 8;
				return 9;
			}
			break;
		}
		case 10:
		{
			if (ch == 'R')
			{
				state = 11;
			}
			else
			{
				state = 9;
				return 10;
			}
			break;
		}
		case 11:
		{
			if (ch == CR)
			{
				state = 12;
			}
			else
			{
				state = 10;
				return 11;
			}
			break;
		}
		case 12:
		{
			if (ch == LF)
			{
				state = 13;
				final = false;
			}
			else
			{
				state = 11;
				return 12;
			}
			break;
		}
		case 13:
		{
			printf("Am ajuns la FINAL prin ERROR\n");
			return 13;
			break;
		}
		case 14:
		{
			if (ch != CR)
			{
				state = 15;
			}
			else
			{
				state = 2;
				return 14;
			}
			break;
		}
		case 15:
		{
			if (ch != CR)
			{
				at.str[line_index][string_index + 1] = ch; // crestem progresiv in cuvant indicele in care scriem info adica luam pe rand litera cu litera ca sa punem pe aceasi linie la indexi de coloana diferiti
				state = 15;
			}
			else
			{
				at.str[line_index][string_index + 1] = '\0';
				string_index = 0;
				state = 16;
			}
			break;
		}
		case 16:
		{
			if (ch == LF)
			{
				line_index++;
				string_index = 0;
				state = 17;
			}
			else
			{
				state = 15;
				return 16;
			}
			break;
		}
		case 17:
		{
			if (ch == '+')
			{
				state = 14;
			}
			else if(ch == CR)
			{
				state = 18;
			}
			else
			{
				state = 16;
				return 17;
			}
			break;
		}
		case 18:
		{
			if (ch == LF)
			{
				state = 19;
			}
			else
			{
				state = 16;
				return 18;
			}
			break;
		}
		case 19:
		{
			if (ch == 'O')
			{
				state = 3;
			}
			else if (ch == 'E')
			{
				state = 7;
			}
			else
			{
				state = 18;
				return 19;
			}
			break;
		}
		default:
		{
			printf("Invalid STATE !\n");
			state = 0;
			return -2;
			break;
		}
	}
	at.ok = final;
	at.line_count = count_final;
}