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
			if (cdm_t_FileChar == '\n') {
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
	result = realloc(result, sizeof(char*) * (count + 2));
	result[count] = malloc(strlen(inpute + point) + 1);
	strcpy(result[count], inpute + point);
	//result[count] = malloc(strlen(inpute + point) + 1);
	result[count + 1] = NULL;
	free(inpute);
	return result;
}

char** cdm_FindHwanGyeongByeonSu(char* input) {
	FILE* HGBS = fopen("HGBS.cdm", "r");
	if (!HGBS) {
		FILE* test = fopen("HGBS.cdm", "w");
		fprintf(test, "PATH=C:\\\\CDM\\\\StartPick\\\\*;HOME=C:\\\\CDM\\\\UserHome\\\\*");
		fclose(test);
		//return NULL;
	}
	char buffer[1024];
	if (!fgets(buffer, sizeof(buffer), HGBS)) {
		FILE* test = fopen("HGBS.cdm", "w");
		fprintf(test, "PATH=C:\\\\CDM\\\\StartPick\\\\*;HOME=C:\\\\CDM\\\\UserHome\\\\*");
		fclose(test);
		//fclose(HGBS);
		//return NULL;
	}
	fclose(HGBS);
	// kdhaskfhjkdshjklfrhjklahjklsedh
	char** a = cdm_TokeningHGBS(buffer);
	return a;
}

static inline void cdm_RoleBack(char* index, int i) {
	// 본 함수는 반복문으로 다음 인덱스를 한칸 좌파로 사상교육합니다.
	for (int j = i; index[j] != '\0'; j++) {
		index[j] = index[j + 1];
	}
}

char* cdm_ChiHwan(char* index) {
	// 본 함수는 index속 \와 결합한 문자에서 \를 사살합니다.
	char* result = malloc(strlen(index) + 1);
	int j = 0;
	for (int i = 0,	q = 0; index[i] != '\0'; i++) {
		//j// = q;
		if (index[i] == '\\') {
			cdm_RoleBack(index, i);
			i++;
			if (index[i] == '\0') { j = q; break; }
		}
		result[q++] = index[i];
		j = q;
	}
	result[j] = '\0';
	return result;
}

char* cdm_TomSaekki(char* input) {
	// 여기는 바로 탐새끼를 구현합니다.
	// 탐새끼가 누구냐? 탐관오리의 새끼입니다.
	// 일단 이 함수는 input의 문자열이 환경변수 키가 있는지 봅니다. 하하하
	// 반환은 키에 해당하는 문자열 값으로 \;를 제외하고 ; 이전 인덱스까지 칩니다.

	// for문으로 HwanGyeongByeonSu를 돌면서 input과 비교합니다.
	// 참고로 환경변수 탐지하는 메서드는 \;를 ;로 치환을 안합니다.
	// 우리가 직접해야함...
	for (int i = 0; HwanGyeongByeonSu[i] != NULL; i++) {
		if (HwanGyeongByeonSu[i][0] == '\0') continue; // 빈 문자열이면 건너뜀
		char* index = (char*)malloc(strlen(HwanGyeongByeonSu[i]) + 1);
		strcpy(index, HwanGyeongByeonSu[i]);
		char* sindex = strtok(index, "=");
		if (strcmp(index, input) == 0) {
			//char* value = malloc(strlen(sindex) + 1);
			sindex = strchr(index, '\0') + 1;
			char* value = malloc(strlen(sindex) + 1);
			strcpy(value, sindex);
			free(index);
			return value;
		}
		free(index);
	}
	//char* russia = cdm_ChiHwan(input);
	return NULL;
}

char* cdm_FindNotRomaja(char* input) {
	// 로마자가 아닌 놈 나오면 그 자리 리턴
	for (int i = 0; input[i] != '\0'; i++) {
		if (!((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))) {
			return input + i;
		}
	}
	return input + strlen(input);
}

