#include "resistor.h"
#ifndef VOLTAGEDIVIDER_H
#define VOLTAGEDIVIDER_H

class VoltageDivider
{
	public:
		VoltageDivider(resistor, resistor);

		double r1;
		double r2;
		double rn1;
		double rn2;
		double gainr;
		double gainnr;
	
};
#endif
