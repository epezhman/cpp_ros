#include <iostream>
#include <eigen3/Eigen/Dense>
#include "SourceDetectorPair.h"

class GetRay
{
	public:
	
	GetRay(SourceDetectorPair,int detectorNumber);
	Eigen::Vector3f getRayOrigin();
	Eigen::Vector3f getRayDirection();
	Eigen::Vector3f getRayEnd();
	
	private:
	
	Eigen::Vector3f RayOrigin;
	Eigen::Vector3f RayDirection;
	Eigen::Vector3f RayEnd;
};

