#ifndef SOKOBAN_SRC_SOKOBAN_H_
#define SOKOBAN_SRC_SOKOBAN_H_

#include <stdbool.h>
#define MAP_SIZE 8

/* 控制键 */
enum Control {
  UP = 87,            // W: 向上移动
  LEFT = 65,          // A: 向左移动
  DOWN = 83,          // S: 向下移动
  RIGHT = 68,         // D: 向右移动
  QUIT = 81,          // Q: 退出
  RESTART = 82        // R: 重新开始
};

/* 物体类型 */
enum Object {
  BLANK = 0,          // 空白
  WALL = 1,           // 墙
  PERSON = 2,         // 人
  BOX = 3,            // 箱子
  TARGET = 4,         // 目标点
  TARGET_PERSON = 6,  // 目标点与人重合
  TARGET_BOX = 7      // 目标点与箱子重合
};

/* 初始化 */
void Init();

/* 打印地图 */
void ShowMap();

/* 移动 */
void Move(int offset_x, int offset_y);

/* 拿到当前位置 */
void GetCurrentPos();

/* 拿到目标点的个数 */
void GetTargetCount();

/* 通关判定 */
bool IsWin();

#endif //SOKOBAN_SRC_SOKOBAN_H_
