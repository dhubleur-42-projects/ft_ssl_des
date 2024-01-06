/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:49:40 by dhubleur          #+#    #+#             */
/*   Updated: 2024/01/06 15:32:36 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithms/pbkdf1.h"

bool	pbkdf1(char *password, uint8_t salt[8], uint8_t key[8])
{
	char *concat = malloc(sizeof(char) * (ft_strlen(password) + 8 + 1));
	if (!concat)
		return false;
	ft_strcpy(concat, password);
	ft_memcpy(concat + ft_strlen(password), salt, 8);

	uint8_t sha256_res[32];
	sha256_string(concat, sha256_res);

	char input[33];
	for (int i = 0; i < PBKDF1_ITERATIONS-1; i++)
	{
		ft_memcpy(input, sha256_res, 32);
		input[32] = '\0';
		sha256_string(input, sha256_res);
	}
	ft_memcpy(key, sha256_res, 8);

	return true;
}