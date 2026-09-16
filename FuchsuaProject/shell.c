#include"v.h"

char cdm_ShellInputString[9][260] = { 0, };	//CDM 1.0.0.first2020
char cdm_FileStringCat[260] = { 0, };
char cdm_FileStringBuffer[260] = { 0, };
char cdm_HyeonjaeDirectoryGyeongro[260] = { 0, };// ".\\*"
char cdm_Directory[2048][260] = { 0, };
char cdm_QwdStar[260] = { 0, };
char Bffr[260] = { 0, };
char __260[260] = { 0, };

wchar_t cdm_Ls[260] = L"";

extern char* cdm_StringPointer;

FILE* cdm_StartMessage;

int cdm_baseDir_Func() {
	FILE* cdm_t_baseDir_cdm = fopen("baseDir.cdm", "r");
	if (cdm_t_baseDir_cdm == NULL) {
		//cdm_t_StartCdm = fopen("text.txt", "w");
		////strcpy(cdm_HyeonjaeDirectoryGyeongro, fgets());
		//fgets(cdm_HyeonjaeDirectoryGyeongro, 260, cdm_t_StartCdm);
		////fclose();
	}
	else {
		//a
		//cdm_t_StartCdm = fopen("text.txt", "w");
		////strcpy(cdm_HyeonjaeDirectoryGyeongro, fgets());
		//fgets(cdm_HyeonjaeDirectoryGyeongro, 260, cdm_t_baseDir_cdm);
		char cdm_t_FileChar = '\0';
		for (int i = 0; i < 260; i++) {
			cdm_t_FileChar = fgetc(cdm_t_baseDir_cdm);
			if (cdm_t_FileChar = '\n') {
				break;
			}
			else {
				cdm_HyeonjaeDirectoryGyeongro[i] = cdm_t_FileChar;
			}
		}
		////fclose();
		fclose(cdm_t_baseDir_cdm);
	}
}

char input[260] = { 0, };
struct shellp {
	void (*funifuni)(char** argp);
	char* optionString;
};

//char* cdm_shelloptiontoken(char* input) {
//	char* token = strtok(input, " ");
//	return token;
//}

char** HwanGyeongByeonSu;
char** cdm_TokeningHGBS(char* input) {
	// ';'를 기점으로 환경변수를 나누고요 다만 '\'를 만나면 무시합니다.
	// ','는 배열입니다. '\'를 만나면 무시합니다.
	// 환경변수 파일 예시
	// "key1=value1;key2=value2;key3=value3"
	char* inpute = malloc(strlen(input) + 1);
	strcpy(inpute, input);
	char** result = NULL;
	char* token = NULL;
	int count = 0;
	int point = 0;
	for (int i = 0; inpute[i] != '\0'; i++) {
		if (inpute[point + i] == '\\') { i++; continue; }
		if (inpute[point + i] == ';') {
			inpute[point + i] = '\0';
			result = realloc(result, sizeof(char*) * (count + 1));
			result[count] = malloc(strlen(inpute + point) + 1);
			strcpy(result[count], inpute + point);
			point += i + 1;
			i = -1;
			count++;
			continue;
		}
	}
	result = realloc(result, sizeof(char*) * (count + 1));
	result[count] = malloc(strlen(inpute + point) + 1);
	strcpy(result[count], inpute + point);
	free(inpute);
	return result;
}

char** cdm_FindHwanGyeongByeonSu(char* input) {
	FILE* HGBS = fopen("HGBS.cdm", "r");
	if (!HGBS) return 0;
	char** a = cdm_TokeningHGBS(input);
	return a;
}

struct shellp shellpList[] = {
	{NULL, "cd"}, // TODO: Implement the 'cd' command functionality
	{NULL, NULL}
};

int cdm_ShellMainCode(char** argp) {
	while (1) {
		fputs("CDM> ", stdout);
		if (fgets(input, sizeof(input), stdin) == NULL) {
			printf("Text is NULL\n");
			continue;
		}
		if (input[0] == '\n') {
			continue;
		}
		strtok(input, "\n"); // Remove the newline character
	}
	return 0;
}