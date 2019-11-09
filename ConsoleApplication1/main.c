
#include <stdlib.h>
#include <stdio.h>

#define ERR_CODE_NOT_ENOUGH_ARGUMENTS -1
#define ERR_CODE_TOO_MANY_ARGUMENTS -100

int main(int argc, char *argv[]) {
	//checking input parameters:
	//only one parameter is allowed
	if (argc < 2)
	{
		return ERR_CODE_NOT_ENOUGH_ARGUMENTS;
	};
	if (argc > 2)
	{
		return ERR_CODE_TOO_MANY_ARGUMENTS;
	};

	char *InputString = argv[1];
	int result;
	for (int i = 0; i < strlen(InputString); i++) {
		if (InputString[i] == '+' || InputString[i] == '*'){
			result = Calculate(InputString, i);
		}
	};
	exit(result);
};

int Calculate(char *InputString, int IndexOfOperand) {
	int EndOfSecondNum;
	int first_num = GetNumFromString(InputString, IndexOfOperand);
	for (int i = IndexOfOperand; i < strlen(InputString)+1; i++) {
		if (InputString[i] == '\0') {
			EndOfSecondNum = i;
			break;
		}
	}
	int second_num = GetNumFromString(InputString + IndexOfOperand, EndOfSecondNum-IndexOfOperand);
	if (InputString[IndexOfOperand] == '*') {
		return first_num * second_num;
	}
	else {
		return first_num + second_num;
	};
}

int GetNumFromString(char *InputString, int EndOfNum) {
	int numeric_result = 0;
	int char_index = 0;
	while (char_index < EndOfNum) {
		numeric_result = numeric_result * 10;
		char_index++;
		switch (*InputString) {
		case '0':
			break;
		case '1':
			numeric_result += 1;
			break;
		case '2':
			numeric_result += 2;
			break;
		case '3':
			numeric_result += 3;
			break;
		case '4':
			numeric_result += 4;
			break;
		case '5':
			numeric_result += 5;
			break;
		case '6':
			numeric_result += 6;
			break;
		case '7':
			numeric_result += 7;
			break;
		case '8':
			numeric_result += 8;
			break;
		case '9':
			numeric_result += 9;
			break;
		};
		InputString++;
	};
	return numeric_result;
}