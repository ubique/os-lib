#include "Interface.h"


/* Commands */
std::string pluginListCommand() {
    return "lsp";
}

std::string runCommand() {
    return "run";
}

std::string selectPluginCommand() {
    return "sel";
}

std::string symbolListCommand() {
    return "lss";
}

std::string exitCommand() {
    return "exit";
}




/* Messages */
std::string pluginListMessage(size_t listSize) {
    return "Found " + std::to_string(listSize) + " plugins:";
}

std::string symbolListMessage(size_t listSize) {
    return "Found " + std::to_string(listSize) + " symbols:";
}

std::string errorMessage() {
    return "Error: \n";
}

std::string greet() {
    return "$ ";
}

std::string runMessage() {
    return "Argument: ";
}

std::string selectMessage() {
    return "Plugin selected.";
}

std::string resultMessage() {
    return "Result: ";
}



/* Errors */
std::string pluginNotFoundError(std::string const &plugin) {
    return "Plugin " + plugin + " not found.";
}

std::string openPluginsDirError(error_t error, const std::string& dirName) {
    std::string errorStr = strerror(error);
    return "Cannot open plugins directory \'" + dirName + "\':\n" + errorStr;
}

std::string dlopenError(const std::string &plugin, const std::string &message) {
    return "Error during opening plugin \'" + plugin + "\'.\n" + message;
}

std::string dlsymError(const std::string &plugin, const std::string &symbol, const std::string &message) {
    return "Symbol \'" + symbol + "\' not found in plugin \'" + plugin + "\'.\n" + message;
}