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
// CDM은 커맨드 라인 인수를 통해 옵션을 입력받습니다.
// 옵션은 대쉬(-)로 시작하며, 옵션 내부의 구분자는 세미클론(;)입니다.
// 예를 들어, -option1;option2 -option3;option4 와 같은 형식입니다.
// CDM은 입력된 옵션을 파싱하여 각 옵션을 별도의 문자열로 분리합니다.

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

int main(int argc, char* argv[]) {
	// 필요한 전체 크기 계산
	size_t len = 0;
	for (int i = 0; i < argc; i++) {
		len += strlen(argv[i]) + 1;
	}

	// 메모리 할당
	char* all_args = (char*)malloc(len);
	if (all_args == NULL) {// 메모리 할당 실패 시
		return 1; // 메모리 할당 실패
	}
	all_args[0] = '\0'; // 빈 문자열로 초기화

	// 모든 인수를 하나의 문자열로 결합
	for (int i = 0; i < argc; i++) {// 모든 인수 순회
		strcat(all_args, argv[i]);// 인수 추가
		if (i < argc - 1) {// 마지막 인수가 아니면
			strcat(all_args, ";"); // 인수 사이에 구분자 세미클론 추가
		}
	}
	option = all_args;
	//만일 argc가 2보다 작다면 표준 입력으로부터 문자열을 읽어들임
	if (argc < 2) {// 인수가 2개 미만인 경우
		// 동적 할당으로 option 버퍼 생성
		option = (char*)malloc(1024 * sizeof(char));// 1KB 버퍼 할당
		scanf("%[^\n]", option);// 표준 입력에서 문자열 읽기
	}

	// option 파싱
	// 문자열에서 대쉬(-)로 시작하는 옵션을 찾아서
	// 그 뒤부터 다음 대쉬(-)로 시작하는 옵션 이전의 옵션까지를 추출
	// 및 OpsionInput 배열에 저장
	int opt_index = 0; // 옵션 인덱스
	char* token = strtok(option, "-"); // 대쉬(-)로 문자열 분리
	// 첫 번째 토큰은 옵션이 아니므로 건너뜀
	token = strtok(NULL, "-");// 다음 토큰으로 이동
	// 나머지 토큰들을 순회하며 옵션 추출
	// 이론상 무제한의 옵션을 지원한다. 이를 위해 동적 할당을 사용해야 하지만
	// 여기서는 최대 9개의 옵션만 지원하도록 제한
	while (token != NULL && opt_index < 9) {// 토큰이 남아있고 옵션 인덱스가 9 미만인 경우
		// 토큰에서 공백 문자 제거
		while (*token == ' ') {// 토큰의 시작이 공백인 경우
			token++;// 토큰 포인터를 다음 문자로 이동
		}
		// 옵션 문자열을 OpsionInput 배열에 복사
		strncpy(cdm_OpsionInput[opt_index], token, 259);// 최대 259자 복사
		cdm_OpsionInput[opt_index][259] = '\0'; // 널 종료자 추가
		opt_index++;// 옵션 인덱스 증가
		// 다음 토큰으로 이동
		token = strtok(NULL, "-");
	}// 옵션 파싱 완료
	// 토큰에서 왜 공백 문자를 제거하느냐?
	// 옵션 앞에 공백이 있을 수 있기 때문
	// 하지만 옵션 구분자는 ;이므로 옵션 내부의 공백은 제거하지 않음
	// 그러면 ;는 어떻게 처리하느냐?
	// 옵션 내부의 공백은 제거하지 않지만
	// 옵션 구분자인 ;는 옵션 내부에 포함될 수 없으므로
	// 옵션 내부의 공백은 제거하지 않음

	// CDM 옵션	처리
	// 각 옵션에 따라 다른 기능 수행
	// 예: -shell, -compile, -qgraphics 등
	// -shell 옵션은 커맨드 라인 셸 모드로 진입
	// -compile 옵션은 NKB 컴파일러 모드로 진입
	// -qgraphics 옵션은 Q 그래픽 라이브러리 모드로 진입
	// -setup 옵션은 설치 프로그램 실행

	for (int i = 0; i < opt_index; i++) {
		// 세미클론(;)으로 옵션 내부 구분
		cdm_StringPointer = strtok(cdm_OpsionInput[i], ";");
		// 셸 옵션 처리
		if (strcmp(cdm_OpsionInput[i], "shell") == 0) {
			// cdm_ShellMainCode 함수 호출
			cdm_ShellMainCode(0);
		}

		// setup 옵션 처리
		if (strcmp(cdm_OpsionInput[i], "setup") == 0) {
			// 하위 옵션	처리
			// setup 옵션은 추가 하위 옵션을 가질 수 있음
			// 예: -setup;install, -setup;uninstall 등
			// 조건문으로 cdm_Setup, yoany 함수 호출

			cdm_StringPointer = strtok(NULL, ";");
			if (cdm_StringPointer != NULL) {
				if (strcmp(cdm_StringPointer, "install") == 0) {
					cdm_Setup();
				}
				else if (strcmp(cdm_StringPointer, "yoany") == 0) {
					yoany();
				}
			}
		}
		// NKB 컴파일러 옵션 처리
		if (strcmp(cdm_OpsionInput[i], "compile") == 0) {
			// 컴파일러 옵션 처리
			// cdmb_Main 인자에 하위 옵션 전달을 위한 토큰 분리
			cdm_StringPointer = strtok(NULL, ";");// 다음 토큰으로 이동
			cdmb_Main(cdm_StringPointer);// cdmb_Main 함수 호출
		}
		//todo: Q 그래픽 라이브러리 옵션 처리
		//todo: 그	외 옵션 처리
	}

	// 토큰 분리 함수 튜토리얼
	// strtok 함수는 문자열을 특정 구분자로 분리하는 함수
	// 사용법:
	// char* strtok(char* str, const char* delim);
	// str: 분리할 문자열 (처음 호출 시에만 전달, 이후에는 NULL 전달)
	// delim: 구분자 문자열
	// 반환값: 분리된 토큰의 포인터 (더 이상 토큰이 없으면 NULL 반환)

	//todo: 프로그램 종료 전 정리 작업

	// 메모리 해제
	free(all_args);
	return 0;
}