#include <locale.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

int main() {
  setlocale(LC_ALL, "");

  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  while (1) {
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    wprintf(L"\033[0G");
    wprintf(L"%d:%d:%d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    usleep(50 * 1000);
  }

  return 0;
}
