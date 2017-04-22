#include "logfile.h"
#include "tool.h"
#include <ctime>

LogFile::LogFile(const string& fn)
:_fn(fn)
{
	CheckDirExist(_fn);
}

LogFile::~LogFile()
{
	
}

LogFile& LogFile::operator<<(const string& log)
{
	time_t result = std::time(NULL);
              
	ofstream ofs(_fn.c_str());
	ofs.seekp(0, ios_base::end);
	ofs<< "[" << asctime(localtime(&result)) << "]:" << log << "\n";
	return *this;
}

