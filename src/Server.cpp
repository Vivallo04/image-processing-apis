#include <iostream>
#include "Server.hpp"
#include <boost/asio.hpp>

Server::Server(int port)
{
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), this -> PORT));
    boost::asio::ip::tcp::socket socket_(io_service);

    std::cout << "Server is initialized" << std::endl;

    acceptor_.accept(socket_);

    std::cout << "Client connected" << std::endl;

    std::string message = ReadMessage(socket_);
    std::cout << "Client says: " + message << std::endl;

    SendMessage(socket_, "Hola, soy el servidor");
    std::cout << "Mensaje enviado" << std::endl;
}

std::string Server::ReadMessage(boost::asio::ip::tcp::socket &socket)
{
    boost::asio::streambuf streamBuff;
    boost::asio::read_until(socket, streamBuff, "\n");
    std::string data = boost::asio::buffer_cast<const char *>(streamBuff.data());
    return data;
}

std::string Server::SendMessage(boost::asio::ip::tcp::socket &socket, const std::string &message)
{
    const std::string msg = message + "\n";
    boost::asio::write( socket, boost::asio::buffer(message));
}
