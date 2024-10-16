#include <iostream>
#include <boost/asio.hpp>

using namespace boost;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cerr << "started\n";
    asio::io_service io_service{};
    asio::ip::tcp::acceptor acceptor{
        io_service,
        asio::ip::tcp::endpoint{
            asio::ip::tcp::v4(),
            1234
        }
    };

    asio::ip::tcp::socket socket{io_service};
    acceptor.accept(socket);

    asio::streambuf buffer;
    asio::read_until(
        socket,
        buffer,
        '\n'
    );

    std::string received_message = asio::buffer_cast<const char*>(buffer.data());


    std::string message = "hello from client\n";
    std::cerr << "message is ready : " << message << std::endl;

    asio::write(
        socket,
        asio::buffer(message)
    );



    std::cerr << "received message : " << received_message << std::endl;
    return 0;
}