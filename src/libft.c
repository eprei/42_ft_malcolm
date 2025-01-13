# include "ft_malcolm.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *d = dst;
	const unsigned char *s = (unsigned char *) src;

	if (src == NULL && dst == NULL)
		return NULL;
	while (n > 0)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return dst;
}

int	ft_strncmp(const char *s1, const char *s2, const size_t n)
{
	unsigned int i = 0;

	while ((*s1 || *s2) && i < n)
	{
		if (*s1 != *s2)
			return (unsigned char)*s1 - (unsigned char)*s2;
		s1++;
		s2++;
		i++;
	}
	return 0;
}

int	ft_tolower(const int c)
{
	if ('A' <= c && c <= 'Z')
		return c + 32;
	return c;
}
