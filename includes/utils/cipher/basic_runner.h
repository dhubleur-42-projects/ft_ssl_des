/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_runner.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:55:20 by dhubleur          #+#    #+#             */
/*   Updated: 2024/01/04 16:51:07 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASIC_RUNNER_H
# define BASIC_RUNNER_H

# include "algorithms/cipher/base64.h"
# include "utils/cipher/basic_parser.h"
# include "utils.h"
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>


typedef char * (*t_basic_cipher_runner)(char *);

typedef struct	s_basic_cipher
{
	char				*name;
	t_basic_cipher_runner	encode_runner;
	t_basic_cipher_runner	decode_runner;
}				t_basic_cipher;

int basic_cipher_run(int argc, char **argv);
bool basic_cipher_is_valid_command(char *command);

#endif