#include "Client.hpp"

void Client::Read(const boost::system::error_code &error, size_t bytes_transferred)
{
    if (!error)
    {
        std::cout << data << std::endl;
    } else
    {
        std::cerr << "error: " << error.message() << std::endl;
        socket.close();
    }
}

void Client::Write(const boost::system::error_code &error, size_t bytes_transferred)
{
    if (!error)
    {
        std::cout << "Server sent Hello message!"<< std::endl;
    } else
    {
        std::cerr << "error: " << error.message() << std::endl;
        socket.close();
    }
}

void Client::Start()
{
    socket.async_read_some(
            boost::asio::buffer(data, max_length),
            boost::bind(
                    &Client::Read,
                    shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));

    socket.async_write_some(boost::asio::buffer(message, max_length),
            boost::bind(
                    &Client::Write,
                    shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

boost::asio::ip::tcp::socket &Client::GetSocket()
{
    return socket;
}

Client::pointer Client::Create(boost::asio::io_service &io_service)
{
    return pointer(new Client(io_service));
}