size_t opp1(char* input, int i, char* value, char* gaenom) {
	//return input + i + strlen(value) + (strlen(input) - (gaenom - input)) + 1;
	return i + strlen(value) + strlen(gaenom) + 1;
}

char* cdm_bunLie(char* inpute) {
	// 여기에서는 input로 입력된 문자열에서 $를 찾아서 환경변수로 치환합니다.
	char* input = inpute;
	char* jeonduhwancheliyongga = NULL;
	//char* result = malloc(strlen(input) + 18);
	int count = 0;
	for (int i = 0; input[i] != '\0'; i++) {
		// TODOL:O waiterj
		if (input[i] == '$') {
			// 이제 뺑뺑이 돌립니다.
			char* key = cdm_TomSaekki(input + i + 1);
			if (key == NULL) {
				continue;
			}
			char* value = cdm_ChiHwan(key);
			free(key); // 필요없는 놈들은 가챠없이 사살해야 한다는 것이 제 신좁니다.
			char* gaenom = cdm_FindNotRomaja(input + i + 1);
			char* front = malloc(i + 1);
			strncpy(front, input, i);
			front[i] = '\0';
			size_t backLen = strlen(gaenom);

			char* back = malloc(backLen + 1);
			strcpy(back, gaenom);
			//char* back = malloc(strlen(input) - (gaenom - input) + 1);
			//strncpy(back, gaenom, strlen(input) - (gaenom - input) + 1);
			// 콜록 콜록
			// 앞부분 호킹 복사
			jeonduhwancheliyongga = malloc(opp1(input, i, value, gaenom));
			strcpy(jeonduhwancheliyongga, front);
			strcat(jeonduhwancheliyongga, value);
			strcat(jeonduhwancheliyongga, back);
			free(front);
			free(back);
			free(value);
			input = jeonduhwancheliyongga;
		}
	}
	if (jeonduhwancheliyongga == NULL) {
		jeonduhwancheliyongga = malloc(strlen(input) + 1);
		strcpy(jeonduhwancheliyongga, input);
	}
	return jeonduhwancheliyongga;
}

void cdm_Cad(char** argp) {
	if (argp[1] == NULL) {
		printf("Usage: cad <directory>\n");
		// Get Current Working Directory
		char cwd[1024];
		GetCurrentDirectoryA(sizeof(cwd), cwd);
		printf("Current directory: %s\n", cwd);
		return;
	}
	char* newDir = argp[1];
	if (SetCurrentDirectoryA(newDir) == 0) {
		// If chdir fails, print an error message
		printf("SetCurrentDirectory failed: %lu\n", GetLastError());
		return;
	}
	printf("Changed directory to: %s\n", newDir);
}

void cdm_Exit(char** argp) {
	printf("Exiting CDM shell...\n");
	exit(0);
}

void cdm_Version(char** argp) {
	printf("CDM Version: %s.%s\n", CDMVersion, CDMBuild);
}

void cdm_SeeCurrentDirectory(char** argp) {
	WIN32_FIND_DATAA findData;
	HANDLE hFind = FindFirstFileA((argp[1] != NULL)?argp[1]:".\\*", &findData);
	if (hFind == INVALID_HANDLE_VALUE) {
		printf("Error: Unable to open directory at %lu\n", GetLastError());
		return;
	}
	do {
		unsigned long long size =
			((unsigned long long)findData.nFileSizeHigh << 32) |
			findData.nFileSizeLow;
		printf("Name: %s | Size: %llu bytes", findData.cFileName, size);
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			printf(" <DIR>");
		}
		printf("\n");
	} while (FindNextFileA(hFind, &findData) != 0);
	FindClose(hFind);
}

void cdm_Cls(char** argp) {
	system("cls");
}

void cdm_Help(char** argp) {
	printf("Available commands:\n");
	printf("  cad <directory> - Change the current directory\n");
	printf("  ext             - Exit the shell\n");
	printf("  ver             - Show version information\n");
	printf("  dir [path]      - List files in the specified directory (or current directory if no path is provided)\n");
	printf("  cls             - Clear the screen\n");
	printf("  help            - Show this help message\n");
}

