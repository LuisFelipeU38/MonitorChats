#include "MonitorChat.h"
#include <iostream>
#include <string>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <direccionIP> <puertoMonitoreo>\n";
        return 1;
    }

    std::string direccionIP = argv[1];
    int puertoMonitoreo = std::stoi(argv[2]);

    while(true){
        obtenerInformacionServidor(direccionIP, puertoMonitoreo);
        sleep(10);
    }

    return 0;
}
