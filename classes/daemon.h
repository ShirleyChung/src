#ifndef _daemon_common_20150901_shirley
#define _daemon_common_20150901_shirley

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

const int D_OK = 0;
const int D_FAIL = -1;

const int DAEMON_PID_OK = 2;
const int DAEMON_PID_FAIL = 3;
const int DAEMON_SID_OK = 4;
const int DAEMON_SID_FAIL = 5;

bool initDaemon();

void writeLog(const char* file, const char* formatStr);

#endif
