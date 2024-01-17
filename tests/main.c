/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:02:23 by dhubleur          #+#    #+#             */
/*   Updated: 2024/01/17 14:04:36 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <check.h>
#include <stdlib.h>

START_TEST(first_test) {

  ck_assert_int_eq(5, 5);
  ck_assert_str_eq("US", "USD");

} END_TEST

Suite *test_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Suite");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, first_test);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int no_failed = 0;                   
  Suite *s;                            
  SRunner *runner;                     

  s = test_suite();                   
  runner = srunner_create(s);          

  srunner_run_all(runner, CK_NORMAL);  
  no_failed = srunner_ntests_failed(runner); 
  srunner_free(runner);                      
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;  
}