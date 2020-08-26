#include <stdio.h>
#include <string.h>
#include <json-c/json.h>

#include "json-wrapper.h"
#include "guild.h"

static const char * char_keyval[NUMBER_OF_GUILD_STRINGS+1] = {
    "color","banner_url","description","description_html",
    "fullname","id","name","permalink","profile_url"
};

static const char * num_keyval[NUMBER_OF_GUILD_NUMS+1] = {
    "created_utc","mods_count","subscriber_count"
};

/*
    Fills the guild struct with the JSON data on str
*/
int ruqqus_guild_fill(struct ruqqus_guild * guild, const char * str) {
    json_object * root,sub;
    int i = 0;

    /* Fill the structure's strings with the given JSON */
    root = json_tokener_parse(str);
    guild->char_fields = malloc(sizeof(char *)*NUMBER_OF_GUILD_STRINGS+1);
    for(i = 0; i < NUMBER_OF_GUILD_STRINGS; i++) {
        sub = fetch_json_object(root,char_keyval[i]);
        if(sub == NULL) {
            fprintf(stderr,"JSON error fetching %s",char_keyval[i]);
            return 1;
        }
        guild->char_fields[i] = malloc(strlen(json_object_to_json_string(sub))+1);
        if(guild->char_fields[i] == NULL) {
            fprintf(stderr,"Alloc request error\n");
            return 2;
        }
        strcpy(guild->char_fields[i],json_object_to_json_string(sub));
#ifdef __DEBUG__
        printf("%s : %s\n\n",char_keyval[i],guild.char_fields[i]);
#endif
    }
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
