#include <iostream>
#include <vector>
#include <utility>
#include <thread>
#include <chrono>
#include "ClienteChat.h"
#include "ServidorChat.h"
#include "MonitorChat.h"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Uso: " << argv[0] << " <modo> <direccionIP> <puerto> <puertoMonitoreo>\n";
        std::cerr << "Modos disponibles: servidor, cliente, monitor\n";
        return 1;
    }

    std::string modo = argv[1];

    if (modo == "servidor") {
        if (argc < 4) {
            std::cerr << "Uso: " << argv[0] << " servidor <puerto> <puertoMonitoreo>\n";
            return 1;
        }
        int puerto = std::stoi(argv[2]);
        int puertoMonitoreo = std::stoi(argv[3]);
        ServidorChat servidor(puerto, puertoMonitoreo);  
        servidor.iniciar();  
        servidor.iniciarMonitoreo();  
    } else if (modo == "cliente") {
        if (argc < 4) {
            std::cerr << "Uso: " << argv[0] << " cliente <direccionIP> <puerto>\n";
            return 1;
        }
        std::string direccionIP = argv[2];
        int puerto = std::stoi(argv[3]);
        ClienteChat cliente(direccionIP, puerto);  
        cliente.conectarAlServidor();  

        std::string mensaje;
        while (std::getline(std::cin, mensaje)) {
            cliente.manejarComando(mensaje);  
        }

        cliente.desconectar();  
    } else if (modo == "monitor") {
        if (argc < 4) {
            std::cerr << "Uso: " << argv[0] << " monitor <direccionIP> <puertoMonitoreo>\n";
            return 1;
        }
        
        std::vector<std::pair<std::string, int>> servidores;

        for (int i = 2; i < argc; i += 2) {
            std::string direccionIP = argv[i];
            int puertoMonitoreo = std::stoi(argv[i + 1]);
            servidores.emplace_back(direccionIP, puertoMonitoreo);
        }
        
        while (true) {
            for (const auto& servidor : servidores) {
                std::cout << "Mandando a " << servidor.first << " en el puerto " << servidor.second << ".\n";
                obtenerInformacionServidor(servidor.first, servidor.second);
            }

            std::this_thread::sleep_for(std::chrono::seconds(5));
        }

    } else {
        std::cerr << "Modo desconocido: " << modo << "\n";
        return 1;
    }

    return 0;
}

