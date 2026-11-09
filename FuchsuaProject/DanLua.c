#include"v.h"
#pragma pack(push,1)

#define DanLuaC "0.5"

char* tknptr = NULL;
int Field = 0;
int Giphi = 0;
int isPostThen = 0;

#define F_GOTO 19

void cdm_DanLua_Token_IF(char** argp) {
	//
	Field = 2; // 필드: if
	return;
}

void cdm_DanLua_Token_LOCAL(char** argp) {
	Field = 1; // 필드: local
	return;
}

void cdm_DanLua_Token_WHILE(char** argp) {
	Field = 3;
	return;
}

void cdm_DanLua_Token_FOR(char** argp) {
	Field = 4;
	return;
}

void cdm_DanLua_Token_END(char** argp) {
	Field = 5;
	Giphi--;
	return;
}

typedef struct {
	void (*func)(char** argp);
	char* name;
}if_table_t;

if_table_t ift[] = {
	{NULL, NULL},
};

typedef struct {
	char name[32];
	unsigned char* ptr;
	int type;
	int reserved1;
	long long reserved2[2];
}symbol_t;

typedef union {
	unsigned char* nil;
	long long number;
	unsigned char* string;
	long long boolean;
	unsigned char* table;
	unsigned char* function;
	unsigned char* userdata;
	unsigned char* thread;
}DType;

//__cdecl(alignas(1)) h
typedef struct {
	int type;
	DType* value;
}DValue;

DValue*(*DFunctionExemple)(int,DValue*);

// .code .symbol .heap .local .stack .str .const 순서 바이너리 파일

typedef struct {
	unsigned long long size;
	unsigned char*     prev;
	unsigned char*     next;
}DHeapBlock;

typedef struct {
	int key_type;
	DType* key_value;
	int value_type;
	DType* value_value;
	void* thisl;
}DKeyV;

typedef struct {
	DKeyV* dict_arr;
	DValue* numkey_arr;
	int size;
	int rea;
	void* metatable;
}table_t;

#define CRRMCHN 8192

int exit_list_head = 0;
int false_list_head = 0;
int loop_start_head = 0;
int loop_end_head = 0;
int data_section_head = 0;
char machine_code[CRRMCHN];
int current_state[65536];
int state_stack_address = 0;
int current_index_address = 0;
symbol_t static_symbol[256];
#define $ ;
#define rshrsh rshptr[*crrstr+temp_count]
#define ccc1(a,b) temp_count&&a(b)
#define ccc2 char* temp_str = realloc(NULL, sizeof(char) * temp_count + 1);\
strcpy_s(temp_str, temp_count+1, &rshptr[*crrstr]);\
*crrstr = *crrstr + temp_count;\
temp_count = 0;\
return temp_str;
#define ccc3(a) if (rshrsh == a && !temp_count) {\
temp_count++;\
ccc2;\
}\
else if (rshrsh == a) {\
	ccc2;\
	temp_count++;\
	ccc2;\
}\
char* NextToken(int* crrstr, char* rshptr) {
	int temp_count = 0;
	int lwzsk = 0;
	// int is_end = 0;
	while (1) {
		//
		if (rshrsh != '\0'&&temp_count) {
			ccc2;
		}
		else if (rshrsh != '\0') {
			return NULL;
		}
		if (rshrsh == '_' && lwzsk || !ccc1(isalpha, rshrsh) && lwzsk || ccc1(isalnum, rshrsh) && lwzsk) {
			ccc2;
			lwzsk = 0;
			temp_count++;
			continue; //&& !lwzsk
		}
		if (rshrsh == '_'&& !lwzsk || !ccc1(isalpha, rshrsh) && !lwzsk || ccc1(isalnum, rshrsh) && !lwzsk) {
			temp_count++;
			continue;
		}
		else {
			if (!lwzsk) {
				ccc2;
			}
			//continue;
		}//1 ㅗㅗㅗ
		if (rshrsh >= '1' && rshrsh <= '9' && (temp_count && !lwzsk)) {
			temp_count++;
			continue;
		}
		if (rshrsh >= '1' && rshrsh <= '9' && (!temp_count || lwzsk)) {
			temp_count++;
			lwzsk = 1;
			continue;
		}
		else if (rshrsh == '0') {
			if (*(&rshrsh + 1) == 'x') {
				//int a = 0; ;
				temp_count++;
				lwzsk = 1;
				continue;
			}
			else if (*(&rshrsh + 1) == 'b') {
				temp_count++;
				lwzsk = 1;
				continue;
			}
		}
		else {
			ccc2;
		} // Riam lis gherlamul zu tabriaes kheddies khedausugs.
		// Quu wtks tist? kalwsei
		ccc3('+') ccc3('-') int ao = 0;
	}
}

void cdm_TokeningTest(char** argp) {
	int count = 0;
	char* utst = "hello123 666aaa _0x abc+def";
	char* ipip = NextToken(&count, utst);
	printf("%s", ipip);
	while (ipip != NULL) {
		ipip = NextToken(&count, utst);
		printf("%s", ipip);
		free(ipip);
	}
}

void cdm_DanLuaMain(char** argp) {
	FILE* file = fopen(find("that", argp), "r");
	char line[1024];
	fread(line, sizeof(char), 1024, file);
	int qezep = 0;
	while (1) {
		char* token = NextToken(tknptr, line);
		int count = 0;
		/*while (ift[count].name != NULL) {
			if (strcmp(token, ift[count].name) == 0) {
				ift[count].func(argp);
				break;
			}
			count++;
		}*/
		if (strcmp(token, "if") == 0) {
			if (current_state[state_stack_address] == 0) {
				//+
				current_state[++state_stack_address] = 2;

			}
			//Field = 2; && !isPostThen()
		}
		else if (strcmp(token, "while") == 0) {
			if (current_state[state_stack_address] == 0) {
				current_state[++state_stack_address] = 2;
			}
		}
		else if (token[0] = '"') {
			if (Field == 1) {}
		}
	}
}