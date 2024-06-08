/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbogdano <bbogdano@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:40:19 by bbogdano          #+#    #+#             */
/*   Updated: 2023/06/24 21:36:25 by bbogdano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//args: pointer to first node, new node
// Adds a new element to the start of a linked list.
// It first checks if the 'new' node exists, if not it does nothing.
// If 'new' exists, it links 'new' to the first element in the list,
// and then updates the list pointer to point to 'new',

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new)
	{
		new -> next = *lst;
		*lst = new;
	}
}
