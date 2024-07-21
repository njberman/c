#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

#define ROWS 50
#define COLS 50

#define ALIVE_CHAR ' '
#define DEAD_CHAR L'\u2588'

int DIRS[8][2] = {{1, 1},   {1, 0},  {1, -1}, {0, -1},
                  {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}};

int state[ROWS][COLS] = {0};

int mod(int a, int b) { return (a % b + b) % b; }

int count(int x, int y, int currentState[ROWS][COLS]) {
  int neighbourCount = 0;

  for (size_t i = 0; i < 8; ++i) {
    int *dir = DIRS[i];
    int dx = dir[0];
    int dy = dir[1];

    int newx = mod(x + dx, COLS);
    int newy = mod(y + dy, ROWS);
    // if (newx < 0 || newx >= COLS || newy < 0 || newy >= ROWS) continue;

    neighbourCount += currentState[newy][newx];
  }

  return neighbourCount;
}

int main() {
  setlocale(LC_ALL, "");
  srand(time(NULL));

  // state[2][3] = 1;
  // state[3][4] = 1;
  // state[4][2] = 1;
  // state[4][3] = 1;
  // state[4][4] = 1;

  for (size_t y = 0; y < ROWS; ++y) {
    for (size_t x = 0; x < COLS; ++x) {
      state[y][x] = rand() / (RAND_MAX / 2 + 1);
    }
  }

  while (1) {
    int newState[ROWS][COLS];

    for (size_t y = 0; y < ROWS; ++y) {
      for (size_t x = 0; x < COLS; ++x) {
        if (state[y][x] == 1) {
          wprintf(L"%lc%lc", ALIVE_CHAR, ALIVE_CHAR);
        } else {
          wprintf(L"%lc%lc", DEAD_CHAR, DEAD_CHAR);
        }

        int neighbourCount = count(x, y, state);

        // wprintf(L"%d", neighbourCount);

        newState[y][x] = 0;
        if ((neighbourCount == 2 && state[y][x] == 1) || neighbourCount == 3)
          newState[y][x] = 1;
      }
      wprintf(L"\n");
    }

    for (size_t y = 0; y < ROWS; ++y) {
      for (size_t x = 0; x < COLS; ++x) {
        state[y][x] = newState[y][x];
      }
    }
    usleep(50 * 1000);

    wprintf(L"\033[H");
  }
}
