#include "csapp.h"

unsigned int wakeup (unsigned int secs)
{
	unsigned int rc = sleep(secs);

	printf("Woke up at %d secs.\n", secs-rc);
	return rc;
}
