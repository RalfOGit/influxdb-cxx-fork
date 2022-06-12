#ifndef __INFLUXDB_HTTP_CLIENT_H
#define __INFLUXDB_HTTP_CLIENT_H

#include <memory>
#include <string>

namespace influxdb
{

    /**
     *  Class implementing a very basic http client.
     */
    class HttpClient {
    public:

        HttpClient(void);

        int sendHttpGetRequest(const std::string& url, std::string& response, std::string& content);
        int sendHttpPutRequest(const std::string& url, const std::string& request_data, std::string& response, std::string& content);
        int sendHttpPostRequest(const std::string& url, const std::string& request_data, std::string& response, std::string& content);

    protected:

        int sendHttpRequest(const std::string& url, const std::string& method, const std::string& request_data, std::string& response, std::string& content);
        int connect_to_server(const std::string& url, std::string& host, std::string& path);
        int communicate_with_server(const int socket_fd, const std::string& request, std::string& response, std::string& content);
        size_t recv_http_response(int socket_fd, char* buffer, int buffer_size);
        int    parse_http_response(const std::string& answer, std::string& http_response, std::string& http_content);
        int    get_http_return_code(char* buffer, size_t buffer_size);
        size_t get_content_length(char* buffer, size_t buffer_size);
        size_t get_content_offset(char* buffer, size_t buffer_size);
        bool   is_chunked_encoding(char* buffer, size_t buffer_size);
        size_t get_chunk_length(char* buffer, size_t buffer_size);
        size_t get_chunk_offset(char* buffer, size_t buffer_size);
        size_t get_next_chunk_offset(char* buffer, size_t buffer_size);
    };

}       // namespace influxdb

#endif // __INFLUXDB_HTTP_CLIENT_H