#include <iostream>
#include <string>

#include <dlfcn.h>

#include "calc.h"

using fpCalc = int (*)(int, int);
using fpPrint = void (*)(int);
using fpVoid = void (*)();
//typedef int (*fpCalc)(int, int);
//typedef void (*fpPrint)(int);

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <num1> <num2>" << std::endl;
        return 1;
    }
    int a = std::stoi(argv[1]);
    int b = std::stoi(argv[2]);

    void* handle = dlopen("./libmycalc.so", RTLD_LAZY);
    if (!handle) {
        std::cerr << "Cannot open library: " << dlerror() << std::endl;
        return 1;
    }

    fpCalc add = (fpCalc) dlsym(handle, "myadd");
    fpCalc sub = (fpCalc) dlsym(handle, "mysub");
    fpCalc mul = (fpCalc) dlsym(handle, "mymul");
    fpCalc div = (fpCalc) dlsym(handle, "mydiv");
    fpPrint print = (fpPrint) dlsym(handle, "printnum");

    if (!add || !sub || !mul || !div || !print) {
        std::cerr << "Cannot load symbol: " << dlerror() << std::endl;
        return 1;
    }

    fpVoid hiddenfunc = (fpVoid) dlsym(handle, "hiddenfunc");
    if (!hiddenfunc) {
        std::cout << "Hidden function is hidden: " << dlerror() << std::endl;
    }

    print(a);
    print(b);
    std::cout << "a + b = " << add(a, b) << std::endl;
    std::cout << "a - b = " << sub(a, b) << std::endl;
    std::cout << "a * b = " << mul(a, b) << std::endl;
    std::cout << "a / b = " << div(a, b) << std::endl;
    
    dlclose(handle);

    return 0;
}