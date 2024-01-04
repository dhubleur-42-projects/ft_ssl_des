/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:33:28 by dhubleur          #+#    #+#             */
/*   Updated: 2024/01/04 15:19:03 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils/hash/runner.h"

typedef bool (*t_is_command_type)(char *);
typedef int (*t_type_runner)(int, char **);
typedef struct {
	t_is_command_type is_command_type;
	t_type_runner runner;
}	t_type_runner_storage;

#define TYPE_RUNNERS_COUNT 1
const static t_type_runner_storage type_runners[TYPE_RUNNERS_COUNT] = {
	(t_type_runner_storage){ .is_command_type = hash_is_valid_command, .runner = hash_run }
};

void print_cmd_error()
{
	ft_putstr_fd("ft_ssl: Usage: ft_ssl [command] [command opts] [command args]\n", 2);
	ft_putstr_fd("Use 'ft_ssl [command] -h' for more help\n", 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("Standard commands:\n", 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("Message Digest commands:\n", 2);
	ft_putstr_fd("md5\n", 2);
	ft_putstr_fd("sha256\n", 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("Cipher commands:\n", 2);
	ft_putstr_fd("base64\n", 2);
	ft_putstr_fd("des\n", 2);
	ft_putstr_fd("des-ecb\n", 2);
	ft_putstr_fd("des-cbc\n", 2);
}

int	main(int argc, char **argv)
{

	t_parser parser;
	if (!parse(argc, argv, &parser))
	{
		print_cmd_error();
		return (1);
	}
	if (parser.help)
	{
		print_cmd_error();
		return (0);
	}

	for (int i = 0; i < TYPE_RUNNERS_COUNT; i++)
	{
		if (type_runners[i].is_command_type(parser.cmd))
			return (type_runners[i].runner(argc, argv));
	}

	print_cmd_error();
	return (1);
}