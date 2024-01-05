/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:44:26 by dhubleur          #+#    #+#             */
/*   Updated: 2024/01/05 13:49:11 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/cipher/basic_parser.h"

static bool parse_option_string(t_basic_cipher_parser *parser, char *str, bool *is_next_arg_input, bool *is_next_arg_output)
{
	for (int i = 1; str[i]; i++)
	{
		if (str[i] == 'h')
			parser->help = true;
		else if (str[i] == 'd')
			parser->mode = DECODE;
		else if (str[i] == 'e')
			parser->mode = ENCODE;
		else if (str[i] == 'i')
			*is_next_arg_input = true;
		else if (str[i] == 'o')
			*is_next_arg_output = true;
		else if (str[i] == 'n')
			parser->newline = true;
		else
		{
			ft_putstr_fd("Unknown option: ", 2);
			ft_putchar_fd(str[i], 2);
			ft_putchar_fd('\n', 2);
			return (false);
		}
	}
	return (true);
}

bool basic_cipher_parse(int argc, char **argv, t_basic_cipher_parser *parser)
{
	parser->mode = ENCODE;
	parser->input = NULL;
	parser->output = NULL;
	parser->help = false;
	parser->newline = false;

	bool is_next_arg_input = false;
	bool is_next_arg_output = false;

	for (int i = 2; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			if (is_next_arg_input || is_next_arg_output)
			{
				ft_putstr_fd("Need an argument after option\n", 2);
				return (false);
			}
			if (!parse_option_string(parser, argv[i], &is_next_arg_input, &is_next_arg_output))
				return (false);
			if (is_next_arg_input && is_next_arg_output)
			{
				ft_putstr_fd("Can't have input and output at the same time\n", 2);
				return (false);
			}
		}
		else
		{
			if (is_next_arg_input)
			{
				parser->input = argv[i];
				is_next_arg_input = false;
			}
			else if (is_next_arg_output)
			{
				parser->output = argv[i];
				is_next_arg_output = false;
			}
			else
			{
				ft_putstr_fd("Unknown argument: ", 2);
				ft_putstr_fd(argv[i], 2);
				ft_putchar_fd('\n', 2);
				return (false);
			}
		}
	}
	if (is_next_arg_input || is_next_arg_output)
	{
		ft_putstr_fd("Need an argument after option\n", 2);
		return (false);
	}
	return (true);
}