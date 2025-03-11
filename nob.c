#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#endif // _WIN32

#define NOB_IMPLEMENTATION
#include "nob.h"

int main(int argc, char **argv)
{
	NOB_GO_REBUILD_URSELF(argc, argv);
	Nob_Cmd cmd = {0};
	nob_cmd_append(&cmd, "clang++", "-Wall", "-Wextra", "-o", "main.exe", "main.cpp");
	if (!nob_cmd_run_sync(cmd))
		return 1;

	return 0;
}