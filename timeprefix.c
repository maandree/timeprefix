/* See LICENSE file for copyright and license details. */
#include <sys/timex.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


static void
printline(const char *line)
{
	static struct timex timex; /* static to zero initialise it */
	struct timespec boottime;
	struct tm *utctime;
	int r;

	clock_gettime(CLOCK_BOOTTIME, &boottime);
	r = adjtimex(&timex);
	if (timex.time.tv_sec % (24 * 60 * 60) == 0) {
		if (r == TIME_INS) {
			timex.time.tv_sec -= 1;
			utctime = gmtime(&timex.time.tv_sec);
			utctime->tm_sec += 1;
		} else if (r == TIME_DEL) {
			timex.time.tv_sec += 1;
			utctime = gmtime(&timex.time.tv_sec);
		} else {
			utctime = gmtime(&timex.time.tv_sec);
		}
	} else if (r == TIME_OOP) {
		utctime = gmtime(&timex.time.tv_sec);
		utctime->tm_sec += 1;
	} else {
		utctime = gmtime(&timex.time.tv_sec);
	}

	printf("[%010lu.%04lu %i-%02i-%02i %02i:%02i:%02i UTC] %s",
	       boottime.tv_sec, boottime.tv_nsec / 100000,
	       utctime->tm_year + 1900, utctime->tm_mon + 1, utctime->tm_mday,
	       utctime->tm_hour, utctime->tm_min, utctime->tm_sec,
	       line);

	fflush(stdout);
}

int
main(int argc, char *argv[])
{
	char *buf = NULL;
	size_t siz = 0;

	if (argc > 1 && argv[1][0] == '-' && argv[1][1] == '-' && !argv[1][2])
		argc -= 1;
	if (argc > 1) {
		fprintf(stderr, "usage: %s\n", argv[0]);
		return 1;
	}

	printline("--- Program started ---\n");
	while (getline(&buf, &siz, stdin) != -1)
		printline(buf);
	printline("--- Program exited ---\n");

	free(buf);
	return 0;
}
