/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmyae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 10:26:46 by cmyae             #+#    #+#             */
/*   Updated: 2026/11/03 10:26:52 by cmyae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	largest_pos(t_stack *s, int bol)
{
	int	i;
	int	big;

	i = 1;
	big = 0;
	while (i < s->size)
	{
		if (bol && stack_at(s, i) > stack_at(s, big))
			big = i;
		if (!bol && stack_at(s, i) < stack_at(s, big))
			big = i;
		i++;
	}
	return (big);
}
