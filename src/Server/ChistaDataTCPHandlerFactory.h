#pragma once

#include <Server/IServer.h>
#include <Server/TCPServerConnectionFactory.h>
#include <Poco/Net/NetException.h>
#include <Poco/Util/LayeredConfiguration.h>
#include <Common/logger_useful.h>
#include "ChistaDataTCPHandler.h"

namespace Poco { class Logger; }

namespace DB
{

class ChistaDataTCPHandlerFactory : public TCPServerConnectionFactory
{
private:
    IServer & server;
    bool parse_proxy_protocol = false;
    Poco::Logger * log;
    std::string server_display_name;

    class DummyTCPHandler : public Poco::Net::TCPServerConnection
    {
    public:
        using Poco::Net::TCPServerConnection::TCPServerConnection;
        void run() override {}
    };

public:
    ChistaDataTCPHandlerFactory(IServer & server_, bool secure_, bool parse_proxy_protocol_)
        : server(server_)
        , parse_proxy_protocol(parse_proxy_protocol_)
        , log(&Poco::Logger::get(std::string("ChistaDataTCP") + (secure_ ? "S" : "") + "HandlerFactory"))
    {
        LOG_TRACE(log, "CHISTADATA: in ChistaDataTCPHandlerFactory constructor");
        server_display_name = "CHISTADATA";
    }

    Poco::Net::TCPServerConnection * createConnection(const Poco::Net::StreamSocket & socket, TCPServer & tcp_server) override
    {
        try
        {
            LOG_TRACE(log, "CHISTADATA: TCP Request. Address: {}", socket.peerAddress().toString());
            return new ChistaDataTCPHandler(server, tcp_server, socket, parse_proxy_protocol, server_display_name);
        }
        catch (const Poco::Net::NetException &)
        {
            LOG_TRACE(log, "CHISTADATA: TCP Request. Client is not connected (most likely RST packet was sent).");
            return new DummyTCPHandler(socket);
        }
    }
};

}
