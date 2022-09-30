#include <iostream>
#include "Server.hpp"
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>


Server::Server()
{
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor_(io_service,
                                             boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), this -> PORT));
    boost::asio::ip::tcp::socket socket_(io_service);

    BOOST_LOG_TRIVIAL(info) <<"Server initialized";
    acceptor_.accept(socket_);

    BOOST_LOG_TRIVIAL(info) <<"Client Connected";

    std::string message = ReadMessage(socket_);
    std::cout << "Client says: " + message << std::endl;

    auto return_message = "Este mensaje viene del servidor";

    SendMessage(socket_, return_message);
    BOOST_LOG_TRIVIAL(info) << "Message sent";
    socket_.close();
}

std::string Server::ReadMessage(boost::asio::ip::tcp::socket &socket)
{
    BOOST_LOG_TRIVIAL(info) <<"Reading message...";
    boost::asio::streambuf streamBuff;
    boost::asio::read_until(socket, streamBuff, "\n");
    std::string data = boost::asio::buffer_cast<const char *>(streamBuff.data());
    BOOST_LOG_TRIVIAL(info) << "Data: " + data;
    return data;
}

std::string Server::SendMessage(boost::asio::ip::tcp::socket &socket, const std::string &message)
{
    BOOST_LOG_TRIVIAL(info) <<"Sending message";
    const std::string msg = message + "\n";
    boost::asio::write( socket, boost::asio::buffer(message));
    BOOST_LOG_TRIVIAL(info) << "Message sent";
}