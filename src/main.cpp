#include <iostream>
#include <string>
#include <sstream>

#include <dlfcn.h>


using namespace std;

void printMessage();

void printMul(int, int);

const string startLine = ">> ";

const string greetingMessage = "Library homework by Baykalov Vladimir. Group M3234.\n"
                               "Write \'Help\' to get all commands.\n";

const string helpMessage = "\'Help\' - shows all commands\n"
                           "\'GetStaticCompileFunc\' - invokes function from static lib.\n"
                           "\'GetSharedCompileFunc\' <args...> - invokes function from shared compile lib.\n"
                           "\'GetSharedRuntimeLib\' <path_to_library> - connects shared library\n"
                           "\'GetSharedRuntimeFunc\' <function_name> <args...>- if library has already connected "
                           "then executes function from shared library\n"
                           "\'Status\' - show info about connected library and function\n"
                           "Hint: path to library: \'./build/libsharedRuntime.so\'\n"
                           "function signature: \'void printSum(int, int);\'\n"
                           "\'Exit\' - terminates the program\n";

const string terminateMessage = "Terminate program.\n";

const string unknownCommandMessage = "Unknown command. Write \'Help\' to see all commands\n";


int main() {
    void *sharedLibrary = nullptr;
    void (*functionPtr)(int, int) = nullptr;

    cout << greetingMessage;

    string lineCommand;

    cout << startLine;
    while (getline(cin, lineCommand)) {
        if (lineCommand.empty()) {
            if (sharedLibrary) {
                dlclose(sharedLibrary);
            }

            cout << terminateMessage;
            exit(EXIT_SUCCESS);
        }

        stringstream stringStream;
        stringStream << lineCommand;

        string mainCommand;
        stringStream >> mainCommand;


        if (mainCommand == "Help") {
            cout << helpMessage;

            cout << startLine;
            continue;
        }


        if (mainCommand == "GetStaticCompileFunc") {
            printMessage();

            cout << startLine;
            continue;
        }


        if (mainCommand == "GetSharedCompileFunc") {
            int first = 0, second = 0;
            stringStream >> first >> second;

            printMul(first, second);

            cout << startLine;
            continue;
        }


        if (mainCommand == "Status") {
            if (sharedLibrary == nullptr) {
                cout << "Library isn\'t connected" << endl;
            } else {
                cout << "Library is connected" << endl;
            }

            if (functionPtr == nullptr) {
                cout << "Function isn\'t found" << endl;
            } else {
                cout << "Function is connected" << endl;
            }

            cout << startLine;
            continue;
        }


        if (mainCommand == "GetSharedRuntimeLib") {
            if (stringStream.eof()) {
                cout << unknownCommandMessage;
                cout << startLine;
                continue;
            }

            string pathToLib;
            stringStream >> pathToLib;

            sharedLibrary = dlopen(pathToLib.c_str(), RTLD_LAZY);

            if (sharedLibrary == nullptr) {
                cerr << "Error connecting library";
                cerr << "Error message: " << dlerror() << endl;

                cout << startLine;
                continue;
            }

            dlerror();

            cout << startLine;
            continue;
        }


        if (mainCommand == "GetSharedRuntimeFunc") {
            if (stringStream.eof()) {
                cout << unknownCommandMessage;

                cout << startLine;
                continue;
            }

            if (!sharedLibrary) {
                cout << "Shared library isn't connected.\nConnect library and try again.\n";

                cout << startLine;
                continue;
            }

            string functionName;
            int first = 0, second = 0;
            stringStream >> functionName >> first >> second;

            functionPtr = reinterpret_cast<void (*)(int, int)>(dlsym(sharedLibrary, functionName.c_str()));

            if (functionPtr == nullptr) {
                cerr << "Error finding shared library function." << endl;
                cerr << "Error message: " << dlerror() << endl;

                cout << startLine;
                continue;
            }

            dlerror();

            functionPtr(first, second);

            cout << startLine;
            continue;
        }


        if (mainCommand == "Exit") {
            if (sharedLibrary) {
                dlclose(sharedLibrary);
            }

            cout << terminateMessage;
            exit(EXIT_SUCCESS);
        }


        cerr << unknownCommandMessage;
        cout << startLine;
    }

    if (sharedLibrary) {
        dlclose(sharedLibrary);
    }

    return 0;
}