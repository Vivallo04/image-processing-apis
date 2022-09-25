#include <boost/asio.hpp>

#ifndef OPENCV_SERVER_HPP
#define OPENCV_SERVER_HPP


class Server
{
public:
    explicit Server(int port);

private:
    int port = 8080;

};


#endif //OPENCV_SERVER_HPP
