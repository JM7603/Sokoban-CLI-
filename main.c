#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "./include/sokoban/sokoban.h"

int main() {
  unsigned char ch;
  HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
  system("cls");

  Init();
  do {
    SetConsoleCursorPosition(h_out, (COORD) {0, 0});
    ShowMap();
    if (IsWin()) break;
    switch (ch = (getch() & ~32)) {
      case UP: Move(-1, 0);
        break;
      case LEFT: Move(0, -1);
        break;
      case DOWN: Move(1, 0);
        break;
      case RIGHT: Move(0, 1);
        break;
    }
  } while (ch != QUIT);

  if (IsWin()) {
    printf("恭喜过关!\n");
  } else {
    printf("似乎出现问题了!\n");
  }

  return 0;
}
