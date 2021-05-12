#include <libchessviz/libmain.h>

using namespace std;

void start_game(char field[8][8], char color[8][8])
{
    for (int i = 2; i <= 5; i++) {
        for (int j = 0; j <= 7; j++) {
            color[i][j] = field[i][j] = '*';
        }
    }
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 7; j++) {
            color[i][j] = 'w';
            color[7 - i][j] = 'b';
        }
    }
    for (int j = 0; j <= 7; j++) {
        field[1][j] = 'w';
        field[6][j] = 'b';
    }

    field[0][0] = field[0][7] = field[7][0] = field[7][7] = 'R';
    field[0][1] = field[0][6] = field[7][1] = field[7][6] = 'N';
    field[0][2] = field[0][5] = field[7][2] = field[7][5] = 'B';
    field[0][3] = field[7][3] = 'Q';
    field[0][4] = field[7][4] = 'K';
}

void draw_game(char field[8][8], char color[8][8])
{
    for (int i = 7; i >= 0; i--) {
        cout << (i + 1);
        for (int j = 0; j <= 7; j++) {
            cout << " " << color[i][j] << field[i][j] << " ";
        }
        cout << endl;
    }
    cout << "   a   b   c   d   e   f   g   h" << endl;
    cout << endl;
}

bool is_pawn(char c)
{
    return (c == 'w' || c == 'b');
}

bool is_figure(char c)
{
    return (c == 'R' || c == 'N' || c == 'B' || c == 'Q' || c == 'K' || c == 'w'
            || c == 'b');
}

bool is_ah(char c)
{
    return (c >= 'a' && c <= 'h');
}

bool is_18(char c)
{
    return (c >= '1' && c <= '8');
}

int is_valid_string(string& s, char color[8][8])
{
    if (s == "0-0") {
        return 2;
    }
    if (s == "0-0-0") {
        return 3;
    }

    if (s.size() < 5 || s.size() > 6) {
        return 0;
    }

    if (s.size() == 5) {
        if (is_ah(s[0]) && is_18(s[1])) {
            s = color[s[1] - '1'][s[0] - 'a'] + s;
        } else {
            s = "*" + s;
        }
    }

    return ((is_figure(s[0]) && is_ah(s[1]) && is_18(s[2]) && s[3] == '-'
             && is_ah(s[4]) && is_18(s[5]))
                    ? 1
                    : 0);
}

void move(string s, char field[8][8], char color[8][8])
// bool w_cast, bool b_cast
{
    //char f = s[0];
    int c1 = s[1] - 'a', r1 = s[2] - '1', c2 = s[4] - 'a', r2 = s[5] - '1';

    
    field[r2][c2] = field[r1][c1];
    color[r2][c2] = color[r1][c1];
    color[r1][c1] = field[r1][c1] = '*';

    return;
}

