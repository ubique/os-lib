//
// Created by dumpling on 30.04.19.
//

const int SUPER_SMALL_MAX_X = 20;
const int SUPER_SMALL_MAX_Y = 10;
const int SMALL_MAX_X = 30;
const int SMALL_MAX_Y = 20;
const int MEDIUM_MAX_X = 40;
const int MEDIUM_MAX_Y = 30;
const int BIG_MAX_X = 50;
const int BIG_MAX_Y = 40;

void make_super_small(int &max_x, int &max_y) {
    max_x = SUPER_SMALL_MAX_X;
    max_y = SUPER_SMALL_MAX_Y;
}

void make_small(int &max_x, int &max_y) {
    max_x = SMALL_MAX_X;
    max_y = SMALL_MAX_Y;
}

void make_medium(int &max_x, int &max_y) {
    max_x = MEDIUM_MAX_X;
    max_y = MEDIUM_MAX_Y;
}

void make_big(int &max_x, int &max_y) {
    max_x = BIG_MAX_X;
    max_y = BIG_MAX_Y;
}