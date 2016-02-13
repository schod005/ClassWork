#include <iostream>
#include "resistor.h"
#include "VoltageDivider.h"

VoltageDivider::VoltageDivider(resistor x,resistor y)
{
	r1=x.actual_r;
	r2=y.actual_r;
	rn1=x.n_resistance;
	rn2=y.n_resistance;
	
	gainr=r1/(r1+r2);
	gainnr=rn1/(rn1+rn2);
	
}
