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
    std::cout << "Conectando al servidor en " << direccionIP << ":" << puertoMonitoreo << "\n";
    if (connect(descriptorMonitor, (sockaddr*)&direccionServidor, sizeof(direccionServidor)) == -1) {
        std::cerr << "Error al conectar al servidor de monitoreo" << direccionIP << ":" << puertoMonitoreo << "\n";;
        close(descriptorMonitor); // Asegúrate de cerrar el socket en caso de error.
        return;
    }
    char buffer[1024];
    ssize_t bytesRecibidos = recv(descriptorMonitor, buffer, sizeof(buffer) - 1, 0);
    if (bytesRecibidos > 0) {
        buffer[bytesRecibidos] = '\0'; // Añadir terminador nulo al final del buffer.
        std::cout << "Conexión exitosa al servidor" << direccionIP << ":" << puertoMonitoreo << "\n" << buffer << std::endl;;
    } else {
        std::cerr << "Error al recibir la información del servidor en" << direccionIP << ":" << puertoMonitoreo << "\n";
    }

    close(descriptorMonitor);
}

/*void monitorearServidores(const std::vector<std::pair<std::string, int>>& servidores, int intervaloSegundos) {
    while (true) {
        std::string resultadosCompletos; // Variable para acumular los resultados

        for (const auto& servidor : servidores) {
            resultadosCompletos += "Obteniendo información del servidor: " + servidor.first + " en el puerto " + std::to_string(servidor.second) + "\n"; 
            // Redirigir la salida de obtenerInformacionServidor a la variable resultadosCompletos
            int descriptorMonitor = socket(AF_INET, SOCK_STREAM, 0);
            if (descriptorMonitor == -1) {
                resultadosCompletos += "Error al crear el socket de monitoreo.\n";
                continue;
            }

            sockaddr_in direccionServidor;
            direccionServidor.sin_family = AF_INET;
            direccionServidor.sin_port = htons(servidor.second);
            inet_pton(AF_INET, servidor.first.c_str(), &direccionServidor.sin_addr);

            if (connect(descriptorMonitor, (sockaddr*)&direccionServidor, sizeof(direccionServidor)) == -1) {
                resultadosCompletos += "Error al conectar al servidor de monitoreo en " + servidor.first + ":" + std::to_string(servidor.second) + "\n";
                close(descriptorMonitor);
                continue;
            }

            char buffer[1024];
            ssize_t bytesRecibidos = recv(descriptorMonitor, buffer, sizeof(buffer) - 1, 0);
            if (bytesRecibidos > 0) {
                buffer[bytesRecibidos] = '\0';
                resultadosCompletos += "Información del servidor en " + servidor.first + ":" + std::to_string(servidor.second) + ":\n" + buffer + "\n";
            } else {
                resultadosCompletos += "Error al recibir la información del servidor en " + servidor.first + ":" + std::to_string(servidor.second) + "\n";
            }

            close(descriptorMonitor);
            resultadosCompletos += "----------------------------------------\n"; // Separador entre servidores
        }

        std::cout << resultadosCompletos; // Imprimir todos los resultados acumulados

        std::this_thread::sleep_for(std::chrono::seconds(intervaloSegundos));
    }
}*/


