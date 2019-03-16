#include <iostream>

#include "client.h"

using namespace std;

int main()
{
    HttpClient client = HttpClient();

    http_request_t request = {
        "GET",
        "http://www.google.com"
    };

    append_header(&request, "Content-Type: text/html");

    client.make_request(request);
}

