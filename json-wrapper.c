#include "json-wrapper.h"

/*
    Get an object KEY from JSON and return the associated object
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
