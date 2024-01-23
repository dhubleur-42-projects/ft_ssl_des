/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:49:40 by dhubleur          #+#    #+#             */
/*   Updated: 2024/01/23 14:15:44 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithms/pbkdf1.h"

bool	pbkdf1(char *password, uint8_t salt[8], uint8_t key[8])
{
	_sha256_context_t context;

	_sha256_init(&context);
	_sha256_fill_and_run_if_complete(&context, (uint8_t *)password, ft_strlen(password));
	_sha256_fill_and_run_if_complete(&context, salt, 8);
	_sha256_padd_and_finalize(&context);

	uint8_t store[32];
	ft_memcpy(store, context.digest, 32);

	for (int i = 1; i < PBKDF1_ITERATIONS; i++)
	{
		_sha256_init(&context);
		_sha256_fill_and_run_if_complete(&context, store, 32);
		_sha256_padd_and_finalize(&context);
		ft_memcpy(store, context.digest, 32);
	}

	ft_memcpy(key, store, 8);

	return true;
}