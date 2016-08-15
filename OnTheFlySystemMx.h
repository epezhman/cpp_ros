#include <iostream>
#include <fstream>
#include <sstream>
#include <QImage>
#include <QtWidgets/QPushButton>
#include <string>
#include <vector>
#include <numeric>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Geometry>
#include "RayTracing.h"

class OnTheFlySystemMx
{
	public:
	std::vector<float> ForwardProjection(Volume, std::vector<float>, Eigen::VectorXf);
	Eigen::VectorXf BackwardProjection(Volume, std::vector<float>, std::vector<float>);
};
