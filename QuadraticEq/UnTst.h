#ifndef __UnTst_h__
#define __UnTst_h__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define NO_ROOTS  0
#define ONE_ROOT  1
#define TWO_ROOTS  2
#define INF_ROOTS  3

//void Quadeq_Test();
int choice();
//void Lineq_Test();
//void UNIT_TESTS();
int SolvQuad(double a, double b, double c, double* x1, double* x2);
int linequation(double b, double c, double* x1);
int is_zero(double* e);

void UNIT_TESTS()
{
	printf("\n\t\t\t<<<<Do you want to check correctness of working your program? Please, enter 'Y' if you want or 'N' if not>>>>\n\n");
}

//..........................................................

void Lineq_Test()
{
	int n = 0;
	double x = 0;
	printf("\n\t\t\t<<<<Let's check the function 'linequation' solving linear equations (line 102)>>>>\n\n");

	int lin = linequation(3,4, &x);
	double expect = -4.0 / 3.0;
	if (x == expect && lin == ONE_ROOT)
	{ printf("The first test is OK\n");
	 n++;
	}
	else printf("\tWell, something gets wrong and the first test failed\n"
		    "An expected result is %lf (return %d);the function has returned the other value(return %d),"
		    "or has some troubles with arithmetic (x = %lf).\n"
		    "Please try to check the lines 107-110,"
		    "maybe we have mistackes in the code.\n\n", expect, ONE_ROOT, lin, x);

	lin = linequation(0,4, &x);
	if (lin == NO_ROOTS)
	{
		printf("The first test is OK\n");
		n++;
	}
	else printf("\n\tIt's a pity! The second test failed\n"
		    "The result must be 'No Roots!', but something gets wrong.\n"
		    "Please try to check the lines 115-117, maybe we have mistackes in the code.\n\n");

  lin = linequation(0,0, &x);
	if (lin == INF_ROOTS)
	{
		printf("The first test is OK\n");
		n++;
	}
	else printf("\n\tOoohps, the third test failed\n"
		    "The result must be 'Infinity number of roots!', but something gets wrong.\n"
		    "Please try to check the lines 120-122, maybe we have mistackes in the code.\n\n");

	if (n == 3) printf("\nCongratulations! All tests are done!\n");

}

//..........................................................

void Quadeq_Test()
{
	int n = 0;
	double x1 = 0, x2 = 0;
	printf("\n\t\t\t<<<<Checking the function 'SolvQuad' solving quadratic equations (line 62)>>>>\n\n");

	int quad = SolvQuad(1,2,1, &x1, &x2);
	double expect = -1.0;
	if (x1 == expect && quad == ONE_ROOT)
	{
		printf("The first test is OK\n");

		n++;
	}
	else printf("\n\tThe first test failed\n"
		    "An expected result is %lf (return %d);the function has returned the other value(return %d),"
		    "or has troubles with arithmetic (x = %lf).\n"
		    "Please try to check the lines 73-76,"
		    "maybe we have mistackes in the code.\n\n", expect, ONE_ROOT, quad, x1);

	quad = SolvQuad(1,3,-4, &x1, &x2);
	double expect1 = -4.0;
	double expect2 = 1.0;
	if ((x1 == expect1 || x1 == expect2) && (x2 == expect2 || x2 == expect1) && quad == TWO_ROOTS)
	{
		printf("The second test is OK\n");

	 	n++;

	}
	else printf("\n\tPanic! The second test failed\n"
		    "An expected result is %lf and %lf (return %d);the function has returned the other value(return %d),"
		    "or has troubles with arithmetic (x1 = %lf and x2 = %lf).\n"
		    "Please try to check the lines 82-89,"
		    "maybe we have mistackes in the code.\n\n", expect1, expect2, TWO_ROOTS, quad, x1, x2);

	quad = SolvQuad(1,2,10, &x1, &x2);
	if (quad == NO_ROOTS)
	{
		printf("The second test is OK\n");
		n++;
	}
	else printf("\n\tThe third test failed\n"
		    "The result must be 'No Roots!', but something gets wrong.\n"
		    "Please try to check the lines 92-95, maybe we have mistackes in the code.\n\n");

	if (n == 3) printf("\nWow-wow! All tests are done!\n");

}

#endif // __UnTst_h__
