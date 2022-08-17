#pragma once

#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/Net/StreamSocket.h"

#include <iostream>
#include <string>

namespace DB
{

class ChistaDataTCPProxyClient
{
private:
    std::string host;
    int port;

    // IP endpoint/socket address (consists of host addr and port #)
    Poco::Net::SocketAddress socketAddr;

    // Interface to a TCP stream socket
    Poco::Net::StreamSocket socket;

public:
    ChistaDataTCPProxyClient(std::string host_, int port_);

    bool connected();
    bool sendMessage(std::string message);
};
}
