#pragma once


#include <string>
#include <vector>


struct ApplicationException : std::exception {
    std::string message;

    explicit ApplicationException(std::string message);

    const char *what() const noexcept override;
};


class Application {
public:
    Application(int argc, char *argv[]);

    int run();

private:

    std::vector<std::string> getPluginList();

    std::vector<std::string> getSymbolList(const std::string& plugin);

    void runPluginFunc(const std::string& pluginName, const std::string& pluginFunc);

    void procPluginList();

    void procRun();

    void procSelect();

    void procSymbolList();

    std::string selectedPlugin;
    std::string pluginDir;
};
