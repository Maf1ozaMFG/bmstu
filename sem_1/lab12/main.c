#include "mylib.h"

int main() {
    char* filePath = getFilePath();
    if (filePath) {
        printInvitation();
        int command;
        command = getCommand();
        while (command != EXIT) {
            executeSelectedCommand(filePath, command);
            printInvitation();
            command = getCommand();
        }
    }
}

//         /Users/626/Downloads/lab12/catalog.txt
