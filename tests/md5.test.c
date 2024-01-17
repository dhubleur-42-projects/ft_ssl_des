/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:57:08 by dhubleur          #+#    #+#             */
/*   Updated: 2024/01/17 15:25:02 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <check.h>
#include <stdlib.h>
#include <fcntl.h>
#include "algorithms/hash/md5.h"

uint8_t md5_hash_42[16] = {0xa1, 0xd0, 0xc6, 0xe8, 0x3f, 0x02, 0x73, 0x27, 0xd8, 0x46, 0x10, 0x63, 0xf4, 0xac, 0x58, 0xa6};

START_TEST(hash_to_string) {
	char *output;
	convert_hash_to_string(md5_hash_42, 16, &output);
	ck_assert_str_eq(output, "a1d0c6e83f027327d8461063f4ac58a6");
	free(output);
} END_TEST

START_TEST(short_string) {
  char *input = "42";
  uint8_t output[16];
  md5_string(input, output);
  for (int i = 0; i < 16; i++)
	ck_assert_int_eq(output[i], md5_hash_42[i]);
} END_TEST

START_TEST(long_string) {
	char input[4242];
	for (int i = 0; i < 4242; i++)
		input[i] = 'a';
	input[4241] = '\0';
	uint8_t output[16];
	md5_string(input, output);
	uint8_t theorical_output[16] = {0x50, 0x17, 0x97, 0x29, 0xc7, 0xcd, 0x46, 0xa9, 0x7b, 0x95, 0x1c, 0x4f, 0x2a, 0x01, 0x50, 0xb2};
	for (int i = 0; i < 16; i++)
		ck_assert_int_eq(output[i], theorical_output[i]);
}

START_TEST(short_file) {
	char *filename = "tests/utils/short_file";
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
		ck_abort_msg("Cannot open file %s", filename);
	uint8_t output[16];
	md5_file(fd, output);
	close(fd);
	for (int i = 0; i < 16; i++)
		ck_assert_int_eq(output[i], md5_hash_42[i]);
}

START_TEST(long_file) {
	char *filename = "tests/utils/long_file";
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
		ck_abort_msg("Cannot open file %s", filename);
	uint8_t output[16];
	md5_file(fd, output);
	close(fd);
	uint8_t theorical_output[16] = {0xf2, 0xda, 0xfe, 0xc3, 0xa0, 0x68, 0x05, 0x02, 0x0a, 0x6d, 0x35, 0x2a, 0x76, 0xc6, 0x53, 0xcc};
	for (int i = 0; i < 16; i++)
		ck_assert_int_eq(output[i], theorical_output[i]);
}

Suite *md5_suite(void) {
  Suite *s = suite_create("MD5");
  TCase *tc_hash = tcase_create("Hash");

  tcase_add_test(tc_hash, hash_to_string);
  tcase_add_test(tc_hash, short_string);
  tcase_add_test(tc_hash, long_string);
  tcase_add_test(tc_hash, short_file);
  tcase_add_test(tc_hash, long_file);
  suite_add_tcase(s, tc_hash);

  return s;
}