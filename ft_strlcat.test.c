#include <stdio.h>
#include <string.h>
#include "libft.h"

void test_ft_strlcat(char *dst, char *src, size_t dstsize)
{
    size_t expected = strlcat(dst, src, dstsize);
    size_t result = ft_strlcat(dst, src, dstsize);
    if (result != expected)
        printf("FAIL: expected %zu but got %zu\n", expected, result);
    else
        printf("PASS\n");
}

int main()
{
    char dst[10] = "abc";
    char *src = "def";
    test_ft_strlcat(dst, src, 10); // should pass
    test_ft_strlcat(dst, src, 5); // should pass
    test_ft_strlcat(dst, src, 3); // should pass
    test_ft_strlcat(dst, src, 2); // should fail
    test_ft_strlcat(dst, src, 0); // should pass
    return (0);
}