#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#endif // _WIN32

#define NOB_IMPLEMENTATION
#include "nob.h"

#ifdef _WIN32
#define OUTPUT "build/RoFoVacation.exe"
#else
#define OUTPUT "build/RoFoVacation"
#endif // _WIN32

#define INCLUDE "-Iinclude", "-Ithird-party/PDFWriter/include/PDFWriter", \
                "-Ithird-party/PDFWriter/include/FreeType/include",       \
                "-Ithird-party/xlnt/include"
#define LIBRARY_PATHS "-Lthird-party/PDFWriter/lib", "-Lthird-party/xlnt/lib"
#define SOURCE "src/main.cpp", "src/PDFLayout.cpp", "src/RoFoVacationLayout.cpp", "src/RoFoVacationLayoutData.cpp"

#define COMMON_CFLAGS "-Wall", "-Wextra", "-pedantic", "-g"
#define LIBRARIES "-lPDFWriter", "-lZlib", "-lFreeType", "-lLibAesgm", "-lLibJpeg", "-lLibPng", "-lLibTiff", \
                  "-lxlnt"
#define STATIC_CFLAGS "-Xclang", "-D_MT", "-DSTATIC_BUILD", "-static", "-DXLNT_STATIC"

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);

    if (!nob_mkdir_if_not_exists("build"))
        return 1;

    Nob_Cmd cmd = {0};
    nob_cmd_append(&cmd, "clang++", "-std=c++17", COMMON_CFLAGS, INCLUDE, LIBRARY_PATHS, LIBRARIES, "-o", OUTPUT, SOURCE, STATIC_CFLAGS);
    if (!nob_cmd_run_sync(cmd))
        return 1;

    return 0;
}