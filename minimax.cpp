// tictactoe_minimax_no_array.cpp
#include <bits/stdc++.h>
using namespace std;

char winner(const char b[])
{
    const int L[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8},
        {0,4,8}, {2,4,6}
    };

    for (auto &l : L)
        if (b[l[0]] != ' ' && b[l[0]] == b[l[1]] && b[l[1]] == b[l[2]])
            return b[l[0]];
    return ' ';
}

bool full(const char b[])
{
    for (int i = 0; i < 9; i++)
        if (b[i] == ' ')
            return false;
    return true;
}

int minimax(char b[], bool aiTurn)
{
    char w = winner(b);
    if (w == 'X') return +10;
    if (w == 'O') return -10;
    if (full(b)) return 0;

    int best = aiTurn ? -1e9 : +1e9;
    char me = aiTurn ? 'X' : 'O';

    for (int i = 0; i < 9; i++)
        if (b[i] == ' ')
        {
            b[i] = me;                     // try move
            int val = minimax(b, !aiTurn); // recurse
            b[i] = ' ';                    // undo move

            if (aiTurn) best = max(best, val);
            else        best = min(best, val);
        }

    return best;
}

int bestMove(const char board[])
{
    char b[9];
    memcpy(b, board, 9);

    int move = -1, best = -1e9;

    for (int i = 0; i < 9; i++)
        if (b[i] == ' ')
        {
            b[i] = 'X';
            int val = minimax(b, false);
            b[i] = ' ';
            if (val > best)
            {
                best = val;
                move = i;
            }
        }

    return move;
}

void printBoard(const char b[])
{
    cout << " " << b[0] << " | " << b[1] << " | " << b[2] << "\n";
    cout << "---+---+---\n";
    cout << " " << b[3] << " | " << b[4] << " | " << b[5] << "\n";
    cout << "---+---+---\n";
    cout << " " << b[6] << " | " << b[7] << " | " << b[8] << "\n\n";
}

int main()
{
    char b[9];
    for (int i = 0; i < 9; i++) b[i] = ' ';

    bool aiTurn = true; // X starts

    while (winner(b) == ' ' && !full(b))
    {
        if (aiTurn)
        {
            int mv = bestMove(b);
            b[mv] = 'X';
        }
        else
        {
            int move = -1, best = 1e9;
            for (int i = 0; i < 9; i++)
                if (b[i] == ' ')
                {
                    b[i] = 'O';
                    int val = minimax(b, true);
                    b[i] = ' ';
                    if (val < best)
                    {
                        best = val;
                        move = i;
                    }
                }
            b[move] = 'O';
        }

        printBoard(b);
        aiTurn = !aiTurn;
    }

    char w = winner(b);
    if (w == ' ')
        cout << "Result: Draw\n";
    else
        cout << "Winner: " << w << "\n";

    return 0;
}
