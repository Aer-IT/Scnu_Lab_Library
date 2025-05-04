#include <iostream>
#include "LibrarySystem.h"

int main() {
    std::cout << "欢迎使用图书管理系统！" << std::endl;
    
    LibrarySystem system;
    system.run();
    
    return 0;
}