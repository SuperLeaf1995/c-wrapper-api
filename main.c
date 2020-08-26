#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        htrps://ruqqus.com/api/is_available/<name> - Checks if username is available
        https://ruqqus.com/api/v1/user/<username>/listing - Listing (the posts that a user made)

    Note: Please dont use www.ruqqus.com, use ruqqus.com as using the www. prefix causes a CORS fault
    This applies to every bot made, regardless of language
*/

struct ruqqus_guild {
    char * banner_url;
    char * color;
    size_t created_utc;
    char * description;
    char * description_html;
    char * fullname;
    char * id;
    char is_banned;
    char is_private;
    char is_restricted;
    size_t mods_count;
    char * name;
    char over_18;
    char * permalink;
    char * profile_url;
    size_t subscriber_count;
};

json_object * fetch_json_object(json_object * root, const char * key) {
    json_object * sub;
    if(json_object_object_get_ex(root,key,&sub)) {
        return sub;
    } else {
        fprintf(stderr,"JSON error\n");
        return NULL;
    }
}

/*
    Functions that does a request and then fills the data
*/
int ruqqus_guild_fill(struct ruqqus_guild * guild, const char * str) {
    json_object * root;
    json_object * sub;

    /* Fill the structure with the given JSON */
    root = json_tokener_parse(str);

    sub = fetch_json_object(root,"banner_url");
    if(sub == NULL) {
        fprintf(stderr,"JSON error\n");
        return 1;
    }

    /* banner_url */
    guild->banner_url = malloc(strlen(json_object_to_json_string(sub))+1);
    if(guild->banner_url == NULL) {
        fprintf(stderr,"Alloc request error\n");
        return 2;
    }
    strcpy(guild->banner_url,json_object_to_json_string(sub));

    /* color */
    sub = fetch_json_object(root,"color");
    if(sub == NULL) {
        fprintf(stderr,"JSON error\n");
        return 1;
    }
    guild->color = malloc(strlen(json_object_to_json_string(sub))+1);
    if(guild->color == NULL) {
        fprintf(stderr,"Alloc request error\n");
        return 2;
    }
    strcpy(guild->color,json_object_to_json_string(sub));
    return 0;
}

int ruqqus_guild_get(struct ruqqus_guild * guild, struct http_handler * handl, const char * guildname) {
    const char * url = "https://ruqqus.com/api/v1/guild/";
    struct http_buffer buffer;
    char * data = NULL;

    http_init_buffer(&buffer);
    data = malloc(strlen(url)+strlen(guildname)+1);
    if(data == NULL) {
        return 1;
    }
    memcpy(data,url,strlen(url)+1);
    strcat(data,guildname);

    printf("ruqqus_guild_get(): %s\n",data);

    if(http_get_request(&buffer,handl,data)) {
        fprintf(stderr,"Http get request error\n");
        return 2;
    }
    free(data);

    ruqqus_guild_fill(guild,buffer.str);

    http_end_buffer(&buffer);
    return 0;
}

/*
{
    "month": "1",
    "num": 3,
    "link": "",
    "year": "2006",
    "news": "",
    "safe_title": "Island (sketch)",
    "transcript": "[[A sketch of an Island]]\n{{Alt:Hello, island}}",
    "alt": "Hello, island",
    "img": "https://imgs.xkcd.com/comics/island_color.jpg",
    "title": "Island (sketch)",
    "day": "1"
}
*/

/*
    Bot that (supposedly) sends XKCD comics
*/

int main(void) {
    struct http_handler handle;
    struct http_buffer buff;
    struct ruqqus_guild * guild;

    printf("RuqqusBot v1.0 by Superleaf1995\n");

    curl_global_init(CURL_GLOBAL_ALL);

    ruqqus_guild_get(&guild,&handle,"linux");

    curl_global_cleanup();
    return 0;
}
