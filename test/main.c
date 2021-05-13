#define CTEST_MAIN

#include <ctest.h>
#include <libchessviz/libmain.h>

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
/*
CTEST(is_valid_string, test1)
{
	char field[8][8];
	char color[8][8];
	start_game(field, color);

	char str[5];
	str[0] = 'a';
	str[1] = '2';
	str[2] = '-';
	str[3] = 'a';
	str[4] = '3';

	ASSERT_EQUAL(1, is_valid_string(&str, color));
}
*/

