/**
 * timeprefix – Prefix each line with the time it as written
 * 
 * Copyright © 2014  Mattias Andrée (maandree@member.fsf.org)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <time.h>
#include <stddef.h>
#include <stdlib.h>


static struct tm* utctime;


static void printline(const char* line)
{
  struct timespec boottime;
  time_t realtime;
  
  clock_gettime(CLOCK_BOOTTIME, &boottime);
  realtime = time(NULL);
  gmtime_r(&realtime, utctime);
  
  printf("[%010lu.%04lu %i-%02i-%02i %02i:%02i:%02i UTC] %s",
	 boottime.tv_sec, boottime.tv_nsec / 100000,
	 utctime->tm_year + 1900, utctime->tm_mon + 1, utctime->tm_mday,
	 utctime->tm_hour, utctime->tm_min, utctime->tm_sec,
	 line);
  
  fflush(stdout);
}


int main(int argc, char** argv)
{
  size_t buf_size = 512;
  char* buf = NULL;
  
  utctime = malloc(sizeof(struct tm));
  
  printline("--- Program started ---\n");
  
  buf = malloc(buf_size * sizeof(char));;
  while (getline(&buf, &buf_size, stdin) != -1)
    printline(buf);
  
  printline("--- Program exited ---\n");
  
  free(buf);
  return 0;
}

