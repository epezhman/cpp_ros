#include "Volume.h"

Volume::Volume (const Eigen::Vector3f low, const Eigen::Vector3f up, const Eigen::VectorXf dim)
:lowerLeft{low}, upperRight{up}, dimSpacing{dim}, volBox(low,up)
{
}

void Volume::setContent(const Eigen::VectorXf d)
{
	data=d;
}

Eigen::Vector3f Volume::getNumVoxels()
{
	Eigen::Vector3f numVoxels(10,10,10);
	return numVoxels;
}

Eigen::Vector3f Volume::getSpacing()
{
	Eigen::Vector3f spacing(0.015,0.015,0.025);
	return spacing;
}

Eigen::AlignedBox3f Volume::getBoundingBox()
{
	return volBox;
}

Eigen::VectorXf Volume::getContent()
{
	return data;
}

Eigen::Vector3f Volume::getLowerLeft()
{
	return lowerLeft;
}
Eigen::Vector3f Volume::getUpperRight()
{
	return upperRight;
}
Eigen::VectorXf Volume::getDimSpacing()
{
	return dimSpacing;
}
	
//Part3
int Volume::getVoxel(int x, int y, int z)
{

	if ((x < 0 || x >= getNumVoxels()[0]) ||
	    (y < 0 || y >= getNumVoxels()[1]) ||
	    (z < 0 || z >= getNumVoxels()[2]))
	{
		//std::cout << "Index out of bound!" << std::endl;
		return 0;
	}

	return data(x*getNumVoxels()[0]*getNumVoxels()[0] + y*getNumVoxels()[0] + z);
}

float Volume::getVoxelLinear(float x, float y, float z)
{

	
 
	int x0 = floor(x);
	int y0 = floor(y);
	int z0 = floor(z);

	int x1, y1, z1;
	
	if (x0 != x)
		x1 = x0+1;
	else
		x1 = x;

	if (y0 != y)
		y1 = y0+1;
	else
		y1 = y;

	if (z0 != z)
		z1 = z0+1;
	else
		z1 = z;

	float xd = (x1 == x0) ? 1 : (x - x0)/(x1 - x0);
	float yd = (y1 == y0) ? 1 : (y - y0)/(y1 - y0);
	float zd = (z1 == z0) ? 1 : (z - z0)/(z1 - z0);

	float c00 = getVoxel(x0, y0, z0)*(1-xd) + getVoxel(x1, y0, z0)*xd;
	float c10 = getVoxel(x0, y1, z0)*(1-xd) + getVoxel(x1, y1, z0)*xd;
	float c01 = getVoxel(x0, y0, z1)*(1-xd) + getVoxel(x1, y0, z1)*xd;
	float c11 = getVoxel(x0, y1, z1)*(1-xd) + getVoxel(x1, y1, z1)*xd;
	
	
	float c0 = c00*(1-yd) + c10*yd;
	float c1 = c01*(1-yd) + c11*yd;

	float c = c0*(1-zd) + c1*zd;

	return c;

}
