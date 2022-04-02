#include <stdio.h>
// days for each month in a year (not leap and leap)
static char day_table [2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int _leap(int year);
int day_of_year(int year, int month, int day);
void month_day(int year, int year_day, int *pmonth, int *pday);
char *month_name(int n);

/* Converts the day of a month into the day of the year and viceversa;
   e.g. 1st of march -> 60th day of the year, or 61st if leap
   year.
*/
int main() {
  int day = 1, month = 3, year = 2022;
  int leap = _leap(year);
  printf("Year %d leap ? %s\n", year, leap ? "True" : "False");

  int day_year = day_of_year(year, month, day);
  printf("%d-%d-%d : day of year = %d\n", year, month, day, day_year);

  int day_month, year_month;
  int *pday = &day_month;
  int *pmonth = &year_month;
  month_day(year, day_year, pmonth, pday);
  printf("Year %d, day of the year %d -> day %d of the month %d\n", year, day_year, day_month, year_month);

  printf("Month %d: %s\n", month, month_name(month));
}

int day_of_year(int year, int month, int day) {
  int leap;
  leap = _leap(year);
  for (int i = 1; i <month; i++)
    day += day_table[leap][i];
  return day;
}

void month_day(int year, int year_day, int *pmonth, int *pday) {
  int i, leap;
  leap = _leap(year);
  for (i = 1; year_day > day_table[leap][i]; i++)
    year_day -= day_table[leap][i];
  *pmonth = i;
  *pday = year_day;
}

int _leap(int year) {
  int leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  return leap;
}
/* Returns a pointer to the name of the month given its number */
char *month_name(int n) {
  static char *name[] = {
    "Unknown month", "January", "February", "March",
    "April", "May", "June", "July", "August", "September",
    "October", "November", "December"
  };
  return (n < 1 || n > 12) ? name[0] : name[n];
}
