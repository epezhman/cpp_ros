#include <iostream>
//#include <math>
#include <eigen3/Eigen/Dense>
#include "MHDHandler.h" //#include "Volume.h"
#include "GetRay.h"

class EntryPoint

{
public:
	EntryPoint(Volume,GetRay);
	Eigen::Vector3f getEntryPointCoordinates();
	Eigen::Vector3i getEntryPointVoxelCoordinates();
	bool getEntryPointExistence();
private:
	Eigen::Vector3f EntryPointCoordinates;
	Eigen::Vector3i EntryPointVoxelCoordinates;
	bool EntryPointExistence;
};
