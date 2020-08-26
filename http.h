#ifndef HTTP_H_INCLUDED
#define HTTP_H_INCLUDED

#include <stdlib.h>
#include <curl/curl.h>

struct http_buffer {
    char * str;
    size_t len;
};

struct http_handler {
    CURL * curl;
    CURLcode res;
};

int http_init_buffer(struct http_buffer * buffer);
int http_append_buffer(struct http_buffer * buffer, const char * str, size_t size);
int http_end_buffer(struct http_buffer * buffer);
size_t http_write_callback(void * ptr, size_t size, size_t nmemb, void * stream);
int http_get_request(struct http_buffer * buffer, struct http_handler * http, const char * url);

#endif // HTTP_H_INCLUDED
