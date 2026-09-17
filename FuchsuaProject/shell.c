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
	result = realloc(result, sizeof(char*) * (count + 1));
	result[count] = malloc(strlen(inpute + point) + 1);
	strcpy(result[count], inpute + point);
	free(inpute);
	return result;
}

char** cdm_FindHwanGyeongByeonSu(char* input) {
	FILE* HGBS = fopen("HGBS.cdm", "r");
	if (!HGBS) return 0;
	char buffer[1024];
	if (!fgets(buffer, sizeof(buffer), HGBS)) {
		fclose(HGBS);
		return NULL;
	}
	fclose(HGBS);
	// kdhaskfhjkdshjklfrhjklahjklsedh
	char** a = cdm_TokeningHGBS(buffer);
	return a;
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

struct shellp shellpList[] = {
	{cdm_Cad, "cad"}, // TODO: Implement the 'cd' command functionality
	{cdm_Exit, "ext"},
	{cdm_Version, "ver"},
	{cdm_SeeCurrentDirectory, "dir"},
	{cdm_Cls, "cls"},
	{cdm_Help, "help"},
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
		HwanGyeongByeonSu = cdm_FindHwanGyeongByeonSu(NULL);
		char commandline[260] = { 0, };
		strcpy(commandline, input);
		char** argp = cdm_OptionToken(input);
		//cdm_TokenTest(argp);
		int ooo = cdm_BiGyo(argp, commandline);
		int ioa = cdm_ioa(argp);
		cdm_Free2DArray(argp, ioa);
		// e
	}
	return 0;
}