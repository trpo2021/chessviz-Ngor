#define CTEST_MAIN

#include <ctest.h>
#include <libchessviz/libmain.h>

using namespace std;

int main(int argc, const char** argv)
{
    return ctest_main(argc, argv);
}

//////////////////////////////////////////////////////
CTEST(start_game, test1)
{
	char field[8][8];
	char color[8][8];
	start_game(field, color);

	ASSERT_EQUAL('K', field[0][4]);
	ASSERT_EQUAL('w', color[0][0]);
}


CTEST(is_pawn, test1)
{
	ASSERT_EQUAL(1, is_pawn('w'));
}

CTEST(is_figure, test1)
{
	ASSERT_EQUAL(1, is_figure('R'));
}

CTEST(is_ah, test1)
{
	ASSERT_EQUAL(1, is_ah('d'));
}

CTEST(is_18, test1)
{
	ASSERT_EQUAL(1, is_18('5'));
}

CTEST(is_valid_string, test1)
{
	char field[8][8];
	char color[8][8];
	start_game(field, color);

	vector<string> str;
	str.push_back("wa2-a3");

	ASSERT_EQUAL(1, is_valid_string(str[0], color));
}

CTEST(is_valid_string, test2)
{
	char field[8][8];
	char color[8][8];
	start_game(field, color);

	vector<string> str;
	str.push_back("Ra2-z3");

	ASSERT_EQUAL(0, is_valid_string(str[0], color));
}

CTEST(move, test1)
{
	char field[8][8];
	char color[8][8];
	start_game(field, color);

	vector<string> str;
	str.push_back("wa2-a3");

	char a = field[1][0];
	char b = color[1][0];

	move(str[0], field, color);

	ASSERT_EQUAL(a, field[2][0]);
	ASSERT_EQUAL(b, color[2][0]);
}


