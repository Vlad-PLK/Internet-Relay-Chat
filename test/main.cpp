#include <iostream>
#include <cstring> // Include the header for memset

int main() {
    char buffer[512];

    std::cout << "Testing memset(buffer, 0, 0);" << std::endl;
    buffer[0] = 'd';
    buffer[1] = 'd';
    buffer[2] = 'd';
    buffer[3] = 'd';
    memset(buffer, 0, 0);
    if (buffer[0] == '\0') {
        std::cout << "Buffer is empty after memset(buffer, 0, 0);" << std::endl;
    } else {
        std::cout << "Buffer is not empty after memset(buffer, 0, 0);" << std::endl;
    }

    std::cout << "Testing memset(buffer, 0, sizeof(buffer));" << std::endl;
    buffer[0] = 'd';
    buffer[1] = 'd';
    buffer[2] = 'd';
    buffer[3] = 'd';
    memset(buffer, 0, sizeof(buffer));
    if (buffer[0] == '\0') {
        std::cout << "Buffer is empty after memset(buffer, 0, sizeof(buffer));" << std::endl;
    } else {
        std::cout << "Buffer is not empty after memset(buffer, 0, sizeof(buffer));" << std::endl;
    }

    return 0;
}
