//
// Created by dumpling on 30.04.19.
//

#include <iostream>
#include "snake.h"

void shift(int cnt, char direction) {
    std::cout << "\033[" << cnt << direction << std::flush;
}

void up(int cnt) {
    shift(cnt, 'A');
}

void down(int cnt) {
    shift(cnt, 'B');
}

void right(int cnt) {
    shift(cnt, 'C');
}

void left(int cnt) {
    shift(cnt, 'D');
}

void print_food() {
    std::cout << "\033[1;33m" << "*" << "\033[0m" << std::flush;
}

void print_snake() {
    std::cout << "\033[1;32m" << "*" << "\033[0m" << std::flush;
}

void fix_element(int max_y, int x, int y, void(*printer)()) {
    up(max_y + 1 - y);
    right(x);
    printer();
    down(max_y + 1 - y);
    left(x + 1);
}

Snake make_world(int max_x, int max_y) {

    Snake snake(max_x, max_y);

    for (int i = 0; i <= max_y; ++i) {
        for (int j = 0; j <= max_x * 2; ++j) {
            if (Snake::Pos{j, i} == snake.where_food()) {
                print_food();
                continue;
            }

            if (snake.is_snake({j, i})) {
                print_snake();
                continue;
            }

            if ((i == 0 || j == 0 || j == max_x * 2 || i == max_y) && (j % 2 == 0)) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    return snake;
}

bool game_logic(Snake &snake) {
    if (snake.is_hungry()) {
        auto e = snake.pop_last();
        fix_element(snake.get_max_y(), e.x, e.y, [] { std::cout << ' ' << std::flush; });
    }

    snake.make_hungry();

    auto h = snake.back();
    if (snake.get_direction() == Snake::Direction::UP) {
        --h.y;
    }

    if (snake.get_direction() == Snake::Direction::DOWN) {
        ++h.y;
    }

    if (snake.get_direction() == Snake::Direction::RIGHT) {
        h.x += 2;
    }

    if (snake.get_direction() == Snake::Direction::LEFT) {
        h.x -= 2;
    }

    if (h.x <= 0 || h.x >= snake.get_max_x() * 2 || h.y <= 0 || h.y >= snake.get_max_y()) {
        return true;
    }

    if (!snake.add(h)) {
        return true;
    }

    if (Snake::Pos{h.x, h.y} == snake.where_food()) {
        snake.make_full();

        snake.gen_food();
        auto food = snake.where_food();
        fix_element(snake.get_max_y(), food.x, food.y, &print_food);

    }

    fix_element(snake.get_max_y(), h.x, h.y, &print_snake);

    return false;
}
