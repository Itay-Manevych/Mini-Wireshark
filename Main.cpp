#include <iostream>
#include <unistd.h>
#include "PacketCapture.h"

int main() 
{
    PacketCapture capture("eth0");
    std::cout << "Hello";
    while (true) {
        sleep(1);
    }
    return 0;
}