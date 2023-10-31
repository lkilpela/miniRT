#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

void test_ft_strdup(const char *s1, const char *expected)
{
    char *result = ft_strdup(s1);
    if (strcmp(result, expected) == 0)
    {
        printf("PASS: ft_strdup(\"%s\") -> \"%s\"\n", s1, result);
    }
    else
    {
        printf("FAIL: ft_strdup(\"%s\") -> \"%s\" (expected \"%s\")\n", s1, result, expected);
    }
    free(result);
}

int main()
{
    test_ft_strdup("", "");
    test_ft_strdup("hello", "hello");
    test_ft_strdup("world", "world");
    test_ft_strdup("foo bar", "foo bar");
    test_ft_strdup("12345", "12345");
    test_ft_strdup("a", "a");
    test_ft_strdup("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    test_ft_strdup("1234567890", "1234567890");
    test_ft_strdup("This is a test string.", "This is a test string.");
    return 0;
}