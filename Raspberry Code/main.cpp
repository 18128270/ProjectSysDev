#include "TCPListener.h"

int main(void) {
    // init class, run the init after
    TCPListener RaspServer(8080);
    RaspServer.init();

    while (1) {
    // runs TCPlistner.run, TCPlistner.CheckIncCommands, WEMOSTunnel.run, WEMOSTunnel.sendCommand
    RaspServer.run();
    }
}