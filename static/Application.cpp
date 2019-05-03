#include <utility>

#include "Application.h"
#include "../dynamic/Interface.h"
#include <iostream>
#include <algorithm>
#include <libgen.h>
#include <dirent.h>
#include <dlfcn.h>


using namespace std;


ApplicationException::ApplicationException(std::string message)
        : message(std::move(message)) {}

const char *ApplicationException::what() const noexcept {
    return message.c_str();
}


Application::Application(int argc, char **argv) {
    pluginDir = dirname(argv[0]);
    if (argc == 2) {
        pluginDir += "/" + string(argv[1]);
    }
}


int Application::run() {
    string command;
    cout << greet(selectedPlugin);
    while (cin >> command) {
        try {
            if (command == pluginListCommand()) {
                procPluginList();
            } else if (command == runCommand()) {
                procRun();
            } else if (command == selectPluginCommand()) {
                procSelect();
            } else if (command == symbolListCommand()) {
                procSymbolList();
            } else if (command == exitCommand()) {
                break;
            }
        } catch (ApplicationException const &exception) {
            cerr << errorMessage() << exception.what() << endl;
        }
        cout << greet(selectedPlugin);
    }
    return 0;
}


void printList(const vector<string> &list) {
    for (auto const &elem : list) {
        cout << elem << endl;
    }
}


void Application::procPluginList() {
    auto pluginList = getPluginList();
    cout << pluginListMessage(pluginList.size()) << endl;
    printList(pluginList);
}


void Application::procRun() {
    string symbol;
    cin >> symbol;
    runPluginFunc(selectedPlugin, symbol);
}


void Application::procSelect() {
    string plugin;
    cin >> plugin;
    auto pluginList = getPluginList();
    if (find(pluginList.begin(), pluginList.end(), plugin) != pluginList.end()) {
        selectedPlugin = plugin;
        cout << selectMessage() << endl;
    } else {
        throw ApplicationException(pluginNotFoundError(plugin));
    }
}


void Application::procSymbolList() {
    auto symbolList = getSymbolList(selectedPlugin);
    cout << symbolListMessage(symbolList.size()) << endl;
    printList(symbolList);
}


std::vector<std::string> Application::getPluginList() {
    DIR *dir = opendir(pluginDir.c_str());
    if (dir == nullptr) {
        throw ApplicationException(openPluginsDirError(errno, pluginDir));
    }

    std::vector<std::string> result;

    struct dirent *dp;
    while ((dp = readdir(dir)) != nullptr) {
        string filename = dp->d_name;
        if (filename.size() > 3 && filename.substr(filename.size() - 3, 3) == ".so") {
            result.emplace_back(dp->d_name);
        }
    }

    closedir(dir);
    return result;
}


std::vector<std::string> Application::getSymbolList(const std::string &pluginName) {
    string pluginPath = pluginDir + "/" + pluginName;

    vector<string> res;
    res.emplace_back("Unimplemented feature :(");

    return res;
}

void Application::runPluginFunc(const std::string &pluginName,
                                       const std::string &pluginFunc) {
    string pluginPath = pluginDir + "/" + pluginName;

    void *handle = dlopen(pluginPath.c_str(), RTLD_LAZY);
    if (handle == nullptr) {
        throw ApplicationException(dlopenError(pluginName, dlerror()));
    }

    dlerror();

    const char* (*func)(const char*);
    func = (const char* (*)(const char*)) dlsym(handle, pluginFunc.c_str());

    auto error = dlerror();
    if (error != nullptr) {
        throw ApplicationException(dlsymError(pluginName, pluginFunc, error));
    }

    string arg;
    cout << runMessage() << endl;
    getline(cin, arg);
    getline(cin, arg);

    auto res = func(arg.c_str());

    cout << resultMessage() << endl;
    cout << res << endl;

    delete[] res;

    dlclose(handle);
}
