/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:06:48 by dhubleur          #+#    #+#             */
/*   Updated: 2024/01/04 15:11:57 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#define STDIN_BUFFER_SIZE 1024

char *read_stdin()
{
	char *buffer = malloc(sizeof(char) * (STDIN_BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	int buffer_size = STDIN_BUFFER_SIZE;
	int readed = 0;
	int total_readed = 0;
	char read_buffer[STDIN_BUFFER_SIZE + 1];
	while ((readed = read(0, read_buffer, STDIN_BUFFER_SIZE)) > 0)
	{
		read_buffer[readed] = '\0';
		if (total_readed + readed >= buffer_size)
		{
			buffer_size *= 2;
			char *new_buffer = malloc(sizeof(char) * (buffer_size + 1));
			if (!new_buffer)
			{
				free(buffer);
				return (NULL);
			}
			ft_strcpy(new_buffer, buffer);
			free(buffer);
			buffer = new_buffer;
		}
		ft_strcat(buffer, read_buffer);
		total_readed += readed;
	}

	return (buffer);
}