#include <stdio.h>
#include <string.h>
#include "libft.h"

void test_ft_strlcat(char *dst, const char *src, size_t dstsize, size_t expected)
{
    size_t result = ft_strlcat(dst, src, dstsize);
    if (result == expected)
    {
        printf("PASS: ft_strlcat(\"%s\", \"%s\", %zu) -> %zu\n", dst, src, dstsize, result);
    }
    else
    {
        printf("FAIL: ft_strlcat(\"%s\", \"%s\", %zu) -> %zu (expected %zu)\n", dst, src, dstsize, result, expected);
    }
}

int main()
{
    char dst[20] = "hello";
    test_ft_strlcat(dst, " world", 20, 11);
    test_ft_strlcat(dst, "!", 20, 12);
    test_ft_strlcat(dst, "abcdefghijklmnopqrstuvwxyz", 20, 31);
    test_ft_strlcat(dst, "abcdefghijklmnopqrstuvwxyz", 5, 12);
    test_ft_strlcat(dst, "", 20, 12);
    test_ft_strlcat("", "hello", 20, 5);
    test_ft_strlcat(NULL, "world", 20, 0);
    test_ft_strlcat(NULL, NULL, 20, 0);
    return 0;
}