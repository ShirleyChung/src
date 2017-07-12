/*****************************************/
/** Deamon Demo 2015.8.28		**/
/*****************************************/

#include "daemon.h"
#include <stdio.h>
#include <time.h>
#include <string>

using namespace std;

void writeLog(const char* file, const char* formatStr)
{
	char buf[512] = {0};
	char line[512] = {0};

	sprintf(buf, "%s.log", file);

	FILE *fp = fopen(buf, "a+");
	if (fp)
	{
		fwrite(formatStr, sizeof(char), strlen(formatStr), fp);
		fwrite("\n", sizeof(char), 1, fp);
		fclose(fp);	
	}
	else
		perror("cannot open log file to write");
}

bool initDaemon()
{
#ifdef posix
        pid_t pid, sid;
	char whoiam[] = "setupDaemon";

        /* Fork off the parent process */       
        if ((pid = fork()) < 0) {
		writeLog(whoiam, "fork fail.");
		return false;
        }
        /* If we got a good PID, then
           we can exit the parent process. */
        if (pid > 0) {
		writeLog(whoiam, "fork ok.");
		exit(DAEMON_PID_OK);
        }

	sid = setsid();
	signal(SIGHUP, SIG_IGN);
	if (sid < 0)
	{
		writeLog(whoiam, "setsid fail!");
		exit(DAEMON_PID_FAIL);
	}

	/*if ( (pid = fork()) < 0 ){
		writeLog(whoiam, "second fork fail.");
		exit(DAEMON_PID_FAIL);
	}
	*/	

	/*change current work directory*/
	/*if (chdir("/") < 0)
	{
		writeLog(whoiam, "change dir fail!");
		exit(D_FAIL);
	}
	*/

        /* Change the file mode mask */
        umask(0);

	writeLog(whoiam, "ready to run loop..\n");

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
#else
#endif
	return true;
}
