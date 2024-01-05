/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:44:25 by dhubleur          #+#    #+#             */
/*   Updated: 2024/01/05 13:46:36 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithms/cipher/base64.h"

static const char *base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char *base64_encode(char *input)
{
	int input_length = ft_strlen(input);
	int pad_length = 2 - (input_length % 3 - 1);
	int output_length = input_length * 4 / 3 + pad_length;
	char *output = malloc(output_length + 1);
	if (!output)
		return NULL;
	output[output_length] = '\0';

	int i = 0;
	int j = 0;
	while (i < input_length)
	{
		uint32_t octet_a = (i < input_length ? (unsigned char)input[i++] : 0);
		uint32_t octet_b = (i < input_length ? (unsigned char)input[i++] : 0);
		uint32_t octet_c = (i < input_length ? (unsigned char)input[i++] : 0);

		uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

		output[j++] = base64_chars[(triple >> 3 * 6) & 0x3F];
		output[j++] = base64_chars[(triple >> 2 * 6) & 0x3F];
		output[j++] = base64_chars[(triple >> 1 * 6) & 0x3F];
		output[j++] = base64_chars[(triple >> 0 * 6) & 0x3F];
	}

	for (int i = 0; i < pad_length; i++)
		output[output_length - i] = '=';

	return output;
}

static bool is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

char *base64_decode(char *input)
{

	int k = 0;
	while (input[k] != '\0')
	{
		if (is_whitespace(input[k]))
		{
			ft_strcpy(input + k, input + k + 1);
			k--;
		}
		k++;
	}

    char decoding_table[256];
	for (int i = 0; i < 64; i++)
        decoding_table[(unsigned char) base64_chars[i]] = i;

	int input_length = ft_strlen(input);
    if (input_length % 4 != 0)
		return NULL;

    int output_length = input_length / 4 * 3;
    if (input[input_length - 1] == '=') (output_length)--;
    if (input[input_length - 2] == '=') (output_length)--;

    char *output = malloc(output_length);
    if (!output)
		return NULL;

    for (int i = 0, j = 0; i < input_length;) {

        uint32_t sextet_a = input[i] == '=' ? 0 & i++ : decoding_table[(unsigned char) input[i++]];
        uint32_t sextet_b = input[i] == '=' ? 0 & i++ : decoding_table[(unsigned char) input[i++]];
        uint32_t sextet_c = input[i] == '=' ? 0 & i++ : decoding_table[(unsigned char) input[i++]];
        uint32_t sextet_d = input[i] == '=' ? 0 & i++ : decoding_table[(unsigned char) input[i++]];

        uint32_t triple = (sextet_a << 3 * 6)
        + (sextet_b << 2 * 6)
        + (sextet_c << 1 * 6)
        + (sextet_d << 0 * 6);

        if (j < output_length) output[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < output_length) output[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < output_length) output[j++] = (triple >> 0 * 8) & 0xFF;
    }

    return output;
}
