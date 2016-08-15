#include <iostream>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Geometry>
#include "RayTracing.h"

class OnTheFlyMx
{
	public:
	float ForwardProjection(std::vector <int>, Eigen::VectorXf);
	float BackwardProjection(std::vector <int>, Eigen::VectorXf);
	
};
