/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:19:09 by dhubleur          #+#    #+#             */
/*   Updated: 2024/01/05 13:48:31 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASIC_PARSER_H
# define BASIC_PARSER_H

# include "libft.h"
# include <stdbool.h>

typedef enum {
	ENCODE,
	DECODE,
}	t_basic_cipher_mode;

typedef struct {
	t_basic_cipher_mode	mode;
	char			*input;
	char			*output;
	bool help;
	bool newline;
}	t_basic_cipher_parser;

bool basic_cipher_parse(int argc, char **argv, t_basic_cipher_parser *parser);

#endif