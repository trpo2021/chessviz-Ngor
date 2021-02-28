#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

void start_game();
void draw_game();
void check_result();
vector<string> split_by_char(string s, char c);
bool is_pawn(char c);
bool is_figure(char c);
bool is_ah(char c);
bool is_18(char c);
int is_valid_string(string& s);
bool is_correct_move(string s, char c);
char get_enemy(char c);
vector<pair<int, int>> attacks(int I, int J);
bool king_check(char c);
bool try_long_castling(char c);
bool try_short_castling(char c);

char field[8][8];

char color[8][8];

string state;

const string IN_PROGRESS = "in progress";
const string WIN_WHITE = "win_white";
const string WIN_BLACK = "win_black";
const string DRAW = "draw";

vector<string> str;

bool w_cast, b_cast;

void start_game() {
	state = IN_PROGRESS;
	w_cast = b_cast = true;

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

void draw_game() {
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

void check_result() {
	if (king_check('w')) {
		state = WIN_BLACK;
	}
	else if (king_check('b')) {
		state = WIN_WHITE;
	}
	state = DRAW;
}

vector<string> split_by_char(string s, char c) {
	vector<string> result;
	string buff;
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] != 'c') {
			buff += s[i];
		}
		else if (buff.size()) {
			result.push_back(buff);
			buff = "";
		}
	}
	if (buff.size()) {
		result.push_back(buff);
	}
	return result;
}

bool is_pawn(char c) {
	return (c == 'w' || c == 'b');
}

bool is_figure(char c) {
	return (c == 'R' || c == 'N' || c == 'B' || c == 'Q' || c == 'K' || c == 'w' || c == 'b');
}

bool is_ah(char c) {
	return (c >= 'a' && c <= 'h');
}

bool is_18(char c) {
	return (c >= '1' && c <= '8');
}

int is_valid_string(string& s) {
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
		}
		else {
			s = "*" + s;
		}
	}

	return ((is_figure(s[0]) && is_ah(s[1]) && is_18(s[2]) && s[3] == '-' && is_ah(s[4]) && is_18(s[5])) ? 1 : 0);
}

bool is_correct_move(string s, char c) {
	char f = s[0];
	int c1 = s[1] - 'a', r1 = s[2] - '1', c2 = s[4] - 'a', r2 = s[5] - '1';


	if (color[r1][c1] != c || field[r1][c1] != f || color[r2][c2] == c || (is_pawn(f) && c1 == c2 && color[r2][c2] != '*')) {
		return false;
	}

	vector<pair<int, int>> allow = attacks(r1, c1);
	bool ok = false;
	for (size_t i = 0; i < allow.size(); i++) {
		if (allow[i].first == r2 && allow[i].second == c2) {
			ok = true;
		}
	}

	if (f == 'w') {
		if (r2 == r1 + 1) {
			if (c2 == c1 - 1 && field[r2][c2] == get_enemy(c)) {
				// ok
			}
			else if (c2 == c1) {
				// ok
			}
			else if (c2 == c1 + 1 && field[r2][c2] == get_enemy(c)) {
				// ok
			}
			else {
				return false;
			}
		}
		else if (r2 == r1 + 2 && c1 == c2 && r1 == 1) {
			// ok
		}
		else {
			return false;
		}
	}
	else if (f == 'b') {
		if (r2 == r1 - 1) {
			if (c2 == c1 - 1 && field[r2][c2] == get_enemy(c)) {
				// ok
			}
			else if (c2 == c1) {
				// ok
			}
			else if (c2 == c1 + 1 && field[r2][c2] == get_enemy(c)) {
				// ok
			}
			else {
				return false;
			}
		}
		else if (r2 == r1 - 2 && c1 == c2 && r1 == 6) {
			// ok
		}
		else {
			return false;
		}
	}
	else if (!ok) {
		return false;
	}

	if (f == 'K') {
		if (c == 'w') {
			w_cast = false;
		}
		else {
			b_cast = false;
		}
	}

	color[r1][c1] = field[r1][c1] = '*';
	field[r2][c2] = f;
	color[r2][c2] = c;

	return !king_check(c);
}

char get_enemy(char c) {
	return (c == 'w' ? 'b' : 'w');
}

vector<pair<int, int>> attacks(int I, int J) {
	vector<pair<int, int>> result;
	if (field[I][J] == '*') {
		return result;
	}

	char c = color[I][J];
	char enemy = get_enemy(c);
	int di[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	int dj[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	int di2[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
	int dj2[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

	if (field[I][J] == c) {
		if (c == 'w') {
			if (I + 1 <= 7 && J - 1 >= 0 && color[I + 1][J - 1] == enemy) {
				result.push_back({ I + 1, J - 1 });
			}
			if (I + 1 <= 7 && J + 1 <= 7 && color[I + 1][J + 1] == enemy) {
				result.push_back({ I + 1, J + 1 });
			}
		}
		else {
			if (I - 1 <= 7 && J - 1 >= 0 && color[I - 1][J - 1] == enemy) {
				result.push_back({ I - 1, J - 1 });
			}
			if (I - 1 <= 7 && J + 1 <= 7 && color[I - 1][J + 1] == enemy) {
				result.push_back({ I - 1, J + 1 });
			}
		}
	}
	else if (field[I][J] == 'R') {
		for (int k = 0; k < 8; k += 2) {
			int ii = I + di[k], jj = J + dj[k];
			while (ii >= 0 && ii <= 7 && jj >= 0 && jj <= 7 && color[ii][jj] != c) {
				result.push_back({ ii, jj });
				if (color[ii][jj] == get_enemy(c)) {
					break;
				}
				ii += di[k];
				jj += dj[k];
			}
		}
	}
	else if (field[I][J] == 'N') {
		for (int k = 0; k < 8; k++) {
			int ii = I + di2[k], jj = J + dj2[k];
			if (color[ii][jj] != c) {
				result.push_back({ ii, jj });
			}
		}
	}
	else if (field[I][J] == 'B') {
		for (int k = 1; k < 8; k += 2) {
			int ii = I + di[k], jj = J + dj[k];
			while (ii >= 0 && ii <= 7 && jj >= 0 && jj <= 7 && color[ii][jj] != c) {
				result.push_back({ ii, jj });
				if (color[ii][jj] == get_enemy(c)) {
					break;
				}
				ii += di[k];
				jj += dj[k];
			}
		}
	}
	else if (field[I][J] == 'Q') {
		for (int k = 0; k < 8; k++) {
			int ii = I + di[k], jj = J + dj[k];
			while (ii >= 0 && ii <= 7 && jj >= 0 && jj <= 7 && color[ii][jj] != c) {
				result.push_back({ ii, jj });
				if (color[ii][jj] == get_enemy(c)) {
					break;
				}
				ii += di[k];
				jj += dj[k];
			}
		}
	}
	else if (field[I][J] == 'K') {
		for (int k = 0; k < 8; k++) {
			int ii = I + di[k], jj = J + dj[k];
			if (color[ii][jj] != c) {
				result.push_back({ ii, jj });
			}
		}
	}

	return result;
}

bool king_check(char c) {
	int I = 0, J = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (color[i][j] == c && field[i][j] == 'K') {
				I = i;
				J = j;
			}
		}
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (color[i][j] == get_enemy(c)) {
				vector<pair<int, int>> attack = attacks(i, j);
				for (size_t k = 0; k < attack.size(); k++) {
					if (attack[k].first == I && attack[k].second == J) {
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool try_short_castling(char c) {
	if (king_check(c) || (c == 'w' && !w_cast) || (c == 'b' && !b_cast)) {
		return false;
	}

	if (c == 'w') {
		w_cast = false;
	}
	else {
		b_cast = false;
	}

	int I = (c == 'w' ? 0 : 7);
	if (field[I][7] == 'R' && color[I][7] == c && field[I][6] == '*' && field[I][5] == '*') {
		color[I][7] = color[I][4] = field[I][7] = field[I][4] = '*';
		color[I][6] = color[I][5] = c;
		field[I][6] = 'K';
		field[I][5] = 'R';
		return true;
	}
	return false;
}

bool try_long_castling(char c) {
	if (king_check(c) || (c == 'w' && !w_cast) || (c == 'b' && !b_cast)) {
		return false;
	}

	if (c == 'w') {
		w_cast = false;
	}
	else {
		b_cast = false;
	}

	int I = (c == 'w' ? 0 : 7);
	if (field[I][0] == 'R' && color[I][0] == c && field[I][1] == '*' && field[I][2] == '*' && field[I][3] == '*') {
		color[I][0] = color[I][4] = field[I][0] = field[I][4] = '*';
		color[I][2] = color[I][3] = c;
		field[I][2] = 'K';
		field[I][3] = 'R';
		return true;
	}
	return false;
}

int main() {
	freopen("movements.txt", "r", stdin);
	string s;
	while (cin >> s) {
		str.push_back(s);
	}
	fclose(stdin);

	start_game();
	draw_game();

	char md = 'w';
	for (size_t i = 0; i < str.size(); i++)
	{
		int valid = is_valid_string(str[i]);
		if (valid) {
			if (valid == 1 && is_correct_move(str[i], md)) {
				draw_game();
			}
			else if (valid == 2 && try_short_castling(md)) {
				draw_game();
			}
			else if (valid == 3 && try_long_castling(md)) {
				draw_game();
			}
			else {
				cout << "ERROR: <Invalid movement> : " << str[i].substr(1) << endl;
				break;
			}
		}
		else {
			cout << "ERROR: <Invalid input data> : " << str[i].substr(1) << endl;
			break;
		}
		if (i == str.size() - 1) {
			check_result();
			cout << "End of game. Result of game : " << state << endl;
		}
		md = get_enemy(md);
	}

	system("pause");
	return 0;
}
