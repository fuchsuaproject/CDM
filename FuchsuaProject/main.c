#include"v.h"

char cdm_OpsionInput[9][260] = { 0, };
char* cdm_StringPointer;
int main_Start = 0;

extern char cdm_HyeonjaeDirectoryGyeongro[260];

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

int main(int argc, char* argv[9]) {
	//
	//FILE* cdm_t_StartCdm = fopen("text.txt", "r");
	//if (cdm_t_StartCdm == NULL) {
	//	//cdm_t_StartCdm = fopen("text.txt", "w");
	//	////strcpy(cdm_HyeonjaeDirectoryGyeongro, fgets());
	//	//fgets(cdm_HyeonjaeDirectoryGyeongro, 260, cdm_t_StartCdm);
	//	////fclose();
	//}
	//else {
	//	//a
	//	//cdm_t_StartCdm = fopen("text.txt", "w");
	//	////strcpy(cdm_HyeonjaeDirectoryGyeongro, fgets());
	//	fgets(cdm_HyeonjaeDirectoryGyeongro, 260, cdm_t_StartCdm);
	//	////fclose();
	//	fclose(cdm_t_StartCdm);
	//}
	//cdm_baseDir_Func();
	//fclose("");
	//
	if (argc == 1) {
	re:
		cdm_baseDir_Func();
		strcpy(cdm_OpsionInput[1], "NULLL");
		//getchar();
		if (main_Start != 0) {
			getchar();
		}
		scanf("%[^\n]", cdm_OpsionInput[1]);
		//cdm_StringPointer = strtok(cdm_OpsionInput[1], " ");
		if (strcmp(cdm_OpsionInput[1], "nowin") == 0) {
			cdm_ShellMainCode(1);
			++main_Start;
		}
		else if (strcmp(cdm_OpsionInput[1], "NULLL") == 0) {
			cdm_ShellMainCode(0);
			++main_Start;
		}
		else if (strcmp(cdm_OpsionInput[1], "setup") == 0) {
			cdm_Setup();
		}
		else if (strcmp(cdm_OpsionInput[1], "test") == 0) {
			printf("%%cd%%");
			++main_Start;
		}
		else if (strcmp(cdm_OpsionInput[1], "exit") == 0) {
			goto exitA;
		}
		goto re;
	}
	exitA:
	return 0;
}