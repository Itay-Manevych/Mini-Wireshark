#include <iostream>
#include <unistd.h>
#include "PacketCapture.h"

int main() 
{
    PacketCapture capture("eth0");
    capture.StartCapture();
    std::cout << "Hello" << std::endl;
    sleep(3);
    capture.StopCapture();
    return 0;
}