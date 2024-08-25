#include "MonitorChat.h"
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <chrono>
#include <thread>

void obtenerInformacionServidor(const std::string& direccionIP, int puertoMonitoreo) {
    int descriptorMonitor = socket(AF_INET, SOCK_STREAM, 0);
    if (descriptorMonitor == -1) {
        std::cerr << "Error al crear el socket de monitoreo.\n";
        return;
    }

    sockaddr_in direccionServidor;
    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_port = htons(puertoMonitoreo);
    inet_pton(AF_INET, direccionIP.c_str(), &direccionServidor.sin_addr);
    std::cout << "---------------Salas--------------:\n" << std::endl;
    std::cout << "Conectando al servidor en " << direccionIP << " : " << puertoMonitoreo << "\n";
    if (connect(descriptorMonitor, (sockaddr*)&direccionServidor, sizeof(direccionServidor)) == -1) {
        std::cerr << "Error al conectar al servidor de monitoreo" << direccionIP << ":" << puertoMonitoreo << "\n";;
        close(descriptorMonitor); 
        return;
    }
    char buffer[1024];
    ssize_t bytesRecibidos = recv(descriptorMonitor, buffer, sizeof(buffer) - 1, 0);
    if (bytesRecibidos > 0) {
        buffer[bytesRecibidos] = '\0'; 
        std::cout << "Conexión exitosa al servidor" << direccionIP << " : " << puertoMonitoreo << "\n" << buffer << std::endl;;
    } else {
        std::cerr << "Error al recibir la información del servidor en" << direccionIP << ":" << puertoMonitoreo << "\n";
    }

    close(descriptorMonitor);
}




