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
void move(
        string s,
        char field[8][8],
        char color[8][8]); // bool w_cast, bool b_cast