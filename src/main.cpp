#include <iostream>
#include <unistd.h>
#include <csignal>
#include "tlc59711.h"

bool interrupted = false;

void handle_signal(int signum) {
    interrupted = true;
    std::cout << " Interrupted." << std::endl;
}

int main() {
    signal(SIGINT, handle_signal);

    TLC59711 tlc = TLC59711(1);
    tlc.begin();

    while (!interrupted) {
        tlc.setLED(0, 65535, 65535, 0);
        tlc.setLED(1, 65535, 65535, 0);
        tlc.setLED(2, 65535, 65535, 0);
        tlc.setLED(3, 65535, 65535, 0);

        tlc.write();
        usleep(500000);

        tlc.setLED(0, 0, 65535, 65535);
        tlc.setLED(1, 0, 65535, 65535);
        tlc.setLED(2, 0, 65535, 65535);
        tlc.setLED(3, 0, 65535, 65535);
        tlc.write();
        usleep(500000);
    }

    tlc.setLED(0, 0, 0, 0);
    tlc.setLED(1, 0, 0, 0);
    tlc.setLED(2, 0, 0, 0);
    tlc.setLED(3, 0, 0, 0);
    tlc.write();
    tlc.end();

    return 0;
}