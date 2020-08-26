#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <json-c/json.h>

#include "http.h"

/*
    There is really not much magic in Ruqqus API. It's just a bunch of requests

    Do an HTTP_GET_REQUEST. It will save the response in the given buffer.

    List of API links:
        https://ruqqus.com/api/v1/guild/<guildname> - Get guild info
        https://ruqqus.com/api/v1/user/<username> - Get user info
        https://ruqqus.com/api/v1/post/<post id> - Get post info
        https://ruqqus.com/api/v1/comment/<comment id> - Get comment info
        https://ruqqus.com/api/v1/guild/<guildname>/listing - Listing (the posts in a guild)
        https://ruqqus.com/board_available/<guildname> - Checks if guild is available for creation

    Note: Please dont use www.ruqqus.com, use ruqqus.com as using the www. prefix causes a CORS fault
    This applies to every bot made, regardless of language
*/

int main(void) {
    struct http_handler handle;
    struct http_buffer buff;

    printf("RuqqusBot v1.0 by Superleaf1995\n");

    curl_global_init(CURL_GLOBAL_ALL);
    http_init_buffer(&buff);

    if(http_get_request(&buff,&handle,"https://ruqqus.com/api/v1/guild/linux")) {
        printf("Error. Ending bot\n");
        curl_global_cleanup();
        return 0;
    }
    printf("%s\n",buff.str); // We got the JSON data!
    http_end_buffer(&buff);

    curl_global_cleanup();
    return 0;
}
