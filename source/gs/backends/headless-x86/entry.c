#include <stdio.h>

int gs_StartedFromCli = 0;

extern int gs_Main(int param);

static unsigned int string_to_int(const char* str) {
	unsigned int num = 0;
	while(*str != 0) {
		if (*str < '0' || *str > '9')
			break;

		num *= 10UL;
		num += *str - '0';

		str++;
	}

	return num;
}


int main(int argc, char** argv) {
	int param = 0;
	if (argc > 1) {
		param = string_to_int(argv[1]);
	}
	gs_StartedFromCli = 1;
	return gs_Main(param);
}