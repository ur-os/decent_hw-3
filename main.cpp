#include "shared_scheme.h"

int main(int argc, char *argv[]) {
    switch (parameter_processing(argv[1])) {
        case WRONG_ARGUMENTS:
            std::cout << "Please, start program in format:\n\t./program_name [split|recover]";
            break;

        case SPLIT:
            split();
            break;

        case RECOVER:
            recover();
            break;

        default:
            std::cout << "¯\\_(ツ)_/¯";
    }
    return 0;
}
