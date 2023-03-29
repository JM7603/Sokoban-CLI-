#include <stdio.h>

#include "../include/sokoban/sokoban.h"

int current_x, current_y;
int target_count, filled_count;
int map[MAP_SIZE][MAP_SIZE] = {
    0, 0, 1, 1, 1, 0, 0, 0,
    0, 0, 1, 4, 1, 0, 0, 0,
    0, 0, 1, 0, 1, 1, 1, 1,
    1, 1, 1, 3, 0, 3, 4, 1,
    1, 4, 0, 3, 2, 1, 1, 1,
    1, 1, 1, 1, 3, 1, 0, 0,
    0, 0, 0, 1, 4, 1, 0, 0,
    0, 0, 0, 1, 1, 1, 0, 0,
};

void Init() {
  GetCurrentPos();
  GetTargetCount();
}

void GetCurrentPos() {
  for (int i = 0; i < MAP_SIZE; ++i) {
    for (int j = 0; j < MAP_SIZE; ++j) {
      if (map[i][j] == PERSON || map[i][j] == TARGET_PERSON) {
        current_x = i;
        current_y = j;
        return;
      }
    }
  }
}

void GetTargetCount() {
  target_count = 0;
  for (int i = 0; i < MAP_SIZE; ++i) {
    for (int j = 0; j < MAP_SIZE; ++j) {
      if (map[i][j] == TARGET) target_count++;
    }
  }
}

void ShowMap() {
  for (int i = 0; i < MAP_SIZE; ++i) {
    for (int j = 0; j < MAP_SIZE; ++j) {
      switch (map[i][j]) {
        case BLANK: printf("  ");
          break;
        case WALL: printf("[]");
          break;
        case PERSON:
        case TARGET_PERSON: printf("&&");
          break;
        case BOX: printf("()");
          break;
        case TARGET: printf("@@");
          break;
        case TARGET_BOX: printf("<>");
          break;
      }
    }
    putc('\n', stdout);
  }
  printf("%d/%d\n", filled_count, target_count);
}

bool IsWin() {
  return filled_count == target_count;
}

/*
 * 有以下几种是可以移动的
 * 1.人的前面是空白
 * 2.人的前面是箱子，箱子前面是空白/目标点
 * 3.人的前面是目标点
 * 4.人的前面是目标点与箱子重合，重合前面是空白
 * */
void Move(int offset_x, int offset_y) {
  int next_x = current_x + offset_x;
  int next_y = current_y + offset_y;
  int next_next_x = next_x + offset_x;
  int next_next_y = next_y + offset_y;

  // 提前判断，防止越界
  if (map[next_x][next_y] == WALL) return;

  if (map[next_x][next_y] == BLANK) {
    map[next_x][next_y] += PERSON;
    map[current_x][current_y] -= PERSON;
    current_x = next_x;
    current_y = next_y;
  } else if (map[next_x][next_y] == BOX
      && (map[next_next_x][next_next_y] == BLANK || map[next_next_x][next_next_y] == TARGET)) {
    if (map[next_next_x][next_next_y] == TARGET) {
      filled_count++;
      map[next_next_x][next_next_y] = TARGET_BOX;
    } else {
      map[next_next_x][next_next_y] = BOX;
    }
    map[next_x][next_y] = PERSON;
    map[current_x][current_y] -= PERSON;
    current_x = next_x;
    current_y = next_y;
  } else if (map[next_x][next_y] == TARGET) {
    map[next_x][next_y] += PERSON;
    map[current_x][current_y] -= PERSON;
    current_x = next_x;
    current_y = next_y;
  } else if (map[next_x][next_y] == TARGET_BOX && map[next_next_x][next_next_y] == BLANK) {
    map[next_next_x][next_next_y] = BOX;
    map[next_x][next_y] = TARGET_PERSON;
    map[current_x][current_y] -= PERSON;
    current_x = next_x;
    current_y = next_y;
    filled_count--;
  }
}
