#include <stdbool.h>
#include <stdlib.h>
#include <uthash.h>

#include "dict.h"

#define HASH_FIND_NSTR(head, findstr, len, out) \
    HASH_FIND(hh, head, findstr, len, out)
#define HASH_ADD_NSTR(head, strfield, len, add) \
    HASH_ADD(hh, head, strfield[0], len, add)

typedef struct DictItem {
    char *arg;
    void *value;
    UT_hash_handle hh;
} DictItem;

typedef struct DictImp {
    DictItem *head;
} DictImp;

Dict *dict_new()
{
    DictImp *dict = malloc(sizeof(DictImp));
    if (dict != NULL) {
        dict->head = NULL;
    }
    return dict;
}

void dict_free(Dict *dict, void (*fn_free_value)(void *))
{
    DictImp *d = (DictImp *)dict;
    struct DictItem *current, *tmp;

    HASH_ITER(hh, d->head, current, tmp)
    {
        HASH_DEL(d->head, current);
        if (fn_free_value != NULL) {
            fn_free_value(current->value);
        }
        free(current);
    }
    free(d);
}

bool dict_add(Dict *dict, char *key, Dict *value)
{
    return dict_addl(dict, key, strlen(key), value);
}

bool dict_addl(Dict *dict, char *key, int len, Dict *value)
{
    DictImp *d = (DictImp *)dict;
    DictItem *item;

    HASH_FIND_NSTR(d->head, key, len, item);
    if (item != NULL) {
        return false;
    }

    item = malloc(sizeof(DictItem));
    if (item == NULL) {
        return false;
    }
    item->arg = key;
    item->value = value;
    HASH_ADD_NSTR(d->head, arg, len, item);
    return true;
}

Dict *dict_get(Dict *dict, char *key)
{
    return dict_getl(dict, key, strlen(key));
}

Dict *dict_getl(Dict *dict, char *key, int len)
{
    DictImp *d = (DictImp *)dict;
    DictItem *item;
    HASH_FIND_NSTR(d->head, key, len, item);
    if (item != NULL) {
        return item->value;
    }
    return NULL;
}

void *dict_del(Dict *dict, char *key)
{
    return dict_dell(dict, key, strlen(key));
}

void *dict_dell(Dict *dict, char *key, int len)
{
    DictImp *d = (DictImp *)dict;
    DictItem *item;
    HASH_FIND_NSTR(d->head, key, len, item);
    if (item != NULL) {
        void *data = item->value;
        HASH_DEL(d->head, item);
        return data;
    }

    return NULL;
}
