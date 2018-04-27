/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mc.maxcanal@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 16:01:55 by mcanal            #+#    #+#             */
/*   Updated: 2018/04/27 16:07:13 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

char			*get_env(char *key)
{
	char	**env;
	size_t	len;

	if (!environ)
		return (NULL);
	env = environ;
	while (*env)
	{
		len = ft_strlen(key);
		if (!ft_memcmp(key, *env, len) && *(*env + len) == '=')
			return (*env + len + 1);
		env++;
	}
	return (NULL);
}
