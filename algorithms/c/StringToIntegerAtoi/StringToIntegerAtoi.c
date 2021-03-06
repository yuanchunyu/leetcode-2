/*
 * StringToIntegerAtoi.c
 *
 *  Created on: Aug 30, 2016
 *      Author: xinsu
 */

/*
 Implement atoi to convert a string to an integer.

 Hint: Carefully consider all possible input cases.
 If you want a challenge, please do not see below and ask yourself what are the possible input cases.

 Notes: It is intended for this problem to be specified vaguely (ie, no given input specs).
 You are responsible to gather all the input requirements up front.

 spoilers alert... click to show requirements for atoi.

 Requirements for atoi:
 The function first discards as many whitespace characters as necessary until the first non-whitespace character is found.
 Then, starting from this character,
 takes an optional initial plus or minus sign followed by as many numerical digits as possible,
 and interprets them as a numerical value.

 The string can contain additional characters after those that form the integral number,
 which are ignored and have no effect on the behavior of this function.

 If the first sequence of non-whitespace characters in str is not a valid integral number,
 or if no such sequence exists because either str is empty or it contains only whitespace characters,
 no conversion is performed.

 If no valid conversion could be performed, a zero value is returned.
 If the correct value is out of the range of representable values,
 INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.
 */

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#define OUT 0
#define READY 1
#define IN 2
#define END 3

int myAtoi(char* str) {
	int length = strlen(str);

	if (length == 0) {
		return 0;
	}

	int sign = 1;
	int idxStart = 0;
	int idxStop = 0;

	int state = OUT;
	int i = 0;
	while (state != END) {
		if (state == OUT) {
			if (str[i] == '+' || str[i] == '-') {
				sign = str[i] == '-' ? -1 : 1;
				state = READY; // change state
			} else if (str[i] >= '0' && str[i] <= '9') {
				idxStart = i;
				state = IN; // change state
			} else if (str[i] == '\0') {
				idxStop = -1;
				state = END; // change state
			} else if (str[i] != ' ') {
				idxStop = -1;
				state = END; // change state
			}
		} else if (state == READY) {
			if (str[i] >= '0' && str[i] <= '9') {
				idxStart = i;
				state = IN; // change state
			} else if (str[i] == '\0') {
				idxStop = -1;
				state = END; // change state
			} else {
				idxStop = -1;
				state = END; // change state
			}
		} else if (state == IN) {
			if (str[i] < '0' || str[i] > '9') {
				idxStop = i - 1;
				state = END; // change state
			}
		}

		i++;
	}

	int result = 0;
	for (i = 0; i < idxStop - idxStart + 1; i++) {
		/*
		 * From 7. Reverse Integer. Changed
		 */
		int remain = sign * (str[idxStart + i] - '0');
		if (remain >= 0 && result > (INT_MAX - remain) / 10) {
			return INT_MAX;
		} else if (remain <= 0 && result < (INT_MIN - remain) / 10) {
			return INT_MIN;
		}

		result = result * 10 + remain;
	}

	return result;
}
