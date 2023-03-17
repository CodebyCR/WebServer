//
// Created by Christoph Rohde on 16.03.23.
//

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../API/Rest.hpp"

class WebServer {
private:
    int port_;
    const char* ip_;
    int server_socket_ = 0;
    bool isRunning_ = true;

public:
    explicit WebServer(int port = 8080, const char* ip = nullptr) : port_(port), ip_(ip) {}

    ~WebServer() {
        // Socket schließen
        close(server_socket_);
    }

    auto run() -> void {
        // Socket erstellen
        server_socket_ = socket(AF_INET, SOCK_STREAM, 0);

        // Server-Adresse festlegen
        struct sockaddr_in server_address{};
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(port_);
        if (ip_ == nullptr) {
            server_address.sin_addr.s_addr = INADDR_ANY;
        } else {
            inet_pton(AF_INET, ip_, &(server_address.sin_addr));
        }
        std::cout << "Server Address: " << inet_ntoa(server_address.sin_addr) << std::endl;

        // Socket an die Adresse binden (+1 für std::boolalpha)
        bool isBound = 1 + bind(server_socket_, (struct sockaddr *)&server_address, sizeof(server_address));
        std::cout << "Address Bound successful: " << std::boolalpha << isBound << std::endl;

        // Socket in den Listenmodus versetzen
        listen(server_socket_, 5);

        const auto api = RestApi();

        // Auf Anfragen von Clients warten
        while (isRunning_) {
            int client_socket = accept(server_socket_, nullptr, nullptr);

            // Anfrage von Client lesen
            char buffer[1024];
            read(client_socket, buffer, 1024);

//            const std::string css = " text-align: center;"
//                                    " margin-top: 100px;"
//                                    " font-size: 50px;"
//                                    " font-family: sans-serif;"
//                                    " background-image:linear-gradient(90deg, purple, blue, cyan);"
//                                    " -webkit-background-clip: text;"
//                                    " -webkit-text-fill-color: transparent;";
//
//            // Response
//            std::ostringstream response;
//            response << "HTTP/1.1 200 OK\r\n";
//            response << "Content-Type: text/html\r\n";
//            response << "\r\n";
//            response << "<html>"
//                            "<body>"
//                                "<div style=\"" << css << "\">"
//                                    "<h1>Hello from C++ Server!</h1>"
//                                    "<div style=\" text-align: right; margin-right: 10%;\">"
//                                        "<a  href=\"https://github.com/CodebyCR\"> My GitHub </a>"
//                                    "</div>"
//                                "</div>"
//                            "</body>"
//                        "</html>";




            // REST-API-Aufruf behandeln
            std::string response = api.handle_request(buffer);

            auto total_response = response;

            // send Client response
            write(client_socket, total_response.c_str(), total_response.length());


            close(client_socket);
        }
    }

    /**
     * Stops the server from running
     * @note This method must be called from another thread
     * @return void
     */
    auto stop() -> void {
        isRunning_ = false;
    }

};
