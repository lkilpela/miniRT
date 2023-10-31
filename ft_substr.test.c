#include <stdio.h>
#include <string.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);

int main(void)
{
	char const *s = "Hello, world!";
	char *result;

	// Test 1: Extracting a substring from the beginning of the string
	result = ft_substr(s, 0, 5);
	printf("Test 1: %s\n", result); // Expected output: "Hello"
	free(result);

	// Test 2: Extracting a substring from the middle of the string
	result = ft_substr(s, 7, 5);
	printf("Test 2: %s\n", result); // Expected output: "world"
	free(result);

	// Test 3: Extracting a substring from the end of the string
	result = ft_substr(s, 8, 6);
	printf("Test 3: %s\n", result); // Expected output: "world!"
	free(result);

	// Test 4: Extracting the entire string
	result = ft_substr(s, 0, strlen(s));
	printf("Test 4: %s\n", result); // Expected output: "Hello, world!"
	free(result);

	// Test 5: Extracting a substring that is longer than the original string
	result = ft_substr(s, 0, 20);
	printf("Test 5: %s\n", result); // Expected output: "Hello, world!"
	free(result);

	// Test 6: Extracting a substring starting from a position beyond the end of the string
	result = ft_substr(s, 20, 5);
	printf("Test 6: %s\n", result); // Expected output: ""
	free(result);

	return (0);
}