/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 10:26:46 by cmyae             #+#    #+#             */
/*   Updated: 2026/11/03 10:26:52 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	compute_disorder(t_stack *s)
{
	long	mistakes;
	long	pairs;
	int		i;
	int		j;

	pairs = (long)s->size * (s->size - 1) / 2;
	if (pairs == 0)
		return (0.0);
	mistakes = 0;
	i = -1;
	while (++i < s->size)
	{
		j = i;
		while (++j < s->size)
		{
			if (stack_at(s, i) > stack_at(s, j))
				mistakes++;
		}
	}
	return ((double)mistakes / (double)pairs);
}
