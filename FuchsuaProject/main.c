/*
#######################################
# 레몬코림 소개 #                     #
#######################################
# Link: https://discord.gg/zVmzkd47HA #
#######################################
*/

// CDM Main Source File
// 이 줄에서부터는 기여자를 위한 기본 동작 원리 주석 설명입니다.

// 기능들
// CDM은 커맨드 라인 인터페이스 셸, NKB라는 함수형 프로그래밍 언어를 위한 컴파일러,
// 그리고 Q라는 4비트 그래픽 라이브러리를 포함합니다.(Q는 타 프로젝트로 분리 예정)

// CDM 메인 동작 원리


// 셸 모드
// CDM은 기본적으로 커맨드 라인 셸 모드로 동작합니다.
// 사용자는 CDM 셸에서 다양한 명령어를 입력하여 파일 시스템을 탐색하고,
// 디렉토리를 변경하며, 파일 및 디렉토리를 생성하거나 삭제할 수 있습니다.

// NKB 컴파일러 모드
// CDM은 NKB 언어로 작성된 소스 코드를 컴파일할 수 있는 기능을 제공합니다.
// 사용자는 CDM을 통해 NKB 소스 파일을 컴파일하여 실행 가능한
// 바이너리 파일을 생성할 수 있습니다.

// Q 그래픽 라이브러리
// CDM은 Q라는 4비트 그래픽 라이브러리를 포함하고 있습니다.
// Q는 간단한 그래픽 작업을 수행할 수 있는 기능을 제공하며,
// CDM과 함께 사용하여 그래픽 애플리케이션을 개발할 수 있습니다.
// 다만, Q 그래픽 라이브러리는 타 프로젝트로 분리될 예정입니다.

// CDM은 이러한 기능들을 통합하여 사용자가 다양한 작업을 수행할 수 있도록 지원합니다.

// 여기 부터는 메인소스코드
#include"v.h"
//#define q_io 0
#include"binary.h"

char cdm_OpsionInput[9][260] = { 0, };
char* cdm_StringPointer;
int main_Start = 0;

char* option;

extern char cdm_HyeonjaeDirectoryGyeongro[260];

//

struct cdm_Link {
	void* functionPointer;
	char* optionString;
};

static inline char** cdm_OptionToken(char* input) {
	char* token = strtok(input, " ");
	int tokenLen = strlen(token);
	char** argp = (char*)malloc(1);
	int count = 0;
	while (token != NULL) {
		//아래 코드를 realloc 으로 할 예정
		realloc(*(argp + count), tokenLen + 1);
		strcpy(*(argp + count), token);
		token = strtok(NULL, " ");
		count++;
	}
	return argp;
}

struct cdm_Link cdm_LinkList[] = { {NULL, NULL} };
static inline void cdm_Arg1(char** argp);
static inline void cdm_Arg0() {
	char** argp = NULL;
	// 옵션이 없는 경우 자주쉘 모드로 갑니다.
	// 보안상 리유로 scanf를 사용하지 않고 fgets나 scanf_s를 련락합니다.
	char* input = (char*)malloc(260);
	fgets(input, 260, stdin);
	if(input != NULL) {
		argp = cdm_OptionToken(input);
	}
	cdm_Arg1(argp);
	free(input);
	//return;
}

static inline void cdm_Arg1(char** argp) {
	// 만약 옵션이 있다면 cdm_LinkList를 돌려서 해당 옵션을 찾습니다.
	int found = 0;
	for (int i = 0; cdm_LinkList[i].optionString != NULL; i++) {
		if (strcmp(argp[1], cdm_LinkList[i].optionString) == 0) {
			void (*func)(char* argp) = cdm_LinkList[i].functionPointer;
			func(argp);
			found++;
			break;
		}
	}
	if (found == 0) {
		printf("Not found option\nError: CDM could not find option that you entered.\n");
		//return;
	}
	//
}

int main(int argc, char* argv[]) {
	// 1. argv[1]을 반복문으로 돌려서 if문으로 옵션을 찾습니다.
	// 2. 맞는 옵션이 있으면 cdm_LinkList[해당].functionPointer를 련락합니다.
	// 3. 맞는 옵션이 없으면 자살합니다.

	while (1) {
		if (argc > 1) {
			cdm_Arg1(argv);
		}
		else {
			cdm_Arg0();
		}
		break;
	}
	exit:
	return 0;
}