## Descripción del Proyecto
Este proyecto es un sistema de chat simple que permite a múltiples clientes conectarse a un servidor de chat, comunicarse entre ellos y ser monitoreados en tiempo real por un programa de monitorización. El sistema está implementado en C++ y utiliza sockets para la comunicación entre clientes, servidores y el monitor.

## El proyecto se compone de tres modos principales:

- Servidor de Chat: Administra las conexiones de los usuarios y facilita la comunicación entre ellos.
- Cliente de Chat: Se conecta al servidor y permite a los usuarios enviar y recibir mensajes.
- Monitor de Servidor: Supervisa el estado del servidor y las conexiones activas en tiempo real.

## Cómo Ejecutar el Proyecto:

- Compilación:

Para compilar el proyecto, navega a la raíz del proyecto y ejecuta el siguiente comando: make

Esto generará los ejecutables para el servidor, cliente y monitor en el directorio raíz.

## Ejecución:
1. Ejecutar el Servidor de Chat: 
            ./main servidor <puerto> <puertoMonitoreo>

Reemplaza <puerto> con el puerto en el que deseas que escuche el servidor (por ejemplo, 12345) y <puertoMonitoreo> con el puerto para la monitorización.

2. Ejecutar un Cliente de Chat:
            ./main cliente <ip_servidor> <puerto>

Reemplaza <ip_servidor> con la dirección IP del servidor de chat y <puerto> con el puerto al que conectarse (el mismo puerto que usaste para el servidor).

3. Ejecutar el Monitor:
            ./main monitor <ip_servidor> <puertoMonitoreo>

Reemplaza <ip_servidor> con la dirección IP del servidor de chat y <puertoMonitoreo> con el puerto usado para la monitorización.

## Funcionalidades:

- Servidor de Chat: Mantiene una lista de usuarios conectados.
                    Permite la comunicación entre múltiples clientes.
                    Envía datos al monitor sobre las conexiones activas.

-Cliente de Chat:   Se conecta al servidor para enviar y recibir mensajes.
                    Permite la interacción entre usuarios en tiempo real.

-Monitor de Chat:   Supervisa el estado del servidor.
                    Muestra el número de usuarios conectados y otros detalles relevantes.

## Requisitos del Sistema:

- Compilador C++ compatible con C++11 o superior.
- Sistema operativo Linux o Windows con soporte para sockets.


