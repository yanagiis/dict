#ifndef DICT_H
#define DICT_H

#include <stdbool.h>

struct Dict;

struct Dict *dict_new();
void *dict_get(struct Dict *dict, const char *key);
void *dict_getl(struct Dict *dict, const char *key, int len);
bool dict_add(struct Dict *dict, const char *key, void *value);
bool dict_addl(struct Dict *dict, const char *key, int len, void *value);
void *dict_del(struct Dict *dict, const char *key);
void *dict_dell(struct Dict *dict, const char *key, int len);
void dict_free(struct Dict *dict, void (*fn_free_value)(void *));

#endif /* DICT_H */
