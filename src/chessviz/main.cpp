#include <libchessviz/libmain.h>

using namespace std;

int main()
{
    vector<string> str;

    char field[8][8];

    char color[8][8];

    freopen("movements.txt", "r", stdin);
    string s;
    while (cin >> s) {
        str.push_back(s);
    }
    fclose(stdin);

    start_game(field, color);
    draw_game(field, color);

    for (size_t i = 0; i < str.size(); i++) {
        int valid = is_valid_string(str[i], color);
        if (valid) {
            move(str[i], field, color);
            draw_game(field, color);
        } else {
            cout << "ERROR: <Invalid input data> : " << str[i].substr(1)
                 << endl;
            break;
        }
    }

    return 0;
}
