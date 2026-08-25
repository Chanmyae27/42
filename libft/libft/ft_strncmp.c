int	ft_strncmp(const *s1, const *s2, size_t n)
{
	while (*s1 == *s2 && n > 0)
	{		
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*s1 - *s2);
}
