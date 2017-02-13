#ifndef DICT_H
#define DICT_H

#include <stdbool.h>

typedef void Dict;

Dict *dict_get(Dict *dict, char *key);
Dict *dict_getl(Dict *dict, char *key, int len);
Dict *dict_new();
bool dict_add(Dict *dict, char *key, Dict *value);
bool dict_addl(Dict *dict, char *key, int len, Dict *value);
void *dict_del(Dict *dict, char *key);
void *dict_dell(Dict *dict, char *key, int len);
void dict_free(Dict *dict, void (*fn_free_value)(void *));

#endif /* DICT_H */
