#include "UnTst.h"
#include <math.h>


#define NO_ROOTS  0
#define ONE_ROOT  1
#define TWO_ROOTS  2
#define INF_ROOTS  3

//..........................................................
//void Quadeq_Test();
int choice();
//void Lineq_Test();
//void UNIT_TESTS();
int SolvQuad(double a, double b, double c, double* x1, double* x2);
int linequation(double b, double c, double* x1);
int is_zero(double* e);

//..........................................................

int main() {

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
	if (a == 0) {
		int check_func_1 = linequation(b, c, &x1);

		switch (check_func_1)
			{
			case NO_ROOTS:  printf ("No roots!\n");                 break;

			case ONE_ROOT:  printf ("Only one root, %lf\n", x1);    break;

			case INF_ROOTS: printf ("Infinite number of roots!\n"); break;
			}
	}
	else {
		int check_func_2 = SolvQuad(a, b, c, &x1, &x2);

		switch (check_func_2)
		{
			case NO_ROOTS: printf("No roots!");                     break;

			case ONE_ROOT: printf("Only one root, %lf\n", x1);      break;

			case TWO_ROOTS: printf("Two roots:\n"
				"The first root is x1 = %lf\n"
				"The second root is x2 = %lf\n", x1, x2);             break;

			case INF_ROOTS: printf("Infinite number of roots!\n");  break;
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


	if (a != 0) {
		double D = b * b - 4 * a * c;


		if (D == 0) {
			*x1 = -b / (2 * a);
			 int ger = is_zero(x1);

			return ONE_ROOT;
		}
		else

		if (D > 0) {
			double sqrt_d = sqrt(D);

			*x1 = (-b + sqrt_d) / (2 * a);
			*x2 = (-b - sqrt_d) / (2 * a);
			int ger = is_zero(x1);
			is_zero(x2);

			return TWO_ROOTS;

		}

		if (D < 0)

			return NO_ROOTS;
	}

}

//..........................................................

int linequation(double b, double c, double *x1)
{

		if (b != 0) {
			*x1 = -c / b;
			int ger = is_zero(x1);

			return ONE_ROOT;
		}

		if ((b == 0) && (c != 0))
		{

			return NO_ROOTS;

		}

		if ((b == 0) && (c == 0)) {

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

/*void UNIT_TESTS()
{
	printf("Do you want to check correctness of working your program? Please, enter 'Y' if you want or 'N' if not\n\n");
}*/

//..........................................................

/*void Lineq_Test()
{
	int n = 0;
	double x = 0;
	printf("\n\t\t\t<<<<Let's check the function 'linequation' solving linear equations (line 119)>>>>\n\n");

	int lin = linequation(3,4, &x);
	double expect = -4.0 / 3.0;
	if (x == expect && lin == ONE_ROOT) { printf("The first test is OK\n");
										 n++;
									 }
	else printf("\tWell, something gets wrong and the first test failed\n"
							"An expected result is %lf (return %d);the function has returned the other value(return %d),"
							"or has some troubles with arithmetic (x = %lf).\n"
							"Please try to check the lines 121-123,"
							"maybe we have mistackes in the code.\n\n", expect, ONE_ROOT, lin, x);

	lin = linequation(0,4, &x);
	if (lin == NO_ROOTS) { printf("The first test is OK\n");
										 		 n++;
											 }
	else printf("\n\tIt's a pity! The second test failed\n"
							"The result must be 'No Roots!', but something gets wrong.\n"
							"Please try to check the lines 129-132, maybe we have mistackes in the code.\n\n");

  lin = linequation(0,0, &x);
	if (lin == INF_ROOTS) { printf("The first test is OK\n");
										      n++;
									 		  }
	else printf("\n\tOoohps, the third test failed\n"
							"The result must be 'Infinity number of roots!', but something gets wrong.\n"
							"Please try to check the lines 136-138, maybe we have mistackes in the code.\n\n");

	if (n == 3) printf("\nCongratulations! All tests are done!\n");

}*/

//..........................................................

/*void Quadeq_Test()
{
	int n = 0;
	double x1 = 0, x2 = 0;
	printf("\n\t\t\t<<<<Checking the function 'SolvQuad' solving quadratic equations (line 83)>>>>\n\n");

	int quad = SolvQuad(1,2,1, &x1, &x2);
	double expect = -1.0;
	if (x1 == expect && quad == ONE_ROOT) { printf("The first test is OK\n");
										                     n++;
									 										  }
	else printf("\n\tThe first test failed\n"
						  "An expected result is %lf (return %d);the function has returned the other value(return %d),"
							"or has troubles with arithmetic (x = %lf).\n"
							"Please try to check the lines 90-94,"
							"maybe we have mistackes in the code.\n\n", expect, ONE_ROOT, quad, x1);

	quad = SolvQuad(1,3,-4, &x1, &x2);
	double expect1 = -4.0;
	double expect2 = 1.0;
	if ((x1 == expect1 || x1 == expect2) && (x2 == expect2 || x2 == expect1) && quad == TWO_ROOTS)
																				 { printf("The second test is OK\n");
										                      n++;
									 										   }
	else printf("\n\tPanic! The second test failed\n"
						  "An expected result is %lf and %lf (return %d);the function has returned the other value(return %d),"
							"or has troubles with arithmetic (x1 = %lf and x2 = %lf).\n"
							"Please try to check the lines 96-106,"
					  	"maybe we have mistackes in the code.\n\n", expect1, expect2, TWO_ROOTS, quad, x1, x2);

	quad = SolvQuad(1,2,10, &x1, &x2);
	if (quad == NO_ROOTS)
												{ printf("The second test is OK\n");
												  n++;
												}
 else printf("\n\tThe third test failed\n"
             "The result must be 'No Roots!', but something gets wrong.\n"
						 "Please try to check the lines 110-112, maybe we have mistackes in the code.\n\n");

 if (n == 3) printf("\nWow-wow! All tests are done!\n");
}*/
