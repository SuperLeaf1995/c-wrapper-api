#include <stdio.h>
#include <string.h>
#include <json-c/json.h>

#include "json-wrapper.h"
#include "guild.h"

/*
    Fills the guild struct with the JSON data on str
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

/*
    Gets info from the guild via API
*/
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
