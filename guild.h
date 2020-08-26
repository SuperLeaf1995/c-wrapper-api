#ifndef GUILD_H_INCLUDED
#define GUILD_H_INCLUDED

#include <stdlib.h>

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

int ruqqus_guild_fill(struct ruqqus_guild * guild, const char * str);
int ruqqus_guild_get(struct ruqqus_guild * guild, struct http_handler * handl, const char * guildname);

#endif // GUILD_H_INCLUDED
