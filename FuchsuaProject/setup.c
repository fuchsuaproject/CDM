#include"v.h"

int cdm_Setup() {
	FILE* pSetupBatch = fopen("CDMSETUP.BAT", "r");
	if (pSetupBatch == NULL) {
		pSetupBatch = fopen("CDMSETUP.BAT", "w");
		fprintf(pSetupBatch, "@title CDM_SETUP_PROGRAM_1_0\n@color 17\n@echo %%cd%%\\* > baseDir.cdm\n@exit");
		fclose(pSetupBatch);
	}
	system("start CDMSETUP.BAT");
	system("echo �� ���α׷��� ��ġ��θ� �Է��ϼ���.\nsetx /p installD=> ");
	system("echo %installD% > .\\STORE\\installD");
	FILE* FindFileSet = fopen(".\\STORE\\Library.list", "r");
	if (FindFileSet == NULL) {
		wprintf(L"setupdirectory/STORE/Library.list�� �������� �ʽ��ϴ�.\n");
	}
	else {
		char installD_Buffer[2048] = { 0, };
		installD_Buffer[0] = fgetc(FindFileSet);
		int i = 1;
		while (installD_Buffer[i] == NULL) {
			/// int it = 0;
			installD_Buffer[i] == fgetc(FindFileSet);
		}
	}
	return 0;
}

//print('dsfjaklsdjfkl' + 'asdfdsaf')
//dsfjaklsdjfklasdfdsaf

//printf("%s%s", "a", "A");
//aA

//%�� ����ϰ� ���������� %%�� ����.