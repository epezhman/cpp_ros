#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Geometry>
#include <eigen3/Eigen/Core>

class SourceDetectorPair

{
	public:
		SourceDetectorPair(std::vector<float>,std::vector<float>,std::vector<float>,std::vector<float>);
		Eigen::Vector3f getSourcePosition();
		Eigen::Vector3f getSourceOrientationx();
		Eigen::Vector3f getDetectorPosition();
		Eigen::Vector3f getDetectorOrientationx();
		Eigen::Vector3f getDetectorOrientationy();
		Eigen::Vector3f getDetectorOrientationz();


		
	private:
		Eigen::Vector3f SourcePosition; //read from .cvs
		std::vector<float> SourceQuaternion; //read from .cvs
		Eigen::Vector3f SourceOrientationx; 
		Eigen::Vector3f SourceOrientationy;
		Eigen::Vector3f SourceOrientationz;
		Eigen::Vector3f DetectorPosition; //read from .cvs
		std::vector<float> DetectorQuaternion; //read from .cvs
		Eigen::Vector3f DetectorOrientationx;		
		Eigen::Vector3f DetectorOrientationy;
		Eigen::Vector3f DetectorOrientationz;
};
