#include <iostream>
#include <unistd.h>

#include "client.h"

using namespace std;

int main()
{
    HttpClient client = HttpClient();

    http_request_t request = {
        "GET",
        "http://google.com"
    };

    append_header(&request, "Content-Type: text/html");

    client.make_request(request);

    usleep(1000000);

    client.make_request(request);
}