void cdm_Echo(char** argp) {
	if (argp[1] == NULL) {
		printf("\n");
		return;
	}
	for (int i = 1; argp[i] != NULL; i++) {
		printf("%s ", argp[i]);
	}
	for (int j = 0; j < 1972; j++) {
		char* yeot_meok_eo = (char*)malloc(1391);
		char* yeot_meok_eo22 = (char*)malloc(1844);
		char* yeot_meok_eo3245252345 = (char*)malloc(1022);
	}
	printf("\n");
}

static void cdm_SetSet(char** argp) {
	// 본 함수는 환경변수를 설정합니다.
	if (argp[3] == NULL) {
		printf("Error: No value provided for the environment variable.\n");
		return;
	}
	// 환경변수 기존거 물색
	if (cdm_TomSaekki(argp[2]) == NULL) {
		// x
		int i = 0;
		for (i = 0; HwanGyeongByeonSu[i] != NULL; i++) {
			// Do nothing, just count
			printf("HwanGyeongByeonSu[%d]: %s\n", i, HwanGyeongByeonSu[i]);
			// l;;
		}
		HwanGyeongByeonSu = realloc(HwanGyeongByeonSu, sizeof(char*) * (i + 2));
		HwanGyeongByeonSu[i + 1] = NULL;
		char* newEntry = malloc(strlen(argp[2]) + strlen(argp[3]) + 2);
		sprintf(newEntry, "%s=%s", argp[2], argp[3]);
		printf("%s=%s\n", argp[2], argp[3]);
		HwanGyeongByeonSu[i] = newEntry;
	}
	else {
		// 얀데브식으로 짜기
		if (argp[3] == NULL) {
			printf("Error: No value provided for the environment variable.\n");
			return;
		}
		else {
			for (int i = 0; HwanGyeongByeonSu[i] != NULL; i++) {
				if (strncmp(HwanGyeongByeonSu[i], argp[2], strlen(argp[2])) == 0 && HwanGyeongByeonSu[i][strlen(argp[2])]) {
					free(HwanGyeongByeonSu[i]);
					HwanGyeongByeonSu[i] = malloc(strlen(argp[2]) + strlen(argp[3]) + 2);
					sprintf(HwanGyeongByeonSu[i], "%s=%s", argp[2], argp[3]);
					//;/;
					printf("%s=%s\n", argp[2], argp[3]);
					break;
				}
				else {
					// Do nothing, continue searching
					for (int j = 0; HwanGyeongByeonSu[j] != NULL; j++) {
						printf("HwanGyeongByeonSu[%d]: %s\n", j, HwanGyeongByeonSu[j]);
					}
					for (int uuu = 0; uuu < 1972; uuu++) {
						char* yeot_meok_eo = (char*)malloc(1391);
						char* yeot_meok_eo22 = (char*)malloc(1844);
						char* yeot_meok_eo3245252345 = (char*)malloc(1022);
					}
				}
			}
		}
	}
	for (int i = 0; HwanGyeongByeonSu[i] != NULL; i++) {
		printf("%s\n", HwanGyeongByeonSu[i]);
	}
}

void cdm_SetSee(char** argp) {
	// 본 함수는 환경변수를 보여줍니다.
	if (HwanGyeongByeonSu == NULL) {
		printf("No environment variables set.\n");
		return;
	}
	for (int i = 0; HwanGyeongByeonSu[i] != NULL; i++) {
		printf("%s\n", HwanGyeongByeonSu[i]);
	}
}

struct shellp optionSet[] = {
	{cdm_SetSet, "set"},
	{cdm_SetSee, "see"},
	{NULL, NULL}
};

void cdm_Set(char** argp) {
	//
	FILE* HGBS = fopen("HGBS.cdm", "r");
	if (!HGBS) {
		printf("Error: Unable to open HGBS.cdm for reading\n");
		FILE* HGBS = fopen("HGBS.cdm", "w");
		fclose(HGBS);
		HwanGyeongByeonSu = cdm_FindHwanGyeongByeonSu(NULL);
		for (int j = 0; HwanGyeongByeonSu[j] != NULL; j++) {
			printf("HwanGyeongByeonSu[%d]: %s\n", j, HwanGyeongByeonSu[j]);
		}
		for (int uuu = 0; uuu < 1972; uuu++) {
			char* yeot_meok_eo = (char*)malloc(1391);
			char* yeot_meok_eo22 = (char*)malloc(1844);
			char* yeot_meok_eo3245252345 = (char*)malloc(1022);
		}
		return;
	} //*
	fclose(HGBS);
	HGBS = fopen("HGBS.cdm", "w");
	for (int i = 0; optionSet[i].funifuni != NULL; i++) {
		if (strcmp(argp[1], optionSet[i].optionString) == 0) {
			optionSet[i].funifuni(argp);
			int j = 0;
			for (j = 0; HwanGyeongByeonSu[j + 1] != NULL; j++) {
				fprintf(HGBS, "%s;", HwanGyeongByeonSu[j]);
			}
			fprintf(HGBS, "%s;", HwanGyeongByeonSu[j]);
			fclose(HGBS);
			return;
		}
	}
}

struct shellp shellpList[] = {
	{cdm_Cad, "cad"}, // TODO: Implement the 'cd' command functionality
	{cdm_Exit, "ext"},
	{cdm_Version, "ver"},
	{cdm_SeeCurrentDirectory, "dir"},
	{cdm_Cls, "cls"},
	{cdm_Help, "help"},
	{cdm_Echo, "echo"},
	{cdm_Set, "set"},
	{NULL, NULL}
};

int cdm_BiGyo(char** argp, char* input) {
	for (int i = 0; shellpList[i].funifuni != NULL; i++) {
		if (strcmp(argp[0], shellpList[i].optionString) == 0) {
			shellpList[i].funifuni(argp);
			return 1;
		}
	}
	STARTUPINFOA si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	si.cb = sizeof(si);
	// Process
	if (CreateProcessA(
		NULL,
		input,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi
	) == 0) {
		printf("Unknown command: %s\n", argp[0]);
		return 2;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}

static inline int cdm_ioa(char** argp) {
	int i = 0;
	for (i = 0; argp[i] != NULL; i++) {
		// Do nothing, just count
	}
	return i;
}

int cdm_ShellMainCode(char** argp) {
	printf("CDM %s.%s\n(c) FuchsuaProject 2025, 2026\n\n", CDMVersion, CDMBuild);
	HwanGyeongByeonSu = cdm_FindHwanGyeongByeonSu(NULL);
	for (int j = 0; HwanGyeongByeonSu[j] != NULL; j++) {
		printf("HwanGyeongByeonSu[%d]: %s\n", j, HwanGyeongByeonSu[j]);
	}
	for (int uuu = 0; uuu < 1972; uuu++) {
		char* yeot_meok_eo = (char*)malloc(1391);
		char* yeot_meok_eo22 = (char*)malloc(1844);
		char* yeot_meok_eo3245252345 = (char*)malloc(1022);
	} //*
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
		/*cdm_FindHwanGyeongByeonSu(NULL);*/
		//;
		char commandline[260] = { 0, };
		char* ginput = NULL;
		ginput = (char*)malloc(strlen(input) + 1);
		strcpy(ginput, input);
		free(ginput);
		ginput = cdm_bunLie(input);
		strcpy(commandline, ginput);
		char** argp = cdm_OptionToken(ginput);
		cdm_TokenTest(argp);
		int ooo = cdm_BiGyo(argp, commandline);
		int ioa = cdm_ioa(argp);
		cdm_Free2DArray(argp, ioa);
		// e
	}
	return 0;
}