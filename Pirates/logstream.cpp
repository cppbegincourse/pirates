#include "logstream.h"

LogStream* LogStream::mpInstance;
std::ofstream LogStream::logfile;
bool LogStream::logEnabled = true;
