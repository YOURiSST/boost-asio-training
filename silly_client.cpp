#include <iostream>
#include <boost/asio.hpp>

using namespace boost;

int main() {
    std::cerr << "client started" << std::endl;

    asio::io_service io_service;
    asio::ip::tcp::socket socket{io_service};
    socket.connect(asio::ip::tcp::endpoint(
        asio::ip::address::from_string("127.0.0.1"), 1234
    ));

    std::cerr << "client connected to server\n";
    std::string message_from_client = "Hello from client!\n";
    asio::write(socket, asio::buffer(message_from_client));
    std::cerr << "writed to server, message : " << message_from_client << std::endl;

    asio::streambuf buffer;
    asio::read(socket, buffer, asio::transfer_all());

    std::string received_from_server = asio::buffer_cast<const char*>(buffer.data());
    std::cerr << "received init message from server : " << received_from_server << std::endl;
    return 0;
}