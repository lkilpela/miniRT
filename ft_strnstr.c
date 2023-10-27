/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:32:56 by lkilpela          #+#    #+#             */
/*   Updated: 2023/10/27 15:34:14 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/*
The strnstr() function locates the first occurrence of the null-terminated string
needle in the string haystack, where not more than len characters are searched.  Char-
acters that appear after a `\0' character are not searched.  Since the strnstr() func-
tion is a FreeBSD specific API, it should only be used when portability is not a con-
cern.
RETURN VALUES
     If needle is an empty string, haystack is returned; if needle occurs nowhere in
     haystack, NULL is returned; otherwise a pointer to the first character of the first
     occurrence of needle is returned.
	 
	 */