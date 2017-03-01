#include "dict/dict.h"
#include <unity/unity.h>

static void test_dict_add_find(void)
{
    char *world = "world";
	void *dict = dict_new();
	TEST_ASSERT_TRUE(dict_add(dict, "hello", world));
    TEST_ASSERT_EQUAL_PTR(world, dict_get(dict, "hello"));
    TEST_ASSERT_EQUAL_PTR(NULL, dict_get(dict, "world"));
	dict_free(dict, NULL);
}

int main(int argc, char *argv[])
{
	UNITY_BEGIN();
	RUN_TEST(test_dict_add_find);
	UNITY_END();
    return 0;
}
