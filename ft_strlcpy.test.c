#include <stdio.h>
#include <string.h>
#include "libft.h"

int main()
{
	char src1[] = "Hello";
	char dst1[10];
	size_t ret1 = ft_strlcpy(dst1, src1, 10);
	size_t expected1 = strlen(src1);
	printf("Test Case 1\n");
	printf("Expected: %zu\n", expected1);
	printf("Got: %zu\n", ret1);
	printf("src: %s\n", src1);
	printf("dst: %s\n", dst1);
	if (ret1 == expected1 && strcmp(src1, dst1) == 0)
		printf("PASS\n");
	else
		printf("FAIL\n");

	char src2[] = "Hello";
	char dst2[5];
	size_t ret2 = ft_strlcpy(dst2, src2, 5);
	size_t expected2 = strlen(src2);
	printf("\nTest Case 2\n");
	printf("Expected: %zu\n", expected2);
	printf("Got: %zu\n", ret2);
	printf("src: %s\n", src2);
	printf("dst: %s\n", dst2);
	if (ret2 == expected2 && strncmp(src2, dst2, 5) == 0)
		printf("PASS\n");
	else
		printf("FAIL\n");

	char src3[] = "";
	char dst3[10];
	size_t ret3 = ft_strlcpy(dst3, src3, 10);
	size_t expected3 = strlen(src3);
	printf("\nTest Case 3\n");
	printf("Expected: %zu\n", expected3);
	printf("Got: %zu\n", ret3);
	printf("src: %s\n", src3);
	printf("dst: %s\n", dst3);
	if (ret3 == expected3 && strcmp(src3, dst3) == 0)
		printf("PASS\n");
	else
		printf("FAIL\n");

	char src4[] = "Hello";
	char dst4[0];
	size_t ret4 = ft_strlcpy(dst4, src4, 0);
	size_t expected4 = strlen(src4);
	printf("\nTest Case 4\n");
	printf("Expected: %zu\n", expected4);
	printf("Got: %zu\n", ret4);
	printf("src: %s\n", src4);
	printf("dst: %s\n", dst4);
	if (ret4 == expected4 && strcmp(src4, dst4) == 0)
		printf("PASS\n");
	else
		printf("FAIL\n");

	return (0);
}