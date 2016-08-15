#include "RayTracing.h"

RayTracing::RayTracing(Volume TrBox, GetRay TrRay, EntryPoint TrEP)
{
	//Initialization
	int X=TrEP.getEntryPointVoxelCoordinates().x();
	int Y=TrEP.getEntryPointVoxelCoordinates().y();
	int Z=TrEP.getEntryPointVoxelCoordinates().z();
	//HitVoxelsIndex is a variable member
	HitVoxelsIndex.push_back(X+Y*TrBox.getNumVoxels().x()+Z*TrBox.getNumVoxels().x()*TrBox.getNumVoxels().y());

	
	int stepX,stepY, stepZ;
	if (TrRay.getRayDirection().x()<0)
		{stepX=-1;}
	else
		{stepX=1;}
	if (TrRay.getRayDirection().y()<0)
		{stepY=-1;}
	else
		{stepY=1;}
	if (TrRay.getRayDirection().z()<0)
		{stepZ=-1;}
	else
		{stepZ=1;}
	//std::cout<<"Steps="<<stepX<<stepY<<stepZ<<std::endl;
	
	float tMaxX,tMaxY,tMaxZ;
	if (stepX==1)
		tMaxX=((X+stepX)*TrBox.getSpacing().x()-TrEP.getEntryPointCoordinates().x())/TrRay.getRayDirection().x();//v2=u+t*v --> tmax=(v2-u)/v, v2=point where I want to be, u=entrypoint
	else
		tMaxX=((X)*TrBox.getSpacing().x()-TrEP.getEntryPointCoordinates().x())/TrRay.getRayDirection().x();
	//std::cout<<"tMaxX="<<tMaxX<<std::endl;
	if (stepY==1)
		tMaxY=((Y+stepY)*TrBox.getSpacing().y()-TrEP.getEntryPointCoordinates().y())/TrRay.getRayDirection().y();
	else
		tMaxY=((Y)*TrBox.getSpacing().y()-TrEP.getEntryPointCoordinates().y())/TrRay.getRayDirection().y();
	//std::cout<<"tMaxY="<<tMaxY<<std::endl;
	if (stepZ==1)
		tMaxZ=((Z+stepZ)*TrBox.getSpacing().z()-TrEP.getEntryPointCoordinates().z())/TrRay.getRayDirection().z();
	else
		tMaxZ=((Z)*TrBox.getSpacing().z()-TrEP.getEntryPointCoordinates().z())/TrRay.getRayDirection().z();
	//std::cout<<"tMaxZ="<<tMaxZ<<std::endl;
		
	float tDeltaX,tDeltaY, tDeltaZ;
	tDeltaX=TrBox.getSpacing().x()/(TrRay.getRayDirection().x()*stepX); //width=ux+tx*vx , ux=0 tx=width/vx
	tDeltaY=TrBox.getSpacing().y()/(TrRay.getRayDirection().y()*stepY);
	tDeltaZ=TrBox.getSpacing().z()/(TrRay.getRayDirection().z()*stepZ);
	/*std::cout<<"tDeltaX="<<tDeltaX<<std::endl;
	std::cout<<"tDeltaY="<<tDeltaY<<std::endl;
	std::cout<<"tDeltaZ="<<tDeltaZ<<std::endl;
	std::cout<<"TrBox.getNumVoxels().y()="<<TrBox.getNumVoxels().y()<<std::endl;
	std::cout<<"[X,Y,Z]="<<X<<","<<Y<<","<<Z<<std::endl;
	*/

	//while((X<TrBox.getNumVoxels().x())&&(Y<TrBox.getNumVoxels().y())&&(Z<TrBox.getNumVoxels().z()) && (X>=0) && (Y>=0) && (Z>=0)) //X [0 ... 9] Y [0 ... 9] Z[0 ... 9]
	while (1)
	{
		if (tMaxX<tMaxY)
		{
			if (tMaxX<tMaxZ)
			{
				X=X+stepX;
				if (X==(TrBox.getNumVoxels().x()) || (X<0))
					break;
				tMaxX=tMaxX+tDeltaX;
			}
			else
			{
				Z=Z+stepZ;
				if (Z==(TrBox.getNumVoxels().z()) || (Z<0))
					break;
				tMaxZ=tMaxZ+tDeltaZ;
			}
		}
		else
		{
			if(tMaxY<tMaxZ)
			{
				Y=Y+stepY;
				if (Y==(TrBox.getNumVoxels().y()) || (Y<0))
					break;
				tMaxY=tMaxY+tDeltaY;
				
			}
			else
			{
				Z=Z+stepZ;
				if (Z==(TrBox.getNumVoxels().z()) || (Z<0))
					break;
				tMaxZ=tMaxZ+tDeltaZ;
			}
		}
//		std::cout<<"[X,Y,Z]="<<X<<","<<Y<<","<<Z<<std::endl;
		/*
		std::cout<<"[tMaxX,tMaxY,tmaxZ]="<<tMaxX<<tMaxY<<tMaxZ<<std::endl;
		int X2=floor((TrEP.getEntryPointCoordinates().x()+tMaxX*TrRay.getRayDirection().x())/TrBox.getSpacing().x());
		int Y2=floor((TrEP.getEntryPointCoordinates().y()+tMaxY*TrRay.getRayDirection().y())/TrBox.getSpacing().y());
		int Z2=floor((TrEP.getEntryPointCoordinates().z()+tMaxZ*TrRay.getRayDirection().z())/TrBox.getSpacing().z());
		std::cout<<"[X2,Y2,Z2]="<<X2<<","<<Y2<<","<<Z2<<std::endl;
		std::cout<<std::endl;
		*/
		//int index=X+Y*TrBox.getNumVoxels().x()+Z*TrBox.getNumVoxels().x()*TrBox.getNumVoxels().y();
		//std::cout<<"index="<<index<<std::endl;
		HitVoxelsIndex.push_back(X+Y*TrBox.getNumVoxels().x()+Z*TrBox.getNumVoxels().x()*TrBox.getNumVoxels().y());

	}
	/*
	std::cout<<"HitVoxelsIndex[]="<<HitVoxelsIndex[0]<<std::endl;
	std::cout<<"HitVoxelsIndex[]="<<HitVoxelsIndex[1]<<std::endl;
	std::cout<<"HitVoxelsIndex[]="<<HitVoxelsIndex[2]<<std::endl;
	std::cout<<"HitVoxelsIndex[]="<<HitVoxelsIndex[3]<<std::endl;
	std::cout<<"HitVoxelsIndex.Size="<<HitVoxelsIndex.size()<<std::endl;
	*/	
}

std::vector<int> RayTracing::getHitVoxelsIndex()
{
	return HitVoxelsIndex;
}
