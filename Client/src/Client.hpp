#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

#ifndef CLIENT_CLIENT_HPP
#define CLIENT_CLIENT_HPP


class Client : public boost::enable_shared_from_this<Client>
{
private:
    boost::asio::ip::tcp::socket socket;
    std::string message = "Hello From Server!";
    enum { max_length = 1024 };
    char data[max_length]{};

public:
    typedef boost::shared_ptr<Client> pointer;
    Client(boost::asio::io_service& io_service): socket(io_service){};
    static pointer Create(boost::asio::io_service& io_service);
    boost::asio::ip::tcp::socket& GetSocket();
    void Start();
    void Read(const boost::system::error_code& error, size_t bytes_transferred);
    void Write(const boost::system::error_code& error, size_t bytes_transferred);
};

#endif //CLIENT_CLIENT_HPP
