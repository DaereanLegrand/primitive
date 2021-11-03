#include <stdio.h>
#include <stdlib.h>
#include <NTL/ZZ.h>
#include <iostream>

using NTL::ZZ;

ZZ
moduloZZ(ZZ a, ZZ b) 
{
    ZZ res = a - ((a / b) * b);
    return res + (res < 0) * b;
}

ZZ powmod(ZZ a, ZZ b, ZZ N)
{
    ZZ cumulativeExponent, newB, nMod, lastSquare, lastExponent, otherSquare, two;
    cumulativeExponent = 1;
    newB = b;
    lastSquare = a;
    lastExponent = 0;
    otherSquare = 1;
    two = 2;
    do
    {
        nMod = moduloZZ(newB, two);
        if (cumulativeExponent != 1) lastSquare = moduloZZ(lastSquare * lastSquare, N);
        if (nMod == 1)
        {
            lastExponent = lastExponent + cumulativeExponent;
            otherSquare = moduloZZ(lastSquare * otherSquare, N);
        }
        newB = newB / 2;
        cumulativeExponent = cumulativeExponent * 2;
    }
    while (newB > 0);
    return otherSquare;
}

ZZ
primitive(ZZ num)
{
    for (ZZ i(2); i < num; i++) {
        ZZ j (1);
        for (; j < num; j++) {
            ZZ tempres = powmod(i, j, num);
            std::cout << i << " ^ " << j << " mod " << num << " = "<< tempres << "\n";
            if (tempres == 1) {
                return i;
            }
        }
        if (j == num - 2) {
            return i;
        }
    }
    return ZZ(-1);
}

int
main (int argc, char* argv[])
{
    if (argc == 2) {
        int number = 0;
        for (char* i = argv[1]; *i != '\0'; i++)
            if (*i < '0' || *i > '9') {
                puts("Not a number!");
                break;
            } else {
                if (i != argv[1]) number *= 10;
                number += *i - '0';
            }
        std::cout << "The primitive is:" << primitive(ZZ(number));
    } else {
        std::cout << powmod(ZZ(2), ZZ(25012), ZZ(100049));
    }
    return 0;
}
