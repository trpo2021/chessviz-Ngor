#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

void start_game(char field[8][8], char color[8][8]);
void draw_game(char field[8][8], char color[8][8]);
string check_result(char field[8][8], char color[8][8]);
bool is_pawn(char c);
bool is_figure(char c);
bool is_ah(char c);
bool is_18(char c);
int is_valid_string(string& s, char color[8][8]);
bool is_correct_move(
        string s,
        char c,
        char field[8][8],
        char color[8][8]); // bool w_cast, bool b_cast
char get_enemy(char c);
vector<pair<int, int>>
attacks(int I, int J, char field[8][8], char color[8][8]);
bool king_check(char c, char field[8][8], char color[8][8]);
bool try_long_castling(
        char c, char field[8][8], char color[8][8], bool w_cast, bool b_cast);
bool try_short_castling(
        char c, char field[8][8], char color[8][8], bool w_cast, bool b_cast);

const string IN_PROGRESS = "in progress";
const string WIN_WHITE = "win_white";
const string WIN_BLACK = "win_black";
const string DRAW = "draw";