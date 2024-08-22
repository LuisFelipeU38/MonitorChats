#include <iostream>
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
        ServidorChat servidor(puerto, puertoMonitoreo);  // Inicializa el servidor con los puertos proporcionados
        servidor.iniciar();  // Inicia el servidor
        servidor.iniciarMonitoreo();  // Inicia el servicio de monitoreo
    } else if (modo == "cliente") {
        if (argc < 4) {
            std::cerr << "Uso: " << argv[0] << " cliente <direccionIP> <puerto>\n";
            return 1;
        }
        std::string direccionIP = argv[2];
        int puerto = std::stoi(argv[3]);
        ClienteChat cliente(direccionIP, puerto);  // Inicializa el cliente con la dirección IP y puerto proporcionados
        cliente.conectarAlServidor();  // Conecta al servidor

        std::string mensaje;
        while (std::getline(std::cin, mensaje)) {
            cliente.manejarComando(mensaje);  // Envía el mensaje al servidor
        }

        cliente.desconectar();  // Desconecta del servidor
    } else if (modo == "monitor") {
        if (argc < 4) {
            std::cerr << "Uso: " << argv[0] << " monitor <direccionIP> <puertoMonitoreo>\n";
            return 1;
        }
        std::string direccionIP = argv[2];
        int puertoMonitoreo = std::stoi(argv[3]);
        // Crear y ejecutar el monitor
        obtenerInformacionServidor(direccionIP, puertoMonitoreo);
    } else {
        std::cerr << "Modo desconocido: " << modo << "\n";
        return 1;
    }

    return 0;
}

