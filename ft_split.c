/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:55:00 by lkilpela          #+#    #+#             */
/*   Updated: 2023/11/15 09:53:22 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_word_count(const char *s, char c)
{
	int	count;
	int	in_substring;

	count = 0;
	in_substring = 0;
	while (*s != '\0')
	{
		if (*s == c)
			in_substring = 0;
		else if (*s != c && in_substring == 0)
		{
			in_substring = 1;
			count++;
		}
		s++;
	}
	return (count);
}

/*static void	free_t(char **t)
{
	int	i;

	i = 0;
	while (t[i] != 0)
	{
		free(t[i]);
		i++;
	}
	free(t);
}*/

/*char	**split_into_chars(char const *s)
{
	char	**t;
	int		i;
	int		len;

	len = ft_strlen(s);
	t = (char **)malloc((len + 1) * sizeof(char *));
	if (t == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		t[i] = ft_substr(s, i, 1);
		if (t[i] == NULL)
		{
			free_t(t);
			return (NULL);
		}
		i++;
	}
	t[len] = NULL;
	return (t);
}*/

char	**split_into_words(char const *s, char **t, char c, int word_count)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (j < word_count)
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			start = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			t[j] = ft_substr(s, start, i - start);
			j++;
		}
	}
	t[j] = NULL;
	return (t);
}

char	**ft_split(char const *s, char c)
{
	char	**t;
	int		word_count;

	if (s == NULL)
		return (NULL);
	word_count = get_word_count(s, c);
	t = (char **)malloc((word_count + 1) * sizeof(char *));
	if (t == NULL)
		return (NULL);
	return (split_into_words(s, t, c, word_count));
}

/**
 * 1. get_word_count is a helper function that counts the number of words in the
 * string s separated by the character c.
 *
 * 2. In the ft_split function, first check if s is NULL. If it is, return NULL.
 *
 * 3. Allocate memory for an array of strings t with size equal to the number of
 * words in s (as determined by get_word_count) plus one for the NULL
 * terminator.
 * If memory allocation fails, return NULL.
 *
 * 4. Initialize two counters i and j to 0. i will be used to iterate over s and
 * j will be used to keep track of the current position in t.
 * We then iterate over s. If we encounter the character c, we skip it.
 * If we encounter a character that is not c, we find the start and end of the
 * word and use ft_substr to create a substring for the word.
 *

* 5. We store each word in the array t and increment j to move to the next
	position in t.
 *
 * 6. Finally, we set the last element of t to NULL and return t.

	* Here are some other edge cases you might want to consider in your ft_split
	function:
 * 1. Input string is NULL: Your function should handle this case gracefully,
	likely
 * by returning NULL.
 * 2. Delimiter is '\0': As discussed in previous responses,
	this is not a typical use

	* case for a split function. You might choose to handle it by splitting the
	string
 * into individual characters, or you might choose to return an error or NULL.
 * 3. Input string is empty (""): In this case,
	your function should return an array
 * containing a single NULL pointer.
 * 4. Input string contains no delimiters: In this case,
	your function should return an
 * array containing one string (the entire input string) and a NULL pointer.
 * 5. Input string starts or ends with delimiters,
	or contains multiple consecutive
 * delimiters: Depending on how you want your function to behave,
	you might choose to
 * treat these as empty strings, or you might choose to ignore them.
 */