#include "log.h"
#include <stdarg.h>

Log::Log(std::string file) {
    outfile.open(file, std::ios::out | std::ios::app);
}

Log::~Log() {
    outfile.close();
}

void Log::log(std::string str, ...) {
    va_list list;
    va_start(list, str);

    // probably really bad for performance, copying the string lots of times
    char *buf = (char*)malloc(sizeof(char)*str.size());
    vsprintf(buf, str.c_str(), list);
    std::string b = buf;
    outfile << b << std::endl;
    std::cout << b << std::endl;
    va_end(list);
}