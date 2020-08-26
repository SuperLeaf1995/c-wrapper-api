#ifndef JSON-WRAPPER_H_INCLUDED
#define JSON-WRAPPER_H_INCLUDED

#include <json-c/json.h>

json_object * fetch_json_object(json_object * root, const char * key);

#endif // JSON-WRAPPER_H_INCLUDED
