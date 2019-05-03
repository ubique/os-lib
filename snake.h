//
// Created by dumpling on 30.04.19.
//

#ifndef LIB_SNAKE_H
#define LIB_SNAKE_H

#include <queue>
#include <set>
#include <random>

struct Snake {

    Snake(int max_x, int max_y) : direction(Direction::RIGHT),
                                  max_x(max_x), max_y(max_y),
                                  full(false),
                                  rg(max_x, max_y) {
        int st_x = rg.get_random_x();
        int st_y = rg.get_random_y();

        while (st_x < 3 && st_x > max_x - 3) {
            st_x = rg.get_random_x();
        }

        while (st_y < 3 && st_y > max_y - 3) {
            st_y = rg.get_random_y();
        }

        add({st_x, st_y});
        add({st_x - 2, st_y});

        gen_food();
    }

    Snake(const Snake &other) : snake_pos(other.snake_pos),
                                snake_set_pos(other.snake_set_pos),
                                direction(other.direction),
                                max_x(other.max_x),
                                max_y(other.max_y),
                                full(other.full),
                                food(other.food),
                                rg(max_x, max_y) {}

    struct Pos {
        int x, y;

        bool operator<(const Pos &other) const {
            return x < other.x || (x == other.x && y < other.y);
        }

        bool operator==(const Pos &other) const {
            return x == other.x && y == other.y;
        }
    };

    struct Random_generator {

        Random_generator(int max_x, int max_y) : gen(rd()), x_dis(1, max_x - 1), y_dis(1, max_y - 1) {}

        int get_random_x() {
            return x_dis(gen) * 2;
        }

        int get_random_y() {
            return y_dis(gen);
        }

    private:
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_int_distribution<int> x_dis, y_dis;
    };

    enum class Direction {
        LEFT, RIGHT, UP, DOWN
    };

    void set_direction(Direction d) {
        direction = d;
    }

    Pos pop_last() {
        auto e = snake_pos.front();
        snake_pos.pop();
        snake_set_pos.erase(e);
        return e;
    }

    Pos back() {
        return snake_pos.back();
    }

    bool add(Pos p) {
        if (is_snake(p)) {
            return false;
        }

        snake_pos.push(p);
        snake_set_pos.insert(p);

        return true;
    }

    void gen_food() {
        int x = rg.get_random_x();
        int y = rg.get_random_y();

        while (snake_set_pos.count({x, y}) > 0) {
            x = rg.get_random_x();
            y = rg.get_random_y();
        }

        food = {x, y};
    }

    Pos where_food() {
        return food;
    }

    bool is_snake(Pos pos) {
        return snake_set_pos.count(pos) > 0;
    }

    bool is_hungry() {
        return !full;
    }

    void make_hungry() {
        full = false;
    }

    void make_full() {
        full = true;
    }

    Direction get_direction() {
        return direction;
    }

    int get_max_x() {
        return max_x;
    }

    int get_max_y() {
        return max_y;
    }

    int get_length() {
        return snake_set_pos.size();
    }

private:
    std::queue<Pos> snake_pos;
    std::set<Pos> snake_set_pos;

    Direction direction;
    int max_x;
    int max_y;
    bool full;
    Pos food{};

    Random_generator rg;
};

#endif //LIB_SNAKE_H
