#include <stdio.h>
#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c);
void test_ft_strrchr(const char *s, int c, const char *expected)
{
    char *result = ft_strrchr(s, c);
    if (result == NULL && expected == NULL)
    {
        printf("PASS: ft_strrchr(\"%s\", %d) returned NULL as expected.\n", s, c);
    }
    else if (result == NULL || expected == NULL)
    {
        printf("FAIL: ft_strrchr(\"%s\", %d) returned %p but expected %p.\n", s, c, result, expected);
    }
    else if (strcmp(result, expected) == 0)
    {
        printf("PASS: ft_strrchr(\"%s\", %d) returned \"%s\" as expected.\n", s, c, result);
    }
    else
    {
        printf("FAIL: ft_strrchr(\"%s\", %d) returned \"%s\" but expected \"%s\".\n", s, c, result, expected);
    }
}

int main()
{
    char s1[] = "hello world";
    test_ft_strrchr(s1, 'l', "ld");
    test_ft_strrchr(s1, 'o', "o world");
    test_ft_strrchr(s1, 'x', NULL);
    test_ft_strrchr(s1, '\0', "");
    test_ft_strrchr(s1, 'h', "hello world");
    test_ft_strrchr(s1, 'd', "d");
    test_ft_strrchr(s1, ' ', " world");
    test_ft_strrchr(s1, '!', NULL);

    char s2[] = "";
    test_ft_strrchr(s2, 'a', NULL);
    test_ft_strrchr(s2, '\0', "");

    char s3[] = "aaaaaa";
    test_ft_strrchr(s3, 'a', "a");
    test_ft_strrchr(s3, 'b', NULL);

    return 0;
}