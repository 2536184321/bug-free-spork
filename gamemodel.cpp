#include "game.h"

void GameModel::startGame(GameType type)
{
    gameType = type;

    //初始棋盘
    gameMapVec.clear();
    for (int i = 0; i < BOARD_GRAD_SIZE; i++)
    {
        std::vector<int> lineBoard;
        for (int j = 0; j < BOARD_GRAD_SIZE; j++)
            lineBoard.push_back(0);
        gameMapVec.push_back(lineBoard);
    }

    //如果是AI模式，需要初始化评分数组
    if (gameType == AI)
    {
        scoreMapVec.clear();
        for (int i = 0; i < BOARD_GRAD_SIZE; i++)
        {
            std::vector<int> lineScores;
            for (int j = 0; j < BOARD_GRAD_SIZE; j++)
                lineScores.push_back(0);
            scoreMapVec.push_back(lineScores);
        }
    }

    //轮到黑方下棋为true，白方为false
    playerFlag = true;

}

void GameModel::actionByPerson(int row, int col)
{
    updateGameMap(row, col);
}

void GameModel::updateGameMap(int row, int col)
{
    if (playerFlag)
        gameMapVec[row][col] = 1;
    else
        gameMapVec[row][col] = -1;

    //换手
    playerFlag = !playerFlag;
}
