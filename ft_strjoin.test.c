#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

void test_ft_strjoin(char const *s1, char const *s2, char const *expected)
{
    char *result = ft_strjoin(s1, s2);
    if (strcmp(result, expected) == 0)
    {
        printf("PASS: ft_strjoin(\"%s\", \"%s\") -> \"%s\"\n", s1, s2, result);
    }
    else
    {
        printf("FAIL: ft_strjoin(\"%s\", \"%s\") -> \"%s\" (expected \"%s\")\n", s1, s2, result, expected);
    }
    free(result);
}

int main()
{
    test_ft_strjoin("", "", "");
    test_ft_strjoin("", "hello", "hello");
    test_ft_strjoin("world", "", "world");
    test_ft_strjoin("hello", "world", "helloworld");
    test_ft_strjoin("foo", "bar", "foobar");
    test_ft_strjoin("hello ", "world", "hello world");
    test_ft_strjoin("hello", " world", "hello world");
    test_ft_strjoin("hello", " world ", "hello world ");
    test_ft_strjoin("hello ", " world ", "hello  world ");
    test_ft_strjoin("hello", NULL, NULL);
    test_ft_strjoin(NULL, "world", NULL);
    test_ft_strjoin(NULL, NULL, NULL);
    return 0;
}