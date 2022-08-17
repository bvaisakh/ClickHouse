#include "ChistaDataTCPProxyClient.h"

namespace DB
{

ChistaDataTCPProxyClient::ChistaDataTCPProxyClient(std::string host_, int port_)
    : host(host_)
    , port(port_)
    , socketAddr(host_, port_)
    , socket() {
    std::cout << "Host: " << host << "\tPort: " << port << std::endl;
}

// Connect to the initialized socket address' hostname and port
bool ChistaDataTCPProxyClient::connected()
{
    std::cout << "Creating a connection with ["
              << socketAddr.host().toString()
              << "] through port [" << socketAddr.port() << "] ...";
    try
    {
        socket.connect(socketAddr);
        std::cout << "Success!" << std::endl;
    }
    catch (Poco::Exception err)
    {
        std::cout << std::endl;
        std::cout << "Socket connection error: [" << err.displayText() << "]" << std::endl;
        return false;
    }
    return true;
}

// Send a message to the connected server
bool ChistaDataTCPProxyClient::sendMessage(std::string message)
{
    std::cout << std::endl;

    try
    {
        connected();
        std::cout << "Sending the message \"" << message << "\" to the server!" << std::endl;
        socket.sendBytes(message.data(), message.size());
        socket.shutdown();
        socket.close();
        return true;
    }
    catch (Poco::Exception err)
    {
        std::cout << "Data send error: [" << err.displayText() << "]" << std::endl;
        return false;
    }
}
}
