#include "TCPListener.h"

int main(void)
{
    TCPListener RaspServer(8080);
    RaspServer.init();

while (1)
{
    RaspServer.run();
    RaspServer.CheckIncCommands();
}

}