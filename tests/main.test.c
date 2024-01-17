/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:02:23 by dhubleur          #+#    #+#             */
/*   Updated: 2024/01/17 15:04:35 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <check.h>
#include <stdlib.h>

Suite *md5_suite(void);

typedef Suite *(*SuiteFunction)();
SuiteFunction suites[] = {md5_suite, NULL};
int main(void) {
  int no_failed = 0;                   
  
  Suite *s = suites[0]();
  SRunner *runner = srunner_create(s);
  for (int i = 1; suites[i]; i++) {
	s = suites[i]();
	srunner_add_suite(runner, s);
  }

  srunner_run_all(runner, CK_VERBOSE);  
  no_failed = srunner_ntests_failed(runner); 
  srunner_free(runner);                      
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;  
}