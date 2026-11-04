/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 10:18:54 by cmyae             #+#    #+#             */
/*   Updated: 2026/11/03 14:44:36 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	parse_values(t_ps *ps, int argc, char **argv)
{
	int	n;
	int	*vals;

	n = walk_args(argc, argv, NUll);
	if (n < 0)
		ps_error(ps);
	if (n == 0)
		return (0);
	vals = malloc(sizeof(int) * n);
	if (!vals)
		return (0);
	if (walk_args(argc, argv, vals) < 0 || has_duplicates(vals, n))
	{
		free (vals);
		ps_error(ps);
	}
	build_stacks(ps, vals, n);
	return (n);
}

int	walk_args(int argc, char **argv, int *vals)
{
	char	**words;
	int		i;
	int		n;

	i = 1;
	while (i < argc && n >= 0)
	{
		if (!is_flag(argv[i]))
		{
			words = ft_split(argv[i], ' ');
			if (!words)
				return (-1);
			n = apply_words(words, vals, n);
			free_split(words);
		}
		i++;
	}
	return (n);
}

int	apply_words(char **words, int *vals, int n)
{
	int	i;
	int	num;

	i = 1;
	num = 0;
	while (words[i])
	{
		if (!parse_int(words[i], num))
			return (-1);
		if (vals)
			vals[n] = num;
		i++;
		n++;
	}
	if (i == 0)
		return (-1);
	return (n);
}

int	rank_of(int *vals, int n, int i)
{
	int	j;
	int	rank;

	j = 0;
	rank = 0;
	while (j < n)
	{
		if (vals[j] < vals[i])
			rank++;
		j++;
	}
	return (rank);
}

void	build_stacks(t_ps *ps, int *vals, int n)
{
	int	i;

	ps->a.array = malloc(sizeof(int) * n);
	ps->b.array = malloc(sizeof(int) * n);
	if (!ps->a.array || !ps->b.array)
	{
		free(vals);
		ps_error(ps);
	}
	ps->a.cap = n;
	ps->b.cap = n;
	ps->a.size = n;
	i = 0;
	while (vals[i])
	{
		ps->a.data[i] = rank_of(vals, n, i);
		i++;
	}
	free (vals);
}
