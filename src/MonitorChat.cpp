// MonitorChat.cpp
#include "MonitorChat.h"
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

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

    if (connect(descriptorMonitor, (sockaddr*)&direccionServidor, sizeof(direccionServidor)) == -1) {
        std::cerr << "Error al conectar al servidor de monitoreo.\n";
        close(descriptorMonitor); // Asegúrate de cerrar el socket en caso de error.
        return;
    }

    char buffer[1024];
    ssize_t bytesRecibidos = recv(descriptorMonitor, buffer, sizeof(buffer) - 1, 0);
    if (bytesRecibidos > 0) {
        buffer[bytesRecibidos] = '\0'; // Añadir terminador nulo al final del buffer.
        std::cout << "Información del servidor:\n" << buffer << std::endl;
    } else {
        std::cerr << "Error al recibir la información del servidor.\n";
    }

    close(descriptorMonitor);
}

