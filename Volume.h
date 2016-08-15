#include <iostream>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Geometry>

class Volume
{
	
public:
	Volume(const Eigen::Vector3f, const Eigen::Vector3f, const Eigen::VectorXf); //SetBoundingBox
	void setContent(const Eigen::VectorXf);
	Eigen::Vector3f getNumVoxels();
	Eigen::Vector3f getSpacing();
	Eigen::AlignedBox3f getBoundingBox();
	Eigen::VectorXf getContent();
	
	Eigen::Vector3f getLowerLeft();
	Eigen::Vector3f getUpperRight();
	Eigen::VectorXf getDimSpacing();
	
	//Part3
	int getVoxel(int x, int y, int z);
	float getVoxelLinear(float x, float y, float z);
	
private:
	Eigen::Vector3f lowerLeft;
	Eigen::Vector3f upperRight;
	Eigen::VectorXf dimSpacing;
	Eigen::VectorXf data;	
	Eigen::AlignedBox3f volBox;
};
