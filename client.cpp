#include "client.h"

using namespace std;

void check_status(int return_code)
{
    if (return_code == 0)
    {
        return;
    }

    throw return_code;
}

void show_client_error(int error_code)
{
    cout << CLIENT_ERROR << error_code << endl;
}

void append_header(http_request_t* request, string header)
{
    request->headers.push_back(header);
}

HttpClient::HttpClient()
{
    perform_setup();
}

HttpClient::HttpClient(http_client_config_t config)
{
    try
    {
        perform_setup();

        process_config(config);
    }
    catch (int error_code)
    {
        show_client_error(error_code);
    }
}

void HttpClient::perform_setup()
{
    if (this->curl_instance == NULL)
    {
        this->curl_instance = curl_easy_init();
    }
}

void HttpClient::perform_operation()
{
    CURLcode return_code = curl_easy_perform(this->curl_instance);

    check_status((int) return_code);
}

void HttpClient::perform_cleanup()
{
    if (this->current_headers != NULL)
    {
        curl_slist_free_all(this->current_headers);
    }

    curl_easy_cleanup(this->curl_instance);

    this->curl_instance = NULL;
}

void HttpClient::process_ssl_config(http_client_config_t config)
{
    if (config.client_cert_path.length())
    {
        CURLcode return_code = curl_easy_setopt(this->curl_instance, CURLOPT_SSLCERTTYPE, "PEM");

        check_status((int) return_code);

        return_code = curl_easy_setopt(this->curl_instance, CURLOPT_SSLCERT, config.client_cert_path.c_str());

        check_status((int) return_code);
    }
}

void HttpClient::process_config(http_client_config_t config)
{
    process_ssl_config(config);
}

void HttpClient::process_request(http_request_t request)
{
    CURLcode return_code = curl_easy_setopt(this->curl_instance, CURLOPT_URL, request.url.c_str());

    check_status((int) return_code);

    process_headers(request);
}

void HttpClient::process_headers(http_request_t request)
{
    if (request.headers.size() > 0)
    {
        this->current_headers = NULL; 

        for (auto i = request.headers.begin(); i != request.headers.end(); i++)
        {
            this->current_headers = curl_slist_append(this->current_headers, i->c_str());
        }

        CURLcode return_code = curl_easy_setopt(this->curl_instance, CURLOPT_HTTPHEADER, this->current_headers);

        check_status((int) return_code);
    }
}

int HttpClient::make_request(http_request_t request)
{
    try
    {
        perform_setup();

        process_request(request);

        perform_operation();

        perform_cleanup();
    
        return 0;
    }
    catch (int error_code)
    {
        show_client_error(error_code);
        return error_code;
    }

    return 1;
}

