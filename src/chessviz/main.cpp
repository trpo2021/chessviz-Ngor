#define _CRT_SECURE_NO_WARNINGS

#include <libchessviz/libmain.h>

using namespace std;

int main()
{
    string state;

    vector<string> str;

    char field[8][8];

    char color[8][8];

    bool w_cast = true, b_cast = true;

    freopen("movements.txt", "r", stdin);
    string s;
    while (cin >> s) {
        str.push_back(s);
    }
    fclose(stdin);

               start_game(field, color);
    draw_game(field, color);

    char md = 'w';
    for (size_t i = 0; i < str.size(); i++) {
        int valid = is_valid_string(str[i], color);
        if (valid) {
            if (valid == 1
                && is_correct_move(
                        str[i], md, field, color)) { //, w_cast, b_cast
                draw_game(field, color);
            } else if (
                    valid == 2
                    && try_short_castling(md, field, color, w_cast, b_cast)) {
                draw_game(field, color);
            } else if (
                    valid == 3
                    && try_long_castling(md, field, color, w_cast, b_cast)) {
                draw_game(field, color);
            } else {
                cout << "ERROR: <Invalid movement> : " << str[i].substr(1)
                     << endl;
                break;
            }
        } else {
            cout << "ERROR: <Invalid input data> : " << str[i].substr(1)
                 << endl;
            break;
        }
        if (i == str.size() - 1) {
            state = check_result(field, color);
            cout << "End of game. Result of game : " << state << endl;
        }
        md = get_enemy(md);
    }

    return 0;
}
