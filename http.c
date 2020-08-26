#include <stdio.h>
#include <string.h>
#include <json-c/json.h>

#include "http.h"

/*
    Basic HTTP requests, the foundation of the API. But not the actual API ;)
*/

int http_init_buffer(struct http_buffer * buffer) {
    buffer->str = malloc(1);
    if(buffer->str == NULL) {
        return 1;
    }
    buffer->str[0] = '\0';
    buffer->len = 0;
    return 0;
}

int http_append_buffer(struct http_buffer * buffer, const char * str, size_t size) {
    buffer->str = realloc(buffer->str,(buffer->len+(size))+1);
    if(buffer->str == NULL) {
        fprintf(stderr,"HTTP_BUFFER allocation error\n");
        return 1;
    }
    memcpy(&buffer->str[buffer->len],str,(size));
    buffer->len += (size);
    return 0;
}

int http_end_buffer(struct http_buffer * buffer) {
    free(buffer->str);
    return 0;
}

/**
    HTTP write callback, appends the data obtained to hstr
*/
size_t http_write_callback(void * ptr, size_t size, size_t nmemb, void * stream) {
    size_t rsize = (size*nmemb);

    if(http_append_buffer((struct http_buffer *)stream,(const char *)ptr,rsize)) {
        printf("HTTP_BUFFER Append failed\n");
        return 0;
    }

    return rsize;
}

/**
    HTTP GET request, does a GET request and gets the results
*/
int http_get_request(struct http_buffer * buffer, struct http_handler * http, const char * url) {
    int retval = 0;
    http->curl = curl_easy_init();
    if(http->curl) {
        /** Send the full HTTP request and obtain the response from the server */
        curl_easy_setopt(http->curl,CURLOPT_WRITEFUNCTION,http_write_callback);
        curl_easy_setopt(http->curl,CURLOPT_USERAGENT,"Never-Gonna-Give-You-Up/1.0");
        curl_easy_setopt(http->curl,CURLOPT_WRITEDATA,(struct http_buffer *)buffer);
        curl_easy_setopt(http->curl,CURLOPT_HTTPGET,1L);
        curl_easy_setopt(http->curl,CURLOPT_URL,url);

        http->res = curl_easy_perform(http->curl);
        if(http->res != CURLE_OK) {
            printf("Error: %s\n",curl_easy_strerror(http->res));
            retval = 1;
        }
        curl_easy_cleanup(http->curl);
    }
    return retval;
}
