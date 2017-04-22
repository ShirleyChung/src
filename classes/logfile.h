#ifndef _logfile_for_logging_msg_save_sand_time
#define _logfile_for_logging_msg_save_sand_time

#include <fstream>
#include <string>

using namespace std;

class LogFile
{
	string _fn;
public:
	LogFile(const string& fn);
	virtual ~LogFile();
	
	LogFile& operator<<(const string& log);
	
};

#endif
