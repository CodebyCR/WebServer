//
// Created by Christoph Rohde on 17.03.23.
//

#pragma once


#include <iostream>
#include <sstream>

enum class Method {
    GET,
    POST,
    PUT,
    DELETE,
    HEAD,
    OPTIONS,
    PATCH,
    TRACE,
    CONNECT,
    UNKNOWN
};

class RestApi {
private:

     [[nodiscard]]
     auto handle_hello() const -> std::string {
        std::ostringstream response;
        response << "HTTP/1.1 200 OK\r\n";
        response << "Content-Type: text/html\r\n";
        response << "\r\n";
        response << "<html><body><h1>Hello, world!</h1></body></html>";
        return response.str();
    }

     [[nodiscard]]
     auto handle_not_found() const -> std::string{
        std::ostringstream response;
        response << "HTTP/1.1 404 Not Found\r\n";
        response << "Content-Type: text/html\r\n";
        response << "\r\n";
        response << "<html><body><h1>Not Found</h1></body></html>";
        return response.str();
    }

public:
    RestApi() = default;
    ~RestApi() = default;

     [[nodiscard]]
     auto handle_request(const std::string& request) const -> auto {
        std::istringstream request_stream(request);
        std::string method, endpoint;
        request_stream >> method >> endpoint;

        if (method == "GET") {
            if (endpoint == "/hello") {
                return handle_hello();
            } else {
                return handle_not_found();
            }
        } else {
            std::cout << "Method not supported: " << method << std::endl;
            return handle_not_found();
        }
    }


};