#ifndef GUILD_H_INCLUDED
#define GUILD_H_INCLUDED

#include <stdlib.h>

#define NUMBER_OF_GUILD_STRINGS 9

struct ruqqus_guild {
    char ** char_fields;
    size_t * num_fields;
    char * bool_fields;

    size_t created_utc;
    char is_banned;
    char is_private;
    char is_restricted;
    size_t mods_count;
    char over_18;
    size_t subscriber_count;
};

int ruqqus_guild_fill(struct ruqqus_guild * guild, const char * str);
int ruqqus_guild_get(struct ruqqus_guild * guild, struct http_handler * handl, const char * guildname);

#endif // GUILD_H_INCLUDED
