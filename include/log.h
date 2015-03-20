#ifndef LOG_H
#define LOG_H

#include <string>
#include <iostream>
#include <fstream>

#define LOG(file, str, list) {printf(str, list);}//{Log *l = new Log(file); l->log(str, list);} broken

class Log
{
public:
    Log(std::string file);
    ~Log();
    
    void log(std::string str, ...);
private:
    std::ofstream outfile;
};

#endif