#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <chrono>

class Usuario {
public:
    Usuario(const std::string& nombreUsuario, int descriptorSocket);
    std::string obtenerNombreUsuario() const;
    int obtenerDescriptorSocket() const;
    std::chrono::system_clock::time_point obtenerTiempoConexion() const;

private:
    std::string nombreUsuario;  // Nombre del usuario
    int descriptorSocket;      // Descriptor del socket del usuario
    std::chrono::system_clock::time_point tiempoConexion;
};

#endif // USUARIO_H