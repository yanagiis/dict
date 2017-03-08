#include "dict/dict.h"
#include <unity/unity.h>

static void test_dict_add_find(void)
{
    char *world = "world";
    struct Dict *dict = dict_new();
    TEST_ASSERT_TRUE(dict_add(dict, "hello", world));
    TEST_ASSERT_EQUAL_PTR(world, dict_get(dict, "hello"));
    TEST_ASSERT_EQUAL_PTR(NULL, dict_get(dict, "world"));
    dict_free(dict, NULL);
}

static void test_dict_iterator(void)
{
    struct Dict *dict = dict_new();
    dict_add(dict, "h", "hello");
    dict_add(dict, "w", "world");

    struct DictIterator *it = dict_iter_new(dict);
    int rc;
    const char *key;
    char *ptr;

    rc = dict_iter_next(it, &key, (void **)&ptr);
    TEST_ASSERT_EQUAL_INT(0, rc);
    TEST_ASSERT_EQUAL_STRING("h", key);
    TEST_ASSERT_EQUAL_STRING("hello", ptr);

    rc = dict_iter_next(it, &key, (void **)&ptr);
    TEST_ASSERT_EQUAL_INT(0, rc);
    TEST_ASSERT_EQUAL_STRING("w", key);
    TEST_ASSERT_EQUAL_STRING("world", ptr);

    dict_iter_free(it);
    dict_free(dict, NULL);
}

static void test_dict_addl_find(void)
{
    char *world = "world";
    struct Dict *dict = dict_new();
    TEST_ASSERT_TRUE(dict_addl(dict, "hello", 5, world));
    TEST_ASSERT_EQUAL_PTR(world, dict_getl(dict, "hello", 5));
    TEST_ASSERT_EQUAL_PTR(NULL, dict_getl(dict, "world", 5));
    dict_free(dict, NULL);
}

static void test_dict_iterator_with_non_zero_terminate_string(void)
{
    struct Dict *dict = dict_new();
    dict_addl(dict, "h", 1, "hello");
    dict_addl(dict, "w", 1, "world");

    struct DictIterator *it = dict_iter_new(dict);
    int rc;
    const char *key;
    char *ptr;

    rc = dict_iter_next(it, &key, (void **)&ptr);
    TEST_ASSERT_EQUAL_INT(0, rc);
    TEST_ASSERT_EQUAL_STRING_LEN("h", key, 1);
    TEST_ASSERT_EQUAL_STRING("hello", ptr);

    rc = dict_iter_next(it, &key, (void **)&ptr);
    TEST_ASSERT_EQUAL_INT(0, rc);
    TEST_ASSERT_EQUAL_STRING_LEN("w", key, 1);
    TEST_ASSERT_EQUAL_STRING("world", ptr);

    dict_iter_free(it);
    dict_free(dict, NULL);
}

int main(int argc, char *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_dict_add_find);
    RUN_TEST(test_dict_iterator);
    RUN_TEST(test_dict_addl_find);
    RUN_TEST(test_dict_iterator_with_non_zero_terminate_string);
    UNITY_END();
    return 0;
}
