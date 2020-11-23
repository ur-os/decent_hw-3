#include "shared_scheme.h"

int main(const int argc, const char *argv[]) {
    if((std::string)argv[1] == "split") {
        split();
        return 0;
    }

    if((std::string)argv[1] == "recover"){
        recover();
        return 0;
    }

    std::cout << " ¯\\_(ツ)_/¯ Please, start program in format:\n\t./program_name [split|recover] ";
    return -1;
}
