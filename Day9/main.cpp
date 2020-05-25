#include <iostream>
// #include <string>

std::string read() {
    return "World";
}

int main(int argc, char * argv[])
{
    std::cout << "Hello " << read() << std::endl;
}