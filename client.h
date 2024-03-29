#ifndef HTTP_CLIENT
#define HTTP_CLIENT

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define CLIENT_ERROR "Http Client error: "

typedef struct curl_slist header_list_t;

struct HttpClientConfig
{
    string client_cert_path;
    string client_ca_cert_path;
};

struct HttpRequest
{
    string method;
    string url;
    vector<string> headers;
};

struct HttpResponse
{
    int response_code;
    string data;
    vector<string> headers;
};

typedef struct HttpClientConfig http_client_config_t;

typedef struct HttpRequest http_request_t;

typedef struct HttpResponse http_response_t;

void check_status(int);

void show_client_error(int);

void append_header(http_request_t*, string);

class HttpClient
{
    CURL* curl_instance;
    header_list_t* current_headers;

    public:
        HttpClient();
        HttpClient(http_client_config_t);
        void perform_setup();
        void perform_operation();
        void process_ssl_config(http_client_config_t);
        void process_config(http_client_config_t);
        void process_request(http_request_t);
        void process_headers(http_request_t);
        void perform_cleanup();
        int make_request(http_request_t);
};

#endif
