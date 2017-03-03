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
    dict_add(dict, "hello", "hello");
    dict_add(dict, "world", "world");

    struct DictIterator *it = dict_iter_new(dict);
    char *ptr;

    ptr = dict_iter_next(it);
    TEST_ASSERT_NOT_EQUAL(NULL, ptr);
    TEST_ASSERT_EQUAL_STRING("hello", ptr);

    ptr = dict_iter_next(it);
    TEST_ASSERT_NOT_EQUAL(NULL, ptr);
    TEST_ASSERT_EQUAL_STRING("world", ptr);

    dict_iter_free(it);
    dict_free(dict, NULL);
}

int main(int argc, char *argv[])
{
	UNITY_BEGIN();
	RUN_TEST(test_dict_add_find);
	RUN_TEST(test_dict_iterator);
	UNITY_END();
    return 0;
}
