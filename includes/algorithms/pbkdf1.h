/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:49:28 by dhubleur          #+#    #+#             */
/*   Updated: 2024/01/16 14:23:56 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PBKDF1_H
# define PBKDF1_H

# include "libft.h"
# include "algorithms/hash/sha256.h"

# include <stdbool.h>

# define PBKDF1_ITERATIONS 10000

bool	pbkdf1(char *password, uint8_t salt[8], uint8_t key[8]);

#endif