#include "Server.hpp"

Server::Server(int port)
{
    boost::asio::io_service io_service; // Servicio de input/output
    boost::asio::ip::tcp::acceptor acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234));
    // Acepta de manera asincrona conexiones en puerto 1234
    boost::asio::ip::tcp::socket socket_(io_service); // Declaracion de socket para conexiones

    cout << "Servidor iniciado" << endl;

    acceptor_.accept(socket_); // Acepta al socket del cliente que pida conectarse

    cout << "Cliente conectado" << endl;

    string message = ReadMessage(socket_); // Lee y declara mensaje del cliente
    cout << "Cliente dice: " + message << endl;

    SendMessage(socket_, "Hola, soy el servidor"); // Envia mensaje al cliente
    cout << "Mensaje enviado" << endl;
}
