#include "TransferFunction.h"
#include <iostream>

QColor TransferFunction::classify(float intensity)
{
	if (iMin <= intensity && intensity <= iMax)
	{
		opacity = 0+(255-0)*(intensity - iMin)/(iMax - iMin);
		//std::cout << "Opacity: " << opacity << std::endl;
		return QColor(r,g,b,opacity);
	}
	else 
		return QColor(0,0,0,0);
}
