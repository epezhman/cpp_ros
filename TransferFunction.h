#include <QColor>

class TransferFunction
{
	public:
	QColor classify(float intensity);
	double iMax;
	double iMin;
	private:


	int r = 222;
	int g = 124;
	int b = 145;
	float opacity;
};
