/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:44:26 by dhubleur          #+#    #+#             */
/*   Updated: 2024/01/05 13:50:00 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithms/cipher/base64.h"
#include "utils/cipher/basic_runner.h"

#define BASIC_CIPHER_RUNNERS_COUNT 1
const static t_basic_cipher basic_cipher_runners[BASIC_CIPHER_RUNNERS_COUNT] = {
	(t_basic_cipher){ "base64",  base64_encode, base64_decode},
};

bool basic_cipher_is_valid_command(char *command)
{
	for (int i = 0; i < BASIC_CIPHER_RUNNERS_COUNT; i++)
	{
		if (ft_strcmp(basic_cipher_runners[i].name, command) == 0)
			return true;
	}
	return false;
}

static void print_help()
{
	ft_putstr_fd("Usage: ./ft_ssl COMMAND [OPTIONS]\n\n", 1);
	ft_putstr_fd("Cipher stdin/file using a specifed algorithm\n\n", 1);
	ft_putstr_fd("The COMMAND argument must be one of:\n", 1);
	ft_putstr_fd("\tbase64\n", 1);
	ft_putstr_fd("\nOPTIONS:\n", 1);
	ft_putstr_fd("\t-h\tPrint this help\n", 1);
	ft_putstr_fd("\t-e\tEncode mode\n", 1);
	ft_putstr_fd("\t-d\tDecode mode\n", 1);
	ft_putstr_fd("\t-i\tUse a file as input\n", 1);
	ft_putstr_fd("\t-o\tUse a file as output\n", 1);
	ft_putstr_fd("\t-n\tPrint a newline every 64 characters\n", 1);
}

int basic_cipher_run(int argc, char **argv)
{
	t_basic_cipher_parser parser;
	if (!basic_cipher_parse(argc, argv, &parser))
		return (1);

	if (parser.help)
	{
		print_help();
		return (0);
	}

	char *content = NULL;
	if (parser.input)
	{
		int fd = open(parser.input, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("ft_ssl: ", 2);
			ft_putstr_fd(parser.input, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
		content = read_file(fd);
		close(fd);
		if (!content)
		{
			ft_putstr_fd("ft_ssl: ", 2);
			ft_putstr_fd(parser.input, 2);
			ft_putstr_fd(": Cannot read file\n", 2);
			return (1);
		}
	}
	else
	{
		content = read_stdin();
		if (!content)
		{
			ft_putstr_fd("ft_ssl: Cannot read stdin\n", 2);
			return (1);
		}
	}

	if (!basic_cipher_is_valid_command(argv[1]))
	{
		ft_putstr_fd("ft_ssl: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": Invalid command\n", 2);
		return (1);
	}

	t_basic_cipher runner;
	for (int i = 0; i < BASIC_CIPHER_RUNNERS_COUNT; i++)
	{
		if (ft_strcmp(basic_cipher_runners[i].name, argv[1]) == 0)
		{
			runner = basic_cipher_runners[i];
			break;
		}
	}

	char *res = parser.mode == ENCODE ? runner.encode_runner(content) : runner.decode_runner(content);
	if (!res)
	{
		ft_putstr_fd("ft_ssl: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": Cannot encode/decode\n", 2);
		return (1);
	}

	int output_fd = 1;
	if (parser.output)
	{
		output_fd = open(parser.output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (output_fd == -1)
		{
			ft_putstr_fd("ft_ssl: ", 2);
			ft_putstr_fd(parser.output, 2);
			ft_putstr_fd(": Cannot open file\n", 2);
			return (1);
		}
	}

	if (parser.mode == ENCODE && parser.newline)
	{
		int i = 0;
		while (res[i] != '\0')
		{
			ft_putchar_fd(res[i], output_fd);
			if (i % 64 == 63)
				ft_putchar_fd('\n', output_fd);
			i++;
		}
		if (i % 64 != 0)
			ft_putchar_fd('\n', output_fd);
	}
	else
	{
		ft_putstr_fd(res, output_fd);
		if (parser.mode == ENCODE)
			ft_putstr_fd("\n", output_fd);
	}

	free(content);
	free(res);

	return (0);
}