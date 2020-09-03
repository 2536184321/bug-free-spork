#ifndef GAME_H
#define GAME_H

#include <vector>

enum GameType
{
    MAN,
    AI
};

enum GameStatus//游戏状态
{
    PLAYING,
    WIN,
    DEAD
};

//棋盘尺寸
const int BOARD_GRAD_SIZE = 19;

const int MARGIN = 30;//棋盘边缘空隙
const int CHESS_RADIUS = 15;//棋子半径
const int MARK_SIZE = 6;//落子标记边长
const int BLOCK_SIZE = 40;//格子的大小
const int POS_OFFSET = BLOCK_SIZE * 0.4;//鼠标点击的模糊距离

const int AI_THINK_TIME = 700;

class GameModel
{
public:
    GameModel(){}

public:
    //存储当前游戏棋盘和棋子的情况，空白为0，黑子为1，白子-1
    std::vector<std::vector<int>> gameMapVec;

    //存储各个点位的评分情况，作为AI下棋依据
    std::vector<std::vector<int>> scoreMapVec;

    //标示下棋方，true：黑棋方 flase：AI/白棋方
    bool playerFlag;

    GameType gameType;//游戏模式

    GameStatus gameStatus;//游戏状态

    void startGame(GameType type);//开始游戏

    void actionByPerson(int row, int col);
    void updataGameMap(int row, int col);


    void calulateScore();//计算评分
    void actionByPerson(int row, int col);//人执行下棋
    void actionByAI(int &clickRow, int &clickCol);//机器执行下棋
    void updateGameMap(int row, int col);//每次落子后更新游戏棋盘
    bool iswin(int row, int col);
    bool isDeadGame();


};

#endif //GAME_H
