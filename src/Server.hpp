#include <boost/asio.hpp>

#ifndef OPENCV_SERVER_HPP
#define OPENCV_SERVER_HPP


class Server
{
public:
    explicit Server(int port);
    static std::string SendMessage(boost::asio::ip::tcp::socket &socket, const std::string &message);
    static std::string ReadMessage(boost::asio::ip::tcp::socket &socket);

private:
    const int PORT = 8080;

};


#endif //OPENCV_SERVER_HPP
