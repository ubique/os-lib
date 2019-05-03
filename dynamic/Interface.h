#pragma once

#include <string>
#include <cstring>

std::string pluginListCommand();

std::string runCommand();

std::string selectPluginCommand();

std::string symbolListCommand();

std::string exitCommand();

std::string pluginListMessage(size_t listSize);

std::string symbolListMessage(size_t listSize);

std::string resultMessage();

std::string errorMessage();

std::string runMessage();

std::string selectMessage();

std::string greet(std::string const &plugin);

std::string pluginNotFoundError(const std::string &plugin);

std::string openPluginsDirError(error_t error, const std::string &dirName);

std::string dlopenError(const std::string &plugin, const std::string &message);

std::string dlsymError(const std::string &plugin,
                       const std::string &symbol,
                       const std::string &message);

std::string commandNotFound(const std::string& command);

std::string pluginNotSelectedError();