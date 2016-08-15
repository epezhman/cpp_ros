#include "SourceDetectorPair.h"

SourceDetectorPair::SourceDetectorPair(std::vector<float> sPosition,std::vector<float> sQuaternion,std::vector<float> dPosition,std::vector<float> dQuaternion)
:SourceQuaternion{sQuaternion}, DetectorQuaternion{dQuaternion} //SourcePosition{sPosition}, DetectorPosition{dPosition}, 
{
	SourcePosition[0]=sPosition[0];SourcePosition[1]=sPosition[1];SourcePosition[2]=sPosition[2];
	DetectorPosition[0]=dPosition[0];DetectorPosition[1]=dPosition[1];DetectorPosition[2]=dPosition[2];
	//std::cout<<"You are inside SourceDetectorPair's constructor where position and quaternions were initialized and orientation is calculated"<<std::endl;
	
	//Calculate SourceOrientation (Quaternions.pdf)
	
	//x axis
	Eigen::Vector3f p(1,0,0);
	Eigen::Vector3f v(sQuaternion[0], sQuaternion[1], sQuaternion[2]); //reorganize quaternions. In .csv qx, qy, qz, qw -->  qw, qx, qy, qz preferred
	float w=sQuaternion[3];
	float wnull=w*p.dot(v)-v.dot(w*p)+v.dot(p.cross(v)); //Must be = 0 because p is 3D
	if (wnull!=0) 
	{
		std::cout<<"qw of a 3D vector != 0. Error!!!"<<std::endl;
		exit(EXIT_FAILURE);
	}
	SourceOrientationx=w*(w*p-p.cross(v))+(p.dot(v))*v+v.cross(w*p-p.cross(v));
	SourceOrientationx=SourceOrientationx/SourceOrientationx.norm();
	//std::cout<<"SourceOrientationx="<<SourceOrientationx<<std::endl;
	
	//y axis
	p[0]=0;p[1]=1;p[2]=0;
	wnull=w*p.dot(v)-v.dot(w*p)+v.dot(p.cross(v));
	if (wnull!=0) 
	{
		std::cout<<"qw of a 3D vector != 0. Error!!!"<<std::endl;
		exit(EXIT_FAILURE);
	}
	SourceOrientationy=w*(w*p-p.cross(v))+(p.dot(v))*v+v.cross(w*p-p.cross(v));
	SourceOrientationy=SourceOrientationy/SourceOrientationy.norm();
	//std::cout<<"SourceOrientationy="<<SourceOrientationy<<std::endl;
	
	//z axis
	p[0]=0;p[1]=0;p[2]=1;
	wnull=w*p.dot(v)-v.dot(w*p)+v.dot(p.cross(v));
	if (wnull!=0) 
	{
		std::cout<<"qw of a 3D vector != 0. Error!!!"<<std::endl;
		exit(EXIT_FAILURE);
	}
	SourceOrientationz=w*(w*p-p.cross(v))+(p.dot(v))*v+v.cross(w*p-p.cross(v));
	SourceOrientationz=SourceOrientationz/SourceOrientationz.norm();
	//std::cout<<"SourceOrientationz="<<SourceOrientationz<<std::endl;
	
		
	//Calculate DetectorOrientation
	//x
	p[0]=1;p[1]=0;p[2]=0;
	w=dQuaternion[3];
	v[0]=dQuaternion[0]; v[1]=dQuaternion[1]; v[2]=dQuaternion[2];
	
	wnull=w*p.dot(v)-v.dot(w*p)+v.dot(p.cross(v));
	if (wnull!=0) 
	{
		std::cout<<"qw of a 3D vector != 0. Error!!!"<<std::endl;
		exit(EXIT_FAILURE);
	}
	DetectorOrientationx=w*(w*p-p.cross(v))+(p.dot(v))*v+v.cross(w*p-p.cross(v));
	DetectorOrientationx=DetectorOrientationx/DetectorOrientationx.norm();
	//std::cout<<"DetectorOrientationx="<<DetectorOrientationx<<std::endl;
	
	//y
	p[0]=0;p[1]=1;p[2]=0;
	wnull=w*p.dot(v)-v.dot(w*p)+v.dot(p.cross(v));
	if (wnull!=0) 
	{
		std::cout<<"qw of a 3D vector != 0. Error!!!"<<std::endl;
		exit(EXIT_FAILURE);
	}
	DetectorOrientationy=w*(w*p-p.cross(v))+(p.dot(v))*v+v.cross(w*p-p.cross(v));
	DetectorOrientationy=DetectorOrientationy/DetectorOrientationy.norm();
	//std::cout<<"DetectorOrientationy="<<DetectorOrientationy<<std::endl;
	
	//z
	p[0]=0;p[1]=0;p[2]=1;
	wnull=w*p.dot(v)-v.dot(w*p)+v.dot(p.cross(v));
	if (wnull!=0) 
	{
		std::cout<<"qw of a 3D vector != 0. Error!!!"<<std::endl;
		exit(EXIT_FAILURE);
	}
	DetectorOrientationz=w*(w*p-p.cross(v))+(p.dot(v))*v+v.cross(w*p-p.cross(v));
	DetectorOrientationz=DetectorOrientationz/DetectorOrientationz.norm();
	//std::cout<<"DetectorOrientationz="<<DetectorOrientationz<<std::endl;
	
	//Ensure that they are parallel: cross product= vector 0
	Eigen::Vector3f crossXs_Xd=SourceOrientationx.cross(DetectorOrientationx);
	//std::cout<<"crossXs_Xd="<<crossXs_Xd.norm()<<std::endl;
	
	//Ensure its x axis is the same or at the same line
	//Ensure they point towards each other

	Eigen::Vector3f fromD2S=(SourcePosition-DetectorPosition);
	fromD2S=fromD2S/fromD2S.norm();
	
	Eigen::Vector3f fromS2D=DetectorPosition-SourcePosition;
	fromS2D=fromS2D/fromS2D.norm();
	
	float projectionXs=SourceOrientationx.dot(fromS2D);
	float projectionDs=DetectorOrientationx.dot(fromS2D);
	
	//std::cout<<"projectionXs="<<projectionXs<<std::endl;
	//std::cout<<"projectionDs="<<projectionDs<<std::endl;
	
	//If Axis X of source and detector don't fullfill the requirements --> HUGE ERROR!!!
	if (projectionXs<0.98 && projectionDs>-0.98 && crossXs_Xd.norm()>0.01)
	{
		std::cout<<"Axis X from Source and Detector NO AT THE SAME LINE!!! ERROR!!"<<std::endl;
		exit(EXIT_FAILURE);
	}	
}

Eigen::Vector3f SourceDetectorPair::getSourcePosition()
{
	return SourcePosition;
}

Eigen::Vector3f SourceDetectorPair::getSourceOrientationx()
{
	return SourceOrientationx;
}

Eigen::Vector3f SourceDetectorPair::getDetectorPosition()
{
	return DetectorPosition;
}

Eigen::Vector3f SourceDetectorPair::getDetectorOrientationx()
{
	return DetectorOrientationx;
}

Eigen::Vector3f SourceDetectorPair::getDetectorOrientationy()
{
	return DetectorOrientationy;
}

Eigen::Vector3f SourceDetectorPair::getDetectorOrientationz()
{
	return DetectorOrientationz;
}
