/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: 2Ahif
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			Pyramid of Numbers
 * Author:		Ivonne Gattringer
 * ----------------------------------------------------------
 * Description:
 * Calculates a pyramid of numbers, i.e., it multiplies a big
 * integer by the number 2, its result by 3, etc. and then
 * returns to the original value by subsequently dividing,
 * again starting by 2, 3, etc.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>

/// The maximum number of digits allowed in a big int.
#define MAX_DIGITS 80

/** BigInt represents an integer number which can have MAX_DIGITS digits
*** @see MAX_DIGITS
*/
struct BigInt {
	/** number of digits of the big int. */
	int digits_count;

	/** array of digits of big int. */
	unsigned int the_int[MAX_DIGITS];
};

void print_big_int(const struct BigInt *big_int)
{
	for (int i = big_int -> digits_count -1; i >=0; i--) {
		printf("%d",big_int-> the_int[i]);
	}
	printf("\n" );
}
int strtobig_int(const char *str, int len, struct BigInt *big_int)
{
	int count = len -1;
	for (int i = 0; i < len; i++) {
		if ('0' <= str[i] && str[i] <= '9')
			big_int->the_int[count] = str[i]-'0';
		else return i;
		count--;
	}
	return len;
}
void multiply(const struct BigInt *big_int,int factor, struct BigInt *big_result)
{
	int carry = 0;
		for (int i = 0; i < big_int -> digits_count ; i++)
		{
			int product = big_int -> the_int[i] * factor +carry;
			carry = product /10;
			big_result->the_int[i] = product%10;

		}
	if(carry != 0){ big_result->digits_count++; big_result->the_int[big_result->digits_count-1] = carry;}
}

void divide(struct BigInt *big_int, int divisor, struct BigInt *big_result)
{
	//int overflow = big_int->the_int[big_int-> digits_count-1];
	int overflow  = 0;
	int count = 0;
	int sum = 0;
	for (int i = big_int-> digits_count-1; i > -1; i--)
	{
			//big_result -> the_int[i] = overflow/divisor;
			//overflow = overflow % divisor + big_int->the_int[i-1];
			int quotient = big_int->the_int[i] + overflow*10;
			big_result->the_int[i] = quotient/divisor;
			overflow =  quotient % divisor;
			sum+= big_result->the_int[i];
			if(big_result->the_int[i] == 0&& sum == 0){
				count++;
			}
	}
	big_int->digits_count -= count;
}

void copy_big_int(const struct BigInt *from, struct BigInt *to){
	to->digits_count = from->digits_count;
	for(int i = from->digits_count-1; i>= 0; i--){
		to->the_int[i] = from->the_int[i];
	}
}

int main(int argc, char *argv[])
{
	printf("Pyramid of numbers \n\n");
	printf("Ender your number: ");
	char input[MAX_DIGITS];
	scanf("%s",input);
	int len = strlen(input);
	if(len > MAX_DIGITS){
		printf("Error -1\n" );
		return 0;
	}

	struct BigInt big_int;
	big_int.digits_count = strtobig_int(input, len, &big_int);
	if(big_int.digits_count != len) {
		printf("ERROR! You used a letter!\n" );
		return 0;
	}

	struct BigInt big_result;
	big_result.digits_count = big_int.digits_count;
	print_big_int(&big_int);
	for (int i = 2; i <= 9; i++) {
		printf(" * %d\n", i);
		multiply(&big_int, i, &big_result);
		print_big_int(&big_result);
		copy_big_int(&big_result, &big_int);
	}

	copy_big_int(&big_result, &big_int);

	print_big_int(&big_int);
	for (int i = 2; i <= 9; i++) {
		printf(" / %d\n", i);
		divide(&big_int, i, &big_result);
		print_big_int(&big_result);
		copy_big_int(&big_result, &big_int);
	}

	return 0;
}
