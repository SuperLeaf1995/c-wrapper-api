#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>

#include "http.h"
#include "guild.h"
#include "json-wrapper.h"

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
        htrps://ruqqus.com/api/is_available/<name> - Checks if username is available
        https://ruqqus.com/api/v1/user/<username>/listing - Listing (the posts that a user made)

    Note: Please dont use www.ruqqus.com, use ruqqus.com as using the www. prefix causes a CORS fault
    This applies to every bot made, regardless of language
*/

/*
    Functions that does a request and then fills the data
*/

json_object * fetch_json_object(json_object * root, const char * key) {
    json_object * sub;
    if(json_object_object_get_ex(root,key,&sub)) {
        return sub;
    } else {
        fprintf(stderr,"JSON error\n");
        return NULL;
    }
}

int main(void) {
    struct http_handler handle;
    struct ruqqus_guild guild;
    printf("RuqqusBot v1.0 by Superleaf1995\n");
    curl_global_init(CURL_GLOBAL_ALL);

    struct http_buffer buff;

    http_init_buffer(&buff);
    http_get_request(&buff,&handle,"https://ruqqus.com/api/v1/guild/linux");
    http_end_buffer(&buff);

    //ruqqus_guild_get(&guild,&handle,"linux");

    curl_global_cleanup();
    return 0;
}
