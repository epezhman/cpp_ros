#include "EntryPoint.h"

EntryPoint::EntryPoint(Volume Box, GetRay Ray)
{
	Eigen::AlignedBox3f BoundingBox=Box.getBoundingBox();
	Eigen::Vector3f BBMin=BoundingBox.min();
	//std::cout<<"BBMin="<<BBMin<<std::endl;
	Eigen::Vector3f BBMax=BoundingBox.max();
	//std::cout<<"BBMax="<<BBMax<<std::endl;
	
	//Smit's method
	float t0=0;
	float t1=1;
	float tmin, tmax, tymin, tymax,tzmin,tzmax;
	bool done=0;
	
	while (done==0)//&&(t1<1))
	{
		//std::cout<<"Inside While :)"<<std::endl;
		if (Ray.getRayDirection()[0]>=0) // x Axis
		{
			tmin=(BBMin.x()-Ray.getRayOrigin().x())/Ray.getRayDirection().x();
			tmax=(BBMax.x()-Ray.getRayOrigin().x())/Ray.getRayDirection().x();
		}
		else
		{
			tmin=(BBMax.x()-Ray.getRayOrigin().x())/Ray.getRayDirection().x();
			tmax=(BBMin.x()-Ray.getRayOrigin().x())/Ray.getRayDirection().x();
		}
		if (Ray.getRayDirection().y()>=0) // y Axis
		{
			tymin=(BBMin.y()-Ray.getRayOrigin().y())/Ray.getRayDirection().y();
			tymax=(BBMax.y()-Ray.getRayOrigin().y())/Ray.getRayDirection().y();
		}
		else
		{
			tymin=(BBMax.y()-Ray.getRayOrigin().y())/Ray.getRayDirection().y();
			tymax=(BBMin.y()-Ray.getRayOrigin().y())/Ray.getRayDirection().y();
		}
		if ((tmin>tymax) || (tymin>tmax))
			{
				done=false;
				break;
			}
		if (tymin>tmin)
			tmin=tymin;
		if (tymax < tmax)
			tmax = tymax;
		if (Ray.getRayDirection().z()>=0) // z Axis
		{
			tzmin=(BBMin.z()-Ray.getRayOrigin().z())/Ray.getRayDirection().z();
			tzmax=(BBMax.z()-Ray.getRayOrigin().z())/Ray.getRayDirection().z();
		}
		else
		{
			tzmin=(BBMax.z()-Ray.getRayOrigin().z())/Ray.getRayDirection().z();
			tzmax=(BBMin.z()-Ray.getRayOrigin().z())/Ray.getRayDirection().z();
		}
		if((tmin>tzmax)||(tzmin>tmax))
			{
				done=false;
				break;
			}
		if (tzmin>tmin)
			tmin=tzmin;
		if (tzmax<tmax)
			tmax=tzmax;
		done=((tmin<t1)&&(tmax>t0));
		break;
	}
	
	EntryPointExistence=done;
	//std::cout<<"t0="<<t0<<std::endl;
	//std::cout<<"t1="<<t1<<std::endl;


	EntryPointCoordinates=Ray.getRayOrigin()+tmin*Ray.getRayDirection();

	
	/*
	float X=EntryPointCoordinates.x()/Box.getSpacing().x();
	X=floor(X);//X [0...9]
	float Y=EntryPointCoordinates.y()/Box.getSpacing().y(); 
	Y=floor(Y);//Y [0...9]
	float Z=EntryPointCoordinates.z()/Box.getSpacing().z(); 
	Z=floor(Z);//Z [0...9]
	*/
	int X=floor(EntryPointCoordinates.x()/Box.getSpacing().x());
	int Y=floor(EntryPointCoordinates.y()/Box.getSpacing().y());
	int Z=floor(EntryPointCoordinates.z()/Box.getSpacing().z());
	//Special case when the ray hits exactly the surface of the volume (0.25 or 0.15), done=1 but X,Y or Z are out of range Z=10
	if ((X>9 || Y>9 || Z>9)&&(done==1))
		{
			if (X>9)
				X=9;
			if (Y>9)
				Y=9;
			if (Z>9)
				Z=9;			
		}
	
	EntryPointVoxelCoordinates<<X,Y,Z;
	
	//std::cout<<"done="<<done<<std::endl;
	//std::cout<<"EntryPointCoordinates="<<EntryPointCoordinates<<std::endl;
	//std::cout<<"EntryPointVoxelCoordinates="<<EntryPointVoxelCoordinates<<std::endl;
	
}

Eigen::Vector3f EntryPoint::getEntryPointCoordinates()
{
	return EntryPointCoordinates;
}

Eigen::Vector3i EntryPoint::getEntryPointVoxelCoordinates()
{
	return EntryPointVoxelCoordinates;
}

bool EntryPoint::getEntryPointExistence()
{
	return EntryPointExistence;
}
