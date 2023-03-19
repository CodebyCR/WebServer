//
// Created by Christoph Rohde on 17.03.23.
//

#pragma once


#include <iostream>
#include <sstream>
#include <unordered_map>
#include <functional>

enum class CRUD {
    CREATE,
    READ,
    UPDATE,
    DELETE,

};


 /// HTTP Status Codes\n\n
 ///
 /// 2xx Success\n
 /// 4xx Client Error\n
 /// 5xx Server Error\n
namespace Status {
    constexpr auto OK = 200;
    constexpr auto CREATED = 201;
    constexpr auto ACCEPTED = 202;
    constexpr auto NO_CONTENT = 204;

    constexpr auto BAD_REQUEST = 400;
    constexpr auto UNAUTHORIZED = 401;
    constexpr auto FORBIDDEN = 403;
    constexpr auto NOT_FOUND = 404;
    constexpr auto METHOD_NOT_ALLOWED = 405;
    constexpr auto NOT_ACCEPTABLE = 406;
    constexpr auto CONFLICT = 409;

    constexpr auto INTERNAL_SERVER_ERROR = 500;
    constexpr auto NOT_IMPLEMENTED = 501;
    constexpr auto BAD_GATEWAY = 502;
    constexpr auto SERVICE_UNAVAILABLE = 503;
    constexpr auto GATEWAY_TIMEOUT = 504;
}

/** Content Types */
namespace ContentType{
    constexpr auto HTML = "text/html";
    constexpr auto JSON = "application/json";
    constexpr auto XML = "application/xml";
    constexpr auto TEXT = "text/plain";
    constexpr auto PNG = "image/png";
    constexpr auto SVG = "image/svg+xml";
    constexpr auto PDF = "application/pdf";
    constexpr auto BINARY = "application/octet-stream";
    constexpr auto MARKDOWN = "text/markdown";

}

/** HTTP Methods */
namespace HTTP{
    constexpr auto GET = "GET";
    constexpr auto POST = "POST";
    constexpr auto PUT = "PUT";
    constexpr auto DELETE = "DELETE";
    constexpr auto HEAD = "HEAD";
    constexpr auto OPTIONS = "OPTIONS";
    constexpr auto PATCH = "PATCH";
    constexpr auto TRACE = "TRACE";
    constexpr auto CONNECT = "CONNECT";
}

namespace REST {
    // "private" functions
    namespace _private_ {

        [[nodiscard]]
        auto handle_hello() -> std::string {
            const std::string css = " text-align: center;"
                        " margin-top: 100px;"
                        " font-size: 50px;"
                        " font-family: sans-serif;"
                        " background-image:linear-gradient(90deg, purple, blue, cyan);"
                        " -webkit-background-clip: text;"
                        " -webkit-text-fill-color: transparent;";

            std::ostringstream response;
            response << "HTTP/1.1 " << Status::OK << " OK\r\n";
            response << "Content-Type: " << ContentType::HTML << "\r\n";
            response << "\r\n";

            response << "<html>"
                            "<body>"
                                "<div style=\"" << css << "\">"
                                    "<h1>Hello from C++ Server!</h1>"
                                    "<div style=\" text-align: right; margin-right: 10%;\">"
                                        "<a  href=\"https://github.com/CodebyCR\"> My GitHub </a>"
                                    "</div>"
                                "</div>"
                            "</body>"
                        "</html>";
            return response.str();
        }

        std::string handle_markdown() {
            std::ostringstream response;
            response << "HTTP/1.1 " << Status::OK << " OK\r\n";
            response << "Content-Type: " << ContentType::MARKDOWN << "\r\n";
            response << "\r\n";
            response << "# Headline\n";
            response << "## Subheadline\n";
            response << "-[x] Listitem \n";
            response << "-[x] Listitem \n";
            response << "-[x] Listitem \n";
            return response.str();
        }

        std::string handle_json() {
            std::ostringstream response;
            response << "HTTP/1.1 " << Status::CREATED << " Created\r\n";
            response << "Content-Type: " << ContentType::JSON << "\r\n";
            response << "\r\n";
            response << "{\n"
                        "  \"name\": \"John Doe\",\n"
                        "  \"age\": 43,\n"
                        "  \"cars\": [\n"
                        "    { \"name\":\"Ford\", \"models\":[ \"Fiesta\", \"Focus\", \"Mustang\" ] },\n"
                        "    { \"name\":\"BMW\", \"models\":[ \"320\", \"X3\", \"X5\" ] },\n"
                        "    { \"name\":\"Fiat\", \"models\":[ \"500\", \"Panda\" ] }\n"
                        "  ]\n"
                        "}";
            return response.str();
        }

        [[nodiscard]]
        auto handle_not_found() -> std::string{
            std::ostringstream response;
            response << "HTTP/1.1 " << Status::NOT_FOUND << " Not Found\r\n";
            response << "Content-Type: " << ContentType::HTML << "\r\n";
            response << "\r\n";
            response << "<html><body><h1>Not Found</h1></body></html>";
            return response.str();
        }

        std::string handle_markdown();

        auto get_method(const std::string_view &method, const std::string_view &endpoint) -> std::string {
            // TODO handel endpoint

            if(method == HTTP::GET){
                if(endpoint == "/markdown"){
                    return _private_::handle_markdown();
                }
                else if(endpoint == "/json"){
                    return _private_::handle_json();
                }

                return _private_::handle_hello();
            }
            else if(method == HTTP::POST){
                return _private_::handle_not_found();
            }
            else if(method == HTTP::PUT){
                return _private_::handle_not_found();
            }
            else if(method == HTTP::DELETE){
                return _private_::handle_not_found();
            }
            else if(method == HTTP::HEAD){
                return _private_::handle_not_found();
            }
            else if(method == HTTP::OPTIONS){
                return _private_::handle_not_found();
            }
            else if(method == HTTP::PATCH){
                return _private_::handle_not_found();
            }
            else if(method == HTTP::TRACE){
                return _private_::handle_not_found();
            }
            else if(method == HTTP::CONNECT){
                return _private_::handle_not_found();
            }
            else{
                return _private_::handle_not_found();
            }

        }



    }
//    constexpr auto HELLO = "/hello";
//    constexpr auto POST = "/post";
//    constexpr auto GET_WITH_PARAMETER = "/get_with_parameter";

    [[nodiscard]]
    auto handle_request(const std::string& request) -> std::string {
        std::istringstream request_stream(request);
        std::string method_str;
        std::string endpoint;
        request_stream >> method_str >> endpoint;


        const auto response = _private_::get_method(method_str, endpoint);
        std::cout << "HTTP Method:\n" << response << std::endl;     // PUT
        std::cout << "Endpoint: " << endpoint << std::endl;        // /hallo

        return response;
    }

}
