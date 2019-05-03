//
// Created by dumpling on 30.04.19.
//

#include <iostream>
#include <dlfcn.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <chrono>
#include <thread>

#include "snake.h"

void make_super_small(int &max_x, int &max_y);

void make_small(int &max_x, int &max_y);

void make_medium(int &max_x, int &max_y);

void make_big(int &max_x, int &max_y);

Snake make_world(int max_x, int max_y);

bool game_logic(Snake &snake);

void print_err(std::string message) {
    std::cerr << "\033[31m" << message << "\033[0m" << std::endl;
}

void print_dll_err() {
    print_err(dlerror());
}

void sleep_millisec(int x) {
    std::this_thread::sleep_for(std::chrono::milliseconds(x));
}

struct Echo_disable {

    Echo_disable() {
        tcgetattr(0, &def);
        dis = def;
        dis.c_lflag &= ~ICANON & ~ECHO;
        tcsetattr(0, TCSANOW, &dis);
        setbuf(stdin, NULL);
    }

    int clicked() {
        int left;
        ioctl(0, FIONREAD, &left);

        return left;
    }

    ~Echo_disable() {
        tcsetattr(0, TCSANOW, &def);
    }

private:
    termios def, dis;
};

struct Dll_connector {

    Dll_connector() : handle(dlopen("./libsecond_shared.so", RTLD_LAZY)), correct_handle(true) {
        if (handle == nullptr) {
            correct_handle = false;
            print_dll_err();
        }
    }

    bool ready_for_use() {
        return correct_handle;
    }

    bool execute_func(std::string func_name) {
        if (handle != nullptr) {
            auto fun = dlsym(handle, func_name.c_str());
            if (fun == nullptr) {
                print_dll_err();
                return false;
            }
            (reinterpret_cast<func_type>(fun))();
            return true;
        } else {
            return false;
        }
    }

    ~Dll_connector() {
        if (handle != nullptr) {
            if (dlclose(handle) != 0) {
                print_dll_err();
            }
        }
    }

private:
    using func_type = void (*)();

    void *handle;
    bool correct_handle;
};


int main(int argc, char **argv) {

    if (argc > 2) {
        std::cerr << "Too many arguments";
        return EXIT_FAILURE;
    }

    std::string arg;

    if (argc == 2) {
        arg = argv[1];
    }

    Dll_connector dc;
    if (!dc.ready_for_use()) {
        return EXIT_FAILURE;
    }

    int max_x, max_y;
    make_small(max_x, max_y);

    if (!arg.empty()) {
        if (arg == "-help") {
            if (!dc.execute_func("print_help")) {
                return EXIT_FAILURE;
            }

            return EXIT_SUCCESS;
        } else if (arg == "-ss") {
            make_super_small(max_x, max_y);
        } else if (arg == "-m") {
            make_medium(max_x, max_y);
        } else if (arg == "-b") {
            make_big(max_x, max_y);
        } else if (arg != "-s") {
            print_err("Incoorect argument");
            return EXIT_FAILURE;
        }
    }

    Echo_disable ed;
    Snake snake = make_world(max_x, max_y);

    auto c = getchar();
    if (c == 'q' || c == 'Q') {
        return EXIT_SUCCESS;
    }

    while (true) {
        sleep_millisec(150);
        if (ed.clicked()) {
            char c = getchar();
            if (c == 'q' || c == 'Q') {
                break;
            }

            if (c == 'p' || c == 'P') {
                while (true) {
                    c = getchar();
                    if (c == 'p' || c == 'P') {
                        break;
                    }
                }
            }

            if (snake.get_direction() == Snake::Direction::LEFT || snake.get_direction() == Snake::Direction::RIGHT) {
                if (c == 'w' || c == 'W') {
                    snake.set_direction(Snake::Direction::UP);
                }

                if (c == 's' || c == 'S') {
                    snake.set_direction(Snake::Direction::DOWN);
                }
            } else {

                if (c == 'a' || c == 'A') {
                    snake.set_direction(Snake::Direction::LEFT);
                }

                if (c == 'd' || c == 'D') {
                    snake.set_direction(Snake::Direction::RIGHT);
                }
            }
        }

        if (game_logic(snake)) {
            break;
        }
    }

    return EXIT_SUCCESS;
}

