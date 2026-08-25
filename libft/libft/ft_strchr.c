char	*ft_strchr(const char *s, int c)
{
	char	*first_character;

	*first_character = NULL;
	while (*s)
	{
		if (*s == (char)c)
			*first_character = (char *)s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (first_character);
}
