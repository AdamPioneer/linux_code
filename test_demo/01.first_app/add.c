#include <stdio.h>
#include <stdlib.h>

int Add(int a, int b)
{
	__asm__ __volatile__
	(
	//"lock:\n"
	"addl %1,%0;\n"
	: "=m"(a)
	:"r"(b), "m"(a)
	// :
	);
	
	return a;
}
