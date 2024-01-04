/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:19:09 by dhubleur          #+#    #+#             */
/*   Updated: 2024/01/04 13:07:39 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include <stdbool.h>

typedef enum {
	FILE_NAME,
	STRING,
}	HASH_ARG_TYPE;

typedef struct {
	char *name;
	HASH_ARG_TYPE type;
}	t_hash_argument;

typedef struct {
	bool help;
	bool printing;
	bool quiet;
	bool reverse;
	char *command;
	int arguments_count;
	t_hash_argument *arguments;
}	t_hash_parser;

bool	hash_parse(t_hash_parser *parser, int argc, char **argv);
void 	hash_free_parser(t_hash_parser *parser);

#endif