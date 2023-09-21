#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <string>
#include "Matrix.h"

using namespace std;

class TicTacToe
{
public:
    TicTacToe();
    void play();

private:
    string playerNames[2];
    Matrix<string> board;
    string currentPlayer;

    bool wantsToQuit();
    bool wantsToSave();
    void printBoard();
    bool checkWin();
    bool checkDraw();
    bool saveGame(const string &fileName);
    bool loadGame(const string &fileName);
};

#endif