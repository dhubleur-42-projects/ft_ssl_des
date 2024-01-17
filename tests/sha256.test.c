/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:57:08 by dhubleur          #+#    #+#             */
/*   Updated: 2024/01/17 16:39:12 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <check.h>
#include <stdlib.h>
#include <fcntl.h>
#include "algorithms/hash/md5.h"

uint8_t sha256_hash_42[32] = {0x73, 0x47, 0x5c, 0xb4, 0x0a, 0x56, 0x8e, 0x8d, 0xa8, 0xa0, 0x45, 0xce, 0xd1, 0x10, 0x13, 0x7e, 0x15, 0x9f, 0x89, 0x0a, 0xc4, 0xda, 0x88, 0x3b, 0x6b, 0x17, 0xdc, 0x65, 0x1b, 0x3a, 0x80, 0x49};

START_TEST(hash_to_string) {
	char *output;
	convert_hash_to_string(sha256_hash_42, 32, &output);
	ck_assert_str_eq(output, "73475cb40a568e8da8a045ced110137e159f890ac4da883b6b17dc651b3a8049");
	free(output);
} END_TEST

START_TEST(short_string) {
  char *input = "42";
  uint8_t output[32];
  sha256_string(input, output);
  for (int i = 0; i < 32; i++)
	ck_assert_int_eq(output[i], sha256_hash_42[i]);
} END_TEST

START_TEST(long_string) {
	char input[4242];
	for (int i = 0; i < 4242; i++)
		input[i] = 'a';
	input[4241] = '\0';
	uint8_t output[32];
	sha256_string(input, output);
	uint8_t theorical_output[32] = {0x2b, 0x69, 0x18, 0x87, 0x29, 0xe5, 0x62, 0x66, 0x5c, 0x1d, 0xa9, 0xf8, 0x7c, 0x44, 0x6b, 0x8b, 0x7e, 0x2d, 0x8a, 0x46, 0xa7, 0xe0, 0xb3, 0x33, 0xf9, 0x2f, 0x64, 0x6e, 0x1d, 0xfe, 0x5a, 0x9d};
	for (int i = 0; i < 32; i++)
		ck_assert_int_eq(output[i], theorical_output[i]);
}

START_TEST(short_file) {
	char *filename = "tests/utils/short_file";
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
		ck_abort_msg("Cannot open file %s", filename);
	uint8_t output[32];
	sha256_file(fd, output);
	close(fd);
	for (int i = 0; i < 32; i++)
		ck_assert_int_eq(output[i], sha256_hash_42[i]);
}

START_TEST(long_file) {
	char *filename = "tests/utils/long_file";
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
		ck_abort_msg("Cannot open file %s", filename);
	uint8_t output[32];
	sha256_file(fd, output);
	close(fd);
	uint8_t theorical_output[32] = {0xd1, 0x1d, 0xbc, 0x54, 0xa2, 0x14, 0x69, 0xfd, 0xb7, 0x77, 0x87, 0x7c, 0x36, 0x87, 0xe2, 0x3b, 0x1c, 0xee, 0x91, 0xf3, 0xb1, 0x0c, 0x18, 0xe3, 0x26, 0xae, 0xb8, 0x87, 0x02, 0x1b, 0x36, 0x65};
	for (int i = 0; i < 32; i++)
		ck_assert_int_eq(output[i], theorical_output[i]);
}

Suite *sha256_suite(void) {
  Suite *s = suite_create("SHA256");
  TCase *tc_hash = tcase_create("Hash");

  tcase_add_test(tc_hash, hash_to_string);
  tcase_add_test(tc_hash, short_string);
  tcase_add_test(tc_hash, long_string);
  tcase_add_test(tc_hash, short_file);
  tcase_add_test(tc_hash, long_file);
  suite_add_tcase(s, tc_hash);

  return s;
}