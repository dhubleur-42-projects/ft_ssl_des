/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:34:57 by dhubleur          #+#    #+#             */
/*   Updated: 2024/01/04 13:09:33 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNNER_H
# define RUNNER_H

# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>

# include "libft.h"
# include "utils/hash/parser.h"
# include "algorithms/hash/md5.h"
# include "algorithms/hash/sha256.h"

typedef void (*t_hash_string_runner)(char *, uint8_t *);
typedef bool (*t_hash_file_runner)(int, uint8_t *);

typedef struct {
	char *name;
	t_hash_string_runner string_runner;
	t_hash_file_runner file_runner;
	int hash_length;
} t_hash_runner;

bool hash_run(t_hash_parser parser, t_hash_argument argument, char *res[2]);
void hash_print(t_hash_parser parser, t_hash_argument argument, bool is_stdin, char *hash);
bool hash_is_valid_command(char *command);

#endif