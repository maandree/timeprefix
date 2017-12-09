/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void
printline(const char *line)
{
	static struct timespec boottime;
	time_t realtime;
	struct tm *utctime;

	clock_gettime(CLOCK_BOOTTIME, &boottime);
	realtime = time(NULL);
	utctime = gmtime(&realtime);

	printf("[%010lu.%04lu %i-%02i-%02i %02i:%02i:%02i UTC] %s",
	       boottime.tv_sec, boottime.tv_nsec / 100000,
	       utctime->tm_year + 1900, utctime->tm_mon + 1, utctime->tm_mday,
	       utctime->tm_hour, utctime->tm_min, utctime->tm_sec,
	       line);

	fflush(stdout);
}

int
main(void)
{
	char *buf = NULL;
	size_t siz = 0;

	printline("--- Program started ---\n");
	while (getline(&buf, &siz, stdin) != -1)
		printline(buf);
	printline("--- Program exited ---\n");

	free(buf);
	return 0;
}
