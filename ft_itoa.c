/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:09:11 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/15 13:17:33 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	convert_to_string_reverse(char *str, int n, int len)
{
	while (n > 0)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
		--len;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		sign;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		sign = -1;
	else
		sign = 1;
	len = intlen(n);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	n *= sign;
	if (n == 0)
		str[0] = '0';
	else
	{
		convert_to_string_reverse(str, n, len - 1);
		if (sign == -1)
			str[0] = '-';
	}
	return (str);
}

/**
* ft_intlen is a helper function that calculates the number of digits in an
integer. If the integer is negative or zero,
it adds one to the count to account for the '-' sign or the '0' digit.

ft_itoa is the main function. It first checks if the input integer n is equal to
INT_MIN, the smallest possible integer. If it is, it returns a string
representing INT_MIN because -INT_MIN is not a valid integer.

It then calculates the sign of n and the length of the string that will be
needed to represent n.

It allocates memory for the string and checks if the allocation was successful.

If n is zero, it sets the first character of the string to '0'.

It then converts n to a positive number if it was negative.

It then fills in the string with the digits of n,
	working from the end of the string back to the beginning.

If n was negative, it adds a '-' sign at the beginning of the string.

Finally, it returns the resulting string.
 *
 */
