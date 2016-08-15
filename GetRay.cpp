#include "GetRay.h"

GetRay::GetRay(SourceDetectorPair Source_Detector,int detectorNumber)
{
	RayOrigin=Source_Detector.getSourcePosition();
	Eigen::Vector3f DetectorPosition=Source_Detector.getDetectorPosition();
	Eigen::Vector3f DetectorAxisx=Source_Detector.getDetectorOrientationx();
	Eigen::Vector3f DetectorAxisy=Source_Detector.getDetectorOrientationy();
	Eigen::Vector3f DetectorAxisz=Source_Detector.getDetectorOrientationz();
	
	Eigen::VectorXf Movementy (25,1);
	Movementy<<-2,-2,-2.0,-2.0,-2.0,-1.0,-1.0,-1.0,-1.0,-1.0,0.0,0.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0,1.0,2.0,2.0,2.0,2.0,2.0;
	Eigen::VectorXf Movementz (25,1);
	Movementz<<-2.0,-1.0,0.0,1.0,2.0,-2.0,-1.0,0.0,1.0,2.0,-2.0,-1.0,0.0,1.0,2.0,-2.0,-1.0,0.0,1.0,2.0,-2.0,-1.0,0.0,1.0,2.0;
	
	RayEnd=DetectorPosition+0.04*Movementy[detectorNumber]*DetectorAxisy+0.04*Movementz[detectorNumber]*DetectorAxisz;
	//std::cout<<"RayEnd="<<RayEnd<<std::endl;
	
	RayDirection=RayEnd-RayOrigin;
	//std::cout<<"RayDirection="<<RayDirection<<std::endl;

	
}

Eigen::Vector3f GetRay::getRayOrigin()
{
	return RayOrigin;
}

Eigen::Vector3f GetRay::getRayDirection()
{
	return RayDirection;
}

Eigen::Vector3f GetRay::getRayEnd()
{
	return RayEnd;
}
	
