#include <QApplication>
#include <QPushButton>
#include <boost/asio.hpp>
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket(io_service);
    boost::system::error_code error;
    boost::asio::streambuf receive_buffer;
    const std::string outMessage = "Hola, soy el cliente\n";

    const int PORT = 9080;

    socket.connect(boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), PORT));
    std::cout << "Conectado al servidor" << std::endl;

    boost::asio::write(socket, boost::asio::buffer(outMessage), error );

    if(!error)
    {
        std::cout << "Mensaje enviado" << std::endl;
    }
    else
    {
        std::cout << "error" << error.message() << std::endl;
    }

    boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);

    if (error && error != boost::asio::error::eof)
    {
        std::cout << "error" << error.message() << std::endl;
    }
    else
    {
        const char* inMessage = boost::asio::buffer_cast<const char*>(receive_buffer.data());
        std::cout << "Servidor dice: " + (std::string) inMessage << std::endl;
    }
    
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
