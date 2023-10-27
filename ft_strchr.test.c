#include <stdio.h>
#include <string.h>
char	*ft_strchr(const char *s, int c);

int main()
{
    char str1[] = "Hello, world!";
    char str2[] = "This is a test string.";
    char str3[] = "Another test string.";
    char str4[] = "This string has a null character \0 in it.";
    char str5[] = "";
    char *result;

    result = ft_strchr(str1, 'o');
    printf("Test 1: %s\n", result);

    result = ft_strchr(str2, 't');
    printf("Test 2: %s\n", result);

    result = ft_strchr(str3, 'z');
    printf("Test 3: %s\n", result);

    result = ft_strchr(str4, '\0') + 1;
    printf("Test 4: %s\n", result);

    result = ft_strchr(str5, 'a');
    printf("Test 5: %s\n", result);

    return 0;
}