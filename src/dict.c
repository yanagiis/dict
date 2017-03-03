#include <stdbool.h>
#include <stdlib.h>
#include <uthash.h>

#include "dict/dict.h"

#define HASH_FIND_NSTR(head, findstr, len, out) \
    HASH_FIND(hh, head, findstr, len, out)
#define HASH_ADD_NSTR(head, strfield, len, add) \
    HASH_ADD(hh, head, strfield[0], len, add)

struct DictItem {
    const char *arg;
    void *value;
    UT_hash_handle hh;
};

struct DictIterator {
    struct DictItem *el;
};

struct Dict {
    struct DictItem *head;
};

struct Dict *dict_new()
{
    struct Dict *dict = malloc(sizeof(struct Dict));
    if (dict != NULL) {
        dict->head = NULL;
    }
    return dict;
}

void dict_free(struct Dict *dict, void (*fn_free_value)(void *))
{
    struct Dict *d = (struct Dict *)dict;
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

bool dict_add(struct Dict *dict, const char *key, void *value)
{
    return dict_addl(dict, key, strlen(key), value);
}

bool dict_addl(struct Dict *dict, const char *key, int len, void *value)
{
    struct Dict *d = (struct Dict *)dict;
    struct DictItem *item;

    HASH_FIND_NSTR(d->head, key, len, item);
    if (item != NULL) {
        return false;
    }

    item = malloc(sizeof(*item));
    if (item == NULL) {
        return false;
    }
    item->arg = key;
    item->value = value;
    HASH_ADD_NSTR(d->head, arg, len, item);
    return true;
}

void *dict_get(struct Dict *dict, const char *key)
{
    return dict_getl(dict, key, strlen(key));
}

void *dict_getl(struct Dict *dict, const char *key, int len)
{
    struct Dict *d = (struct Dict *)dict;
    struct DictItem *item;
    HASH_FIND_NSTR(d->head, key, len, item);
    if (item != NULL) {
        return item->value;
    }
    return NULL;
}

void *dict_del(struct Dict *dict, const char *key)
{
    return dict_dell(dict, key, strlen(key));
}

void *dict_dell(struct Dict *dict, const char *key, int len)
{
    struct Dict *d = (struct Dict *)dict;
    struct DictItem *item;
    HASH_FIND_NSTR(d->head, key, len, item);
    if (item != NULL) {
        void *data = item->value;
        HASH_DEL(d->head, item);
        return data;
    }

    return NULL;
}

struct DictIterator *dict_iter_new(struct Dict *dict)
{
    struct DictIterator *it = malloc(sizeof(struct DictIterator));
    if (dict->head == NULL) {
        return NULL;
    }

    it->el = dict->head;
    return it;
}

void *dict_iter_next(struct DictIterator *it)
{
    if (it->el == NULL) {
        return NULL;
    }

    void *val = it->el->value;
    it->el = (it->el)->hh.next;
    return val;
}

void dict_iter_free(struct DictIterator *it)
{
    free(it);
}
