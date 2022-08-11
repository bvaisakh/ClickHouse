#pragma once

#include <Server/IServer.h>
#include <Server/TCPHandler.h>

namespace Poco
{
class Logger;
}

namespace DB
{

class ChistaDataTCPHandler : public TCPHandler
{
private:
    Poco::Logger * log;

public:
    ChistaDataTCPHandler(
        IServer & server_,
        TCPServer & tcp_server_,
        const Poco::Net::StreamSocket & socket_,
        bool parse_proxy_protocol_,
        std::string server_display_name_)
        : TCPHandler(server_, tcp_server_, socket_, parse_proxy_protocol_, server_display_name_)
        , log(&Poco::Logger::get(std::string("ChistaDataTCPHandler")))
    {
        LOG_TRACE(log, "CHISTADATA: in ChistaDataTCPHandler constructor");
    }
};
}
