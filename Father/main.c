
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#define _CRT_SECURE_NO_WARNINGS
#define ERR_CODE_NOT_ENOUGH_ARGUMENTS -1
#define ERR_CODE_TOO_MANY_ARGUMENTS -100
#define MAX_SIZE_OF_PATTERN 256

typedef struct parser
{
	char ParsedString[MAX_SIZE_OF_PATTERN];
	int NumOfActions;
	int CurrentIndex;
	int PatternStartIndex;
	int PatternEndIndex;

} parser;

parser *InitParser(char *StringToParse);
void FindPattern(parser *parser);
int GetResultFromSon(parser *parser);
void GetPattern(parser *parser, char *pattern);
char *ConcateStrings(const char *s1, const char *s2);
void ReplacePattern(parser *parser, int SonResult);
void NumToStr(char *TargetString, int SourceNumber);

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

	FILE *FileHandler = fopen("Computation.txt", "w");
	parser *parser = InitParser(argv[1]);

	while (parser->NumOfActions != 0) {
		fputs(ConcateStrings(parser->ParsedString,"\n"), FileHandler);
		FindPattern(parser);
		int SonResult = GetResultFromSon(parser);
		ReplacePattern(parser, SonResult);
		parser->NumOfActions--;
		parser->PatternEndIndex = 0;
		parser->PatternStartIndex = 0;
	};
	fputs(parser->ParsedString, FileHandler);
	fclose(FileHandler);
};
parser *InitParser(char *StringToParse) {
	parser *parser = {StringToParse};
	parser->PatternEndIndex = 0;
	parser->PatternStartIndex = 0;
	parser->CurrentIndex = 0;
	parser->NumOfActions = 0;
	while (*StringToParse != '\0') {
		if (*StringToParse == '(') {
			parser->NumOfActions += 1;
		};
		StringToParse++;
	};
	return parser;
};

void FindPattern(parser *parser) {
	while (parser->ParsedString[parser->CurrentIndex] != '\0') {
		if (parser->ParsedString[parser->CurrentIndex] == '('){
			parser->PatternStartIndex = parser->CurrentIndex + 1;
		}
		else if (parser->ParsedString[parser->CurrentIndex] == ')') {
			parser->PatternEndIndex = parser->CurrentIndex - 1;
			break;
		};
		parser->CurrentIndex++;
	};
	parser->CurrentIndex = 0;
};

int GetResultFromSon(parser *parser) {
	char Pattern[MAX_SIZE_OF_PATTERN];
	char TempStr[MAX_SIZE_OF_PATTERN] = "Son.exe ";
	GetPattern(parser, Pattern);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DWORD* ExitCode = TempStr;

	//init the STARTUPINFO struct
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);

	LPTSTR CommandLine = ConcateStrings(TempStr, Pattern);
	int SonProcessSucceeded = CreateProcess(NULL, CommandLine, NULL, NULL, 0, 0, NULL, NULL, &si, &pi);

	//wait till the proc ends
	WaitForSingleObject(pi.hProcess, INFINITE);

	BOOL GetExitCodeSucceeded = GetExitCodeProcess(pi.hProcess,ExitCode);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	
	int result = *ExitCode;
	return result;
};

void GetPattern(parser *parser, char *pattern) {
	for (int index = parser->PatternStartIndex ; index < parser->PatternEndIndex + 1; index++) {
		*pattern = parser->ParsedString[index];
		pattern++;
	};
	*pattern = '\0';
}

char* ConcateStrings(const char *s1, const char *s2)
{
	char *result = malloc(strlen(s1) + strlen(s2) + 1); 
	strcpy(result, s1);
	strcat(result, s2);
	return result;
};

void ReplacePattern(parser *parser, int SonResult) {
	char SonStringResult[MAX_SIZE_OF_PATTERN];
	NumToStr(SonStringResult, SonResult);

	char *pParsedString = parser->ParsedString;
	char *pSonStringResult = &SonStringResult;

	while (TRUE) {
		if (parser->CurrentIndex < parser->PatternStartIndex - 1) {
			*pParsedString = parser->ParsedString[parser->CurrentIndex];
			parser->CurrentIndex++;
			pParsedString++;
		}
		else {
			while (*pSonStringResult != '\0') {
				*pParsedString = *pSonStringResult;
				pParsedString++;
				pSonStringResult++;
			};
			break;
		};
	};

	parser->CurrentIndex = parser->PatternEndIndex + 2;
	while (parser->ParsedString[parser->CurrentIndex] != '\0') {
		*pParsedString = parser->ParsedString[parser->CurrentIndex];
		parser->CurrentIndex++;
		pParsedString++;
	};
	*pParsedString = '\0';
	parser->CurrentIndex = 0;

};

void NumToStr(char *TargetString, int SourceNumber) {
	char TempString[MAX_SIZE_OF_PATTERN];
	int StringIndex = -1;
	while (SourceNumber != 0) {
		StringIndex++;
		switch (SourceNumber % 10) {
		case 0:
			TempString[StringIndex] = '0';
			break;
		case 1:
			TempString[StringIndex] = '1';
			break;
		case 2:
			TempString[StringIndex] = '2';
			break;
		case 3:
			TempString[StringIndex] = '3';
			break;
		case 4:
			TempString[StringIndex] = '4';
			break;
		case 5:
			TempString[StringIndex] = '5';
			break;
		case 6:
			TempString[StringIndex] = '6';
			break;
		case 7:
			TempString[StringIndex] = '7';
			break;
		case 8:
			TempString[StringIndex] = '8';
			break;
		case 9:
			TempString[StringIndex] = '9';
			break;
		};
		SourceNumber = SourceNumber / 10;
	};
	while (StringIndex >= 0) {
		*TargetString = TempString[StringIndex];
		TargetString++;
		StringIndex--;
	};
	*TargetString = '\0';
};