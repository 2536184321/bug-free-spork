#ifndef GAMEMODEL_H
#define GAMEMODEL_H

// ---- 五子棋游戏模型类 ---- //
#include <vector>

// 游戏类型，双人还是AI（目前固定让AI下黑子）
enum GameType
{
    PERSON,
    AI   //人机对弈模式
};

// 游戏状态
enum GameStatus
{
    PLAYING,
    WIN,
    DEAD
};

// 棋盘尺寸
const int BOARD_GRAD_SIZE = 20;
const int MARGIN = 30; // 棋盘边缘空隙
const int CHESS_RADIUS = 15; // 棋子半径
const int MARK_SIZE = 6; // 落子标记边长
const int BLOCK_SIZE = 40; // 格子的大小
const int POS_OFFSET = BLOCK_SIZE * 0.4; // 20 鼠标点击的模糊距离上限

const int AI_THINK_TIME = 700; // AI下棋的思考时间

class GameModel
{
public:
    GameModel();

public:
    // 存储当前游戏棋盘和棋子的情况,空白为0，黑子1，白子-1
    std::vector<std::vector<int>> gameMapVec;

    // 存储各个点位的评分情况，作为AI下棋依据
    std::vector<std::vector<int>> scoreMapVec;

    // 标示下棋方, true:黑棋方  false: AI 白棋方（AI方）
    bool playerFlag;

    // 游戏模式：人机对弈，还是双人
    GameType gameType;

    // 游戏状态
    GameStatus gameStatus;

    void startGame(GameType type); // 开始游戏

    void actionByPerson(int row, int col);

    void updateGameMap(int row, int col);

    bool isWin(int row, int col); //判断输赢

    bool ispease();

    void calculateScore();
    void actionByAI(int &clickRow, int &clickCol); // 机器执行下棋
};

#endif // GAMEMODEL_H
