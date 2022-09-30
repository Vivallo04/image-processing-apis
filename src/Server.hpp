#include <boost/asio.hpp>

#ifndef OPENCV_SERVER_HPP
#define OPENCV_SERVER_HPP


class Server
{
public:
    Server();
    std::string SendMessage(boost::asio::ip::tcp::socket &socket, const std::string &message);
    std::string ReadMessage(boost::asio::ip::tcp::socket &socket);

private:
    const int PORT = 9080;

};


#endif //OPENCV_SERVER_HPP
