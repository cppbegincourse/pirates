#ifndef LOGSTREAM_H
#define LOGSTREAM_H
#include "stdafx.h"
#include <fstream>
#include <string>

// A bit strange log system
// It can write to logFile only once
// Auto-disabled itself on Close()
class LogStream
{
public:
    LogStream* operator->() {return mpInstance;}
    const LogStream* operator->() const {return mpInstance;}

    LogStream(std::string logFile) {
        static bool static_init = [this, &logFile]()->bool {
                    mpInstance = this;
                    logfile.open(logFile);
                    logEnabled = true;
                    return true;
                }();
    }

    LogStream& operator<< (std::string str) {
        if (logEnabled)
            logfile << str;
        return *this;
    }

    void Close() { logfile.close(); logEnabled = false; }
private:
    LogStream(const LogStream& root) = delete;
    LogStream& operator=(const LogStream&) = delete;

    static std::ofstream logfile;

    static LogStream* mpInstance;
    static bool logEnabled;
};
#endif // LOGSTREAM_H
