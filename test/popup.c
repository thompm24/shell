#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  int nap = atoi(argv[1]);

  pid_t pid = fork();

  if (pid < 0) {
    printf("Error occurred\n");
  }
  if (pid == 0) {
    sleep(nap);
    system("xmessage 'Hello world'");
  }
  if (pid > 0) {
    time_t start = time(NULL);
    wait(NULL);
    sleep(2);
    printf("%ld\n", start);
  }
}



/*
time_t ==long int %ld
time_t now = time(NULL);   current time epoch

double difftime


char *ctime(time_t *)      ==      char *asctime(localtime(time_t *));

printf("%s\n", ctime(&now));
Fri Aug 6 11:32:41 2021\n

struct tm *gmtime(&now);       //Greenwich
struct tm *localtime(&now);    //Local

mktime(struct tm)
procues time_t format converted from unix time.

take in input from user, if only time included, get localtime(time(NULL))->tm_sec = (time to seconds))
sleep((int) difftime)
system("xmessage 'ALARM ALARM ALARM\n%s'", user_message);



char s[100] = strftime(s,100,"%A %B %d", cur_time);


clock_t start = clock()
Amount of clock ticks sinc start of program




struct tm {
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;       //day of month
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_dst;         //is daylight savings

}

char s[100] = strftime(s,100,"%A %B %d", cur_time);
printf*("%s\n" s);
Sunday March 06

%a 	Abbreviated weekday name 	Sun
%A 	Full weekday name 	Sunday
%b 	Abbreviated month name 	Mar
%B 	Full month name 	March
%c 	Date and time representation 	Sun Aug 19 02:56:02 2012
%d 	Day of the month (01-31) 	19
%H 	Hour in 24h format (00-23) 	14
%I 	Hour in 12h format (01-12) 	05
%j 	Day of the year (001-366) 	231
%m 	Month as a decimal number (01-12) 	08
%M 	Minute (00-59) 	55
%p 	AM or PM designation 	PM
%S 	Second (00-61) 	02
%U 	Week number with the first Sunday as the first day of week one (00-53) 	33
%w 	Weekday as a decimal number with Sunday as 0 (0-6) 	4
%W 	Week number with the first Monday as the first day of week one (00-53) 	34
%x 	Date representation 	08/19/12
%X 	Time representation 	02:50:06
%y 	Year, last two digits (00-99) 	01
%Y 	Year 	2012
%Z 	Timezone name or abbreviation 	CDT
%% 	A % sign 	%

*/#
