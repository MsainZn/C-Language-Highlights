#include <stdio.h>
#include <time.h>

int main ()
{
  
  time_t rawtime;
  
  /*
   // This function returns a pointer to a tm structure with the time information filled in. 
       struct tm 
       {
           int tm_sec;         // seconds,  range 0 to 59          
           int tm_min;         // minutes, range 0 to 59           
           int tm_hour;        // hours, range 0 to 23             
           int tm_mday;        // day of the month, range 1 to 31  
           int tm_mon;         // month, range 0 to 11             
           int tm_year;        // The number of years since 1900   
           int tm_wday;        // day of the week, range 0 to 6    
           int tm_yday;        // day in the year, range 0 to 365  
           int tm_isdst;       // daylight saving time             	
        };
  */
  struct tm * timeinfo;

  
  /*
        time() function is defined in time.h (ctime in C++) header file. 
        This function returns the time since 00:00:00 UTC, Jan-1-1970 (Unix timestamp) in seconds. 
        If second is not a null pointer, the returned value is also stored in the object pointed to by second.
        time_t time ( time_t *second ) 
  */
  time (&rawtime);
  
  
  
  /*
        The C library function struct tm *localtime(const time_t *timer) uses the time pointed by time_t* timer and 
        breaks into the structure tm and expressed in the local time zone.
  */
  timeinfo = localtime (&rawtime);
  
  
  /*
        The C library function char *asctime(const struct tm *timeptr) returns a pointer to a string which represents the day and time of the structure struct timeptr.
  */
  puts(asctime(timeinfo));
  
  
  printf ("Current local second:    %i\n", timeinfo->tm_sec);
  printf ("Current local minute:    %i\n", timeinfo->tm_min);
  printf ("Current local hour:      %i\n", timeinfo->tm_hour);
  
  printf ("Current local month-day: %i\n", timeinfo->tm_mday);
  printf ("Current local week-day:  %i\n", timeinfo->tm_wday);
  printf ("Current local year-day:  %i\n", timeinfo->tm_yday);
    
  printf ("Current local month:     %i\n", timeinfo->tm_mon);
  printf ("Current local year:      %i\n", timeinfo->tm_year);
  

  return 0;
}

