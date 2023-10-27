#include <stdio.h>
#include <ctype.h>

int ft_toupper(int c);

int main(void)
{
    int test_cases[] = {'a', 'A', 'z', 'Z', '!', '1', ' '};
    int expected[] = {'A', 'A', 'Z', 'Z', '!', '1', ' '};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++)
    {
        int result = ft_toupper(test_cases[i]);
        if (result != expected[i])
        {
            printf("Test case %d failed: expected %c but got %c\n", i+1, expected[i], result);
        }
    }

    printf("Tests complete\n");
    return 0;
}