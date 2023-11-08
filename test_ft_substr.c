#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

void test_ft_substr(char const *s, unsigned int start, size_t len, char const *expected_result)
{
    char *result = ft_substr(s, start, len);
    if (strcmp(result, expected_result) == 0)
    {
        printf("PASS: ft_substr(\"%s\", %d, %zu) => \"%s\"\n", s, start, len, result);
    }
    else
    {
        printf("FAIL: ft_substr(\"%s\", %d, %zu) => \"%s\" (expected \"%s\")\n", s, start, len, result, expected_result);
    }
    free(result);
}

int main()
{
    // Test 1: Substring is within the string
    test_ft_substr("Hello, world!", 7, 5, "world");

    // Test 2: Substring starts at the beginning of the string
    test_ft_substr("Hello, world!", 0, 5, "Hello");

    // Test 3: Substring ends at the end of the string
    test_ft_substr("Hello, world!", 7, 6, "world!");

    // Test 4: Substring is longer than the remaining string
    test_ft_substr("Hello, world!", 7, 20, "world!");

    // Test 5: Substring starts beyond the end of the string
    test_ft_substr("Hello, world!", 20, 5, "");

    // Test 6: Substring starts at the end of the string
    test_ft_substr("Hello, world!", 12, 1, "");

    // Test 7: Substring is empty
    test_ft_substr("Hello, world!", 7, 0, "");

    return 0;
}