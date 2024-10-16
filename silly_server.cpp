#include <iostream>
#include <boost/asio.hpp>

using namespace boost;

int main() {
    std::cerr << "server is started" << std::endl;
    asio::io_service io_service{};
    asio::ip::tcp::acceptor acceptor{
        io_service,
        asio::ip::tcp::endpoint{
            asio::ip::tcp::v4(),
            1234
        }
    };

    asio::ip::tcp::socket socket{io_service};
    std::cerr << "waiting for client\n";
    acceptor.accept(socket);

    asio::streambuf buffer;
    asio::read_until(
        socket,
        buffer,
        '\n'
    );

    std::string received_message = asio::buffer_cast<const char*>(buffer.data());
    std::cerr << "init message from client is ready : " << received_message << std::endl;

    std::string answer_message = "hello from server\n";
    asio::write(
        socket,
        asio::buffer(answer_message)
    );
    std::cerr << "answered for client : " << answer_message << std::endl;

    return 0;
}