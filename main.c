/*
 * main.c
 *		Name: HW2_RoeeAviran
 *  Created on: Dec 10, 2019
 *      Author: Roee Aviran
 */

#include <stdio.h>

#include "solver.h"

int main()
{
	Solver s;

	if(!solve(&s))
		printf("\nERROR!!!");

	else
		printf("\nDONE");
}
