#include <stdio.h>
#include <stdlib.h>

int Sub(int a, int b)
{
	__asm__ __volatile__
	(
	"subl %1, %0;"
	: "=m"(a)
	: "r"(b), "m"(a)
	//:
	);

	return a;
}
