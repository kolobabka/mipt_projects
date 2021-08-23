#include "UnTst.h"
#include <math.h>

#define NO_ROOTS  0
#define ONE_ROOT  1
#define TWO_ROOTS  2
#define INF_ROOTS  3

//..........................................................

//==========================================================
//!
//! @note this function gives a user a choice to start Unit_Tests or not
//!
//! @return return 1 if it works corretly and -1 if not.
//!
//==========================================================

int choice();

//=========================================================
//! @note this function solves an equation if the first coefficient is not zero
//!
//! @param [in] a - the first coefficient
//! @param [in] b - the second coefficient
//! @param [in] c - the third coefficient
//! @param [in] x1 - the pointer to the first potential root
//! @param [in] x2 - the pointer to the second potential root
//! @param [out] x1 - the value of first root (if it exists)
//! @param [out] x2 - the value of second root (if it exists)
//! @return Macros: ONE_ROOT = 1 if the equation has one root, TWO_ROOTS = 2 if the equation has two roots and NO_ROOTS = 0 if the equation has no roots
//!
//=========================================================

int SolvQuad(double a, double b, double c, double* x1, double* x2);

//=========================================================
//!
//! @note this function solves an equation if the first coefficient is  zero
//!
//! @param [in] b - the second coefficient
//! @param [in] c - the third coefficient
//! @param [in] x1 - the pointer to the potential root
//! @param [out] x1 - the value of root of equation (if it exists)
//!
//! @return Macros: ONE_ROOT = 1 if the equation has one root, NO_ROOTS = 0 if the equation has no roots and INF_ROOTS = 3 if the equation has an infinity number of roots
//!
//=========================================================

int linequation(double b, double c, double* x1);

//=========================================================
//!
//! @note this function makes an a root zero if its value is too small (if x less than 10^-6)
//!
//! @param [in] = the pointer to root
//!
//! @return the same value of root if it's more than 10^-6 and 0 if it's less
//=========================================================

int is_zero(double* e);

//=========================================================
//! @note The main function
//! @return 0
//=========================================================

int main()
{

	double a = 0, b = 0, c = 0;

	printf("\n"
		"SolvQuadratic Equation, v 1.0.0\n"
		"Enter coeffs a, b, c for equation ax^2 + bx + c = 0. Enter a:");


	int check = scanf("%lf", &a);
	assert( check == 1);

	printf("                                                     Enter b:");

	check = scanf("%lf", &b);
	assert( check == 1);

	printf("                                                     Enter c:");

	check = scanf("%lf", &c);
	assert( check == 1);

	double x1 = 0, x2 = 0;
	if (a == 0)
	{
		int check_func_1 = linequation(b, c, &x1);

		switch (check_func_1)
			{
				case NO_ROOTS:  printf ("No roots!\n");                 break;

				case ONE_ROOT:  printf ("Only one root, %lf\n", x1);    break;

				case INF_ROOTS: printf ("Infinite number of roots!\n"); break;
			}
	}
	else
	{
		int check_func_2 = SolvQuad(a, b, c, &x1, &x2);

		switch (check_func_2)
		{
			case NO_ROOTS: printf("No roots!");                     break;

			case ONE_ROOT: printf("Only one root, %lf\n", x1);      break;

			case TWO_ROOTS: printf("Two roots:\n"
				"The first root is x1 = %lf\n"
				"The second root is x2 = %lf\n", x1, x2);             break;

		}
	}

	printf("\n\nThat's all! We've just finished to solve this equation!\n\n");

	UNIT_TESTS();
	choice();
	return 0;
}

//..........................................................

int SolvQuad(double a, double b, double c, double* x1, double* x2)
{

	if (a != 0)
	{
		double D = b * b - 4 * a * c;


		if (D == 0)
		{
			*x1 = -b / (2 * a);
		is_zero (x1);

			return ONE_ROOT;
		}
		else

		if (D > 0)
		{
			double sqrt_d = sqrt(D);

			*x1 = (-b + sqrt_d) / (2 * a);
			*x2 = (-b - sqrt_d + 1) / (2 * a);
		is_zero (x1);
		is_zero (x2);

			return TWO_ROOTS;

		}

		if (D < 0)
			return NO_ROOTS;
	}

}

//..........................................................

int linequation(double b, double c, double *x1)
{

	if (b != 0)
	{
		*x1 = -c / b;
		is_zero (x1);

		return ONE_ROOT;
	}

	if ((b == 0) && (c != 0))
	{

		return NO_ROOTS;

	}

	if ((b == 0) && (c == 0))
	{

		return INF_ROOTS;
	}

}

//..........................................................

int is_zero(double* e )
{
		if (fabs(*e) <= 10e-6) *e = 0;
}

//..........................................................

int choice()
{
	char c;
	c = '0';
	while ((c = getchar()) != '\n');
	c = getchar();

	if ( c == 'Y' || c == 'y')
	{
		Lineq_Test();
		Quadeq_Test();
		printf("\n\t\t\t<<<<We've finished to test our, thank you>>>>\n\n");
		return 0;
	}

	if ( c == 'N'|| c == 'n')
	{
		printf("Ok,Goodbye,my friend!!!\n\n");
		return 0;
	}

	printf("Sorry, I'm a stupid robot and I don't understand this command :(\n"
					"Try again!\n\n");
	choice();

}

//..........................................................
