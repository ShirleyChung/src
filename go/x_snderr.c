/******************************************************************************
 * PROGRAM ID : Send error message to monitor			  	      *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <axis.h>

main(int argc, char *argv[])
{
	int	rc;
	char	pname[16];

	if (argc < 2)
	{
		printf("Usage: x_snderr [pname] [errmsg]\n");
		printf("Example: x_snderr daemon \"daemon check error\"\n");
		exit(-1);
	}

	strcpy(pname, argv[1]);
	l_trim(pname);
	pname[8] = 0;
	rc = l_errlogmsg(pname, "%s", argv[2]);
	if (rc == 0)
		printf("send: [%s]-%s -------- ok\n", pname, argv[2]);
	else
	{
		printf("send: [%s]-%s ---------------- error\n", pname, argv[2]);
		exit(-1);
	}
	exit(0);
}
