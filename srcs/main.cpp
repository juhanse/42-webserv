#include "../webserv.h"

int main(int ac, char **av) {
    if (ac != 2) {
        std::cout << "Bad arguments: [./webserv [configuration file]]" << std::endl;
        return (1);
    }

    std::cout << av[1] << std::endl;

    return (0);
}
