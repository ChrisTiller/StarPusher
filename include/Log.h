#ifndef LOG_H
#define LOG_H

#include <string>
#include <fstream>
#include <iostream>

using std::ofstream;
using std::string;

class Log {

public:

    Log();
    Log(const string);
    ~Log();

    void setFileName(const string);

    template<typename T>
    void log(const T line) {

        if (!_file.is_open()) {

            _file.open(_fileName.c_str(), std::ofstream::out | std::ofstream::app );

            if (!_file.is_open()) {
                std::cout << "Couldn't open log file: " << _fileName << std::endl;
                return;
            }

        }

        _file << line << std::endl;

        _file.flush();

    }

private:

    string _fileName;

    ofstream _file;

};

static Log logInstance("test");

#endif
