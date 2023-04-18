// mycalc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>

using fpCalc = int (*)(int, int);
using fpPrint = void (*)(int);
//typedef int (*fpCalc)(int, int);
//typedef void (*fpPrint)(int);

int main()
{
    HINSTANCE hDll = LoadLibrary(L"mydll.dll");
    if (hDll == NULL) {
        std::cerr << "Error loading library\n";
        return 1;
    }

    fpCalc myadd = (fpCalc)GetProcAddress(hDll, "myadd");
    fpCalc mysub = (fpCalc)GetProcAddress(hDll, "mysub");
    fpCalc mymul = (fpCalc)GetProcAddress(hDll, "mymul");
    fpCalc mydiv = (fpCalc)GetProcAddress(hDll, "mydiv");
    fpPrint myprint = (fpPrint)GetProcAddress(hDll, "printnum");

    if (myadd == NULL) {
        std::cerr << "Error getting function address\n";
    }

    int a = 6;
    int b = 7;

    myprint(a);
    myprint(b);
    std::cout << "a + b = " << myadd(a, b) << std::endl;
    std::cout << "a - b = " << mysub(a, b) << std::endl;
    std::cout << "a * b = " << mymul(a, b) << std::endl;
    std::cout << "a / b = " << mydiv(a, b) << std::endl;

    return 0;
}
