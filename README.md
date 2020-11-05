# ChessVersus 双人棋类线下竞技游戏

## 需求概述

程序实现一个带管理员后台、支持多用户、支持双人同玩的CLI棋类游戏。游戏实现了3种兼顾易上手性与可玩性的双人棋类游戏。

### 游戏系统需求

- 管理员后台及管理员对游戏系统、游戏数据的操作
- 游戏数据，游戏进度支持保存、读取
- 多用户系统

### 游戏主体需求

- 实现翻转棋、五子棋、移子棋
- 双人游戏
- 支持中途退出游戏并保存，支持从上次游戏进度恢复游戏

### 玩家需求

- 查看个人信息，维护个人信息
- 查看游戏记录

## 程序流程

![流程图](流程图.png)

## 架构设计

### graph.cpp

在控制台窗口绘图

### game.cpp

游戏主要内容，调用`graph.cpp`进行绘图，`getch()`获取键盘事件并作出响应

```c++
GameRecord NewReversi(GameStatus &new_status);//翻转棋
GameRecord NewGomoku(GameStatus &new_status);//五子棋
GameRecord NewMove(GameStatus &new_status);//移子棋
```

在`main.cpp`中调用函数开启新游戏，并引用一个`struct GameStatus`在游戏中途退出时用于保存游戏进度。正常结束游戏返回`struct GameRecord`游戏记录