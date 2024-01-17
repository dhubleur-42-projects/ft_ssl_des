/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:34:50 by dhubleur          #+#    #+#             */
/*   Updated: 2024/01/17 15:07:59 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/hash/runner.h"

#define HASH_RUNNERS_COUNT 2
const static t_hash_runner hash_runners[HASH_RUNNERS_COUNT] = {
	(t_hash_runner){ "md5", md5_string, md5_file, 16 },
	(t_hash_runner){ "sha256", sha256_string, sha256_file, 32 },
};

bool hash_is_valid_command(char *command)
{
	for (int i = 0; i < HASH_RUNNERS_COUNT; i++)
	{
		if (ft_strcmp(hash_runners[i].name, command) == 0)
			return true;
	}
	return false;
}

bool convert_hash_to_string(uint8_t *hash, int hash_length, char **buffer)
{
	*buffer = malloc(hash_length * 2 + 1);
	if (!*buffer)
	{
		ft_putstr_fd("A malloc failed\n", 2);
		return (false);
	}
	for (int i = 0; i < hash_length; i++)
	{
		(*buffer)[i * 2] = "0123456789abcdef"[hash[i] / 16];
		(*buffer)[i * 2 + 1] = "0123456789abcdef"[hash[i] % 16];
	}
	(*buffer)[hash_length * 2] = '\0';
	return (true);
}

static bool run_element(t_hash_parser parser, t_hash_argument argument, char **res)
{
	t_hash_runner runner = { 0 };
	for (int i = 0; i < HASH_RUNNERS_COUNT; i++)
	{
		if (ft_strcmp(hash_runners[i].name, parser.command) == 0)
		{
			runner = hash_runners[i];
			break;
		}
	}
	if (runner.name == NULL)
		return false;
	uint8_t hash[runner.hash_length];
	if (argument.type == STRING)
		runner.string_runner(argument.name, hash);
	else
	{
		int fd = open(argument.name, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("ft_ssl: ", 2);
			ft_putstr_fd(argument.name, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return false;
		}
		bool res = runner.file_runner(fd, hash);
		close(fd);
		if (!res)
			return false;
	}
	if (!convert_hash_to_string(hash, runner.hash_length, res))
		return false;
	return true;
}

static void print_help()
{
	ft_putstr_fd("Usage: ./ft_ssl COMMAND [OPTIONS] [ARGUMENTS]\n\n", 1);
	ft_putstr_fd("Hash stdin/file/string using a specifed algorithm\n\n", 1);
	ft_putstr_fd("The COMMAND argument must be one of:\n", 1);
	ft_putstr_fd("\tmd5\n", 1);
	ft_putstr_fd("\tsha256\n", 1);
	ft_putstr_fd("\nOPTIONS:\n", 1);
	ft_putstr_fd("\t-h\tPrint this help\n", 1);
	ft_putstr_fd("\t-p\tPrint content of stdin to stdout\n", 1);
	ft_putstr_fd("\t-q\tQuiet mode. Print just the hash\n", 1);
	ft_putstr_fd("\t-r\tReverse the format of the output\n", 1);
	ft_putstr_fd("\t-s\tPrint the sum of the given string\n", 1);
}

int hash_run(int argc, char **argv)
{
	t_hash_parser parser;
	if (!hash_parse(&parser, argc, argv))
	{
		hash_free_parser(&parser);
		return (1);
	}

	if (parser.help)
	{
		print_help();
		hash_free_parser(&parser);
		return (0);
	}

	if (parser.arguments_count == 0 || parser.printing)
	{
		char *stdin_content = read_stdin();
		if (!stdin_content)
		{
			ft_putstr_fd("A malloc failed\n", 2);
			hash_free_parser(&parser);
			return (1);
		}
		t_hash_argument argument = { .type = STRING, .name = stdin_content };
		char *buffer;
		if (!run_element(parser, argument, &buffer))
			free(stdin_content);
		else
		{
			hash_print(parser, argument, true, buffer);
			free(buffer);
			free(stdin_content);
		}
	}
	for (int i = 0; i < parser.arguments_count; i++)
	{
		char *buffer;
		if (run_element(parser, parser.arguments[i], &buffer))
		{
			hash_print(parser, parser.arguments[i], false, buffer);
			free(buffer);
		}
	}

	hash_free_parser(&parser);
	return (0);
}