/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:57:07 by dhubleur          #+#    #+#             */
/*   Updated: 2024/01/04 15:16:14 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool parse(int argc, char **argv, t_parser *parser)
{
	parser->cmd = NULL;
	parser->help = false;
	
	if (argc < 2)
		return (false);
	for (int i = 1; i < argc; i++)
	{
		if (ft_strlen(argv[i]) == 0)
			return (false);
		
		if (ft_strcmp(argv[i], "-h") == 0)
			parser->help = true;
		else if (argv[i][0] == '-')
			return (false);
		else if (parser->cmd == NULL)
		{
			parser->cmd = argv[i];
			return (true);
		}
	}
	return (false);
}