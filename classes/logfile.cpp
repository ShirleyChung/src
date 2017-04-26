#include "logfile.h"
#include "tool.h"
#include <ctime>

LogFile::LogFile(const string& fn)
:_fn(fn)
{
	CheckDirExist(_fn);
	CheckFileExist(_fn);
}

LogFile::~LogFile()
{
	
}

LogFile& LogFile::operator<<(const string& log)
{
	time_t result = std::time(NULL);
              
	ofstream ofs(_fn.c_str(), ios::app);
//	ofs.seekp(0, ios::end);
	string time = asctime(localtime(&result));
	ofs<< "[" << rtrim( time, "\r\n") << "] : " << log << "\n";
	return *this;
}

