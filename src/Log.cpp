#include "../include/Log.h"

Log::Log() {

}

Log::Log(const string fileName) {
    _fileName = fileName;

    if (!_file.is_open()) {

        _file.open(_fileName.c_str(), std::ofstream::out | std::ofstream::app );

        if (!_file.is_open()) {
            std::cout << "Couldn't open log file: " << _fileName << std::endl;
            return;
        }

    }

}

Log::~Log() {
    if (_file.is_open()) {
        _file.close();
    }
}

void Log::setFileName(const string fileName) {
    if (_fileName.length() == 0) {
        _fileName = fileName;
    }
}
