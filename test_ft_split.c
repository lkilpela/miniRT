#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

void test_ft_split(char const *s, char c, char **expected_result)
{             
    char **result = ft_split(s, c);
    int i = 0;
    if(result == NULL)
    {
        printf("FAIL: ft_split(\"%s\", '%c'\n", s, c);
        return;
    }
    char* current = result[i];
    while (result[i] != NULL || expected_result[i] != NULL)
    {
        if (strcmp(result[i], expected_result[i]) != 0)
        {
            printf("FAIL: ft_split(\"%s\", '%c') => [%s] (expected [%s])\n", s, c, result[i], expected_result[i]);
            return;
        }
        i++;
        current = result[i];
    }
    printf("PASS: ft_split(\"%s\", '%c')\n", s, c);
    free(result);
}

int main()
{
    // Test 1: Split a non-empty string with a non-empty delimiter
    char *expected_result1[] = {"Hello", "world", "how", "are", "you", NULL};
    test_ft_split("Hello world how are you", ' ', expected_result1);

    // Test 2: Split a non-empty string with an empty delimiter
    char *expected_result2[] = {"H", "e", "l", "l", "o", NULL};
    test_ft_split("Hello", '\0', expected_result2);

    // Test 3: Split an empty string with a non-empty delimiter
    char *expected_result3[] = {NULL};
    test_ft_split("", ' ', expected_result3);

    // Test 4: Split a string with a delimiter that doesn't appear in the string
    char *expected_result4[] = {"Hello,world,how,are,you", NULL};
    test_ft_split("Hello,world,how,are,you", '!', expected_result4);

    // Test 5: Split a string with a delimiter at the beginning
    char *expected_result5[] = {"hello!", NULL};
    test_ft_split("xxxxxxxxhello!", 'x', expected_result5);

    // Test 6: Split a string with a delimiter that doesn't appear in the string
    char *expected_result6[] = {"hello!", NULL};
    test_ft_split("hello!", ' ', expected_result6);

    // Test 7: Split a string with a delimiter at the end
    char *expected_result7[] = {"hello!", NULL};
    test_ft_split("hello!zzzzzzzz", 'z', expected_result7);

    // Test 8: Split a string with a delimiter being a tab character
    char *expected_result8[] = {"hello!", NULL};
    test_ft_split("\t\t\t\thello!\t\t\t\t", '\t', expected_result8);

    return 0;
}