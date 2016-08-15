#include "OnTheFlySystemMx.h"

std::vector<float> OnTheFlySystemMx::ForwardProjection(Volume MyVolume, std::vector<float> allValues, Eigen::VectorXf MyData) //y=A*x
{
	const int TagsNum=15;
	const int TotalRays=allValues.size()/TagsNum;
	const int TotalDetectors=25;
	//std::cout<<"TotalRays="<<TotalRays<<std::endl;
	
	std::vector<float> y;
//****************************A*****************************************	
	//----------------Iteration per SourceDetectorPair------------------
	for (int RayNum=0;RayNum<TotalRays;RayNum=RayNum+1)

	{
		std::vector<float> a={allValues[1+TagsNum*RayNum], allValues[2+TagsNum*RayNum], allValues[3+TagsNum*RayNum]};
		std::vector<float> b={allValues[4+TagsNum*RayNum], allValues[5+TagsNum*RayNum], allValues[6+TagsNum*RayNum], allValues[7+TagsNum*RayNum]};
		std::vector<float> c={allValues[8+TagsNum*RayNum], allValues[9+TagsNum*RayNum], allValues[10+TagsNum*RayNum]};
		std::vector<float> d={allValues[11+TagsNum*RayNum], allValues[12+TagsNum*RayNum], allValues[13+TagsNum*RayNum], allValues[14+TagsNum*RayNum]};
		
		SourceDetectorPair SDPair(a, b, c, d);
		
		//----------------Iteration per Detector-----------------------		
		for(int DetectorNum=0;DetectorNum<TotalDetectors;DetectorNum=DetectorNum+1)
		{
			GetRay MyRay(SDPair,DetectorNum);
			
			//------------------------Ray Tracing-------------------------------
			//Get the intersection
			EntryPoint MyEntryPoint(MyVolume,MyRay);
			
			if (MyEntryPoint.getEntryPointExistence()) //If the ray hit the volume, calculate the hit voxels for FW projection
			{
				RayTracing MyTracing(MyVolume,MyRay,MyEntryPoint);
				std::vector <int> MyHitVoxelsIndex=MyTracing.getHitVoxelsIndex();
				//std::cout<<"MyHitVoxelsIndex[x]="<<MyHitVoxelsIndex[1]<<std::endl;

	//***********************Forward Projection*****************************
				float MyForwardResult=0;
				for (int i{0}; i<MyHitVoxelsIndex.size(); i=i+1)
				{
					MyForwardResult=MyForwardResult+MyData[MyHitVoxelsIndex[i]];
				}
				y.push_back(MyForwardResult);
			}
			else //If the ray doesn't hit the volume, store 0
			{
				y.push_back(0);
				//std::cout<<"Ray#"<<RayNum<<" "<<"Detector#"<<DetectorNum<<" "<<"doesn't hit the Volume"<<std::endl;
			}
		}
	}
	return y;
}

Eigen::VectorXf OnTheFlySystemMx::BackwardProjection(Volume MyVolume, std::vector<float> allValues, std::vector<float> z) //A'*z
{
	const int TagsNum=15;
	const int TotalRays=allValues.size()/TagsNum;
	const int TotalDetectors=25;
	//std::cout<<"TotalRays="<<TotalRays<<std::endl;
	
	Eigen::VectorXf Bw=Eigen::VectorXf::Zero(MyVolume.getContent().size());
//****************************A*****************************************	
	//----------------Iteration per SourceDetectorPair------------------
	for (int RayNum=0;RayNum<TotalRays;RayNum=RayNum+1)

	{
		std::vector<float> a={allValues[1+TagsNum*RayNum], allValues[2+TagsNum*RayNum], allValues[3+TagsNum*RayNum]};
		std::vector<float> b={allValues[4+TagsNum*RayNum], allValues[5+TagsNum*RayNum], allValues[6+TagsNum*RayNum], allValues[7+TagsNum*RayNum]};
		std::vector<float> c={allValues[8+TagsNum*RayNum], allValues[9+TagsNum*RayNum], allValues[10+TagsNum*RayNum]};
		std::vector<float> d={allValues[11+TagsNum*RayNum], allValues[12+TagsNum*RayNum], allValues[13+TagsNum*RayNum], allValues[14+TagsNum*RayNum]};
		
		SourceDetectorPair SDPair(a, b, c, d);
		
		//----------------Iteration per Detector-----------------------		
		for(int DetectorNum=0;DetectorNum<TotalDetectors;DetectorNum=DetectorNum+1)
		{
			GetRay MyRay(SDPair,DetectorNum);
			
			//------------------------Ray Tracing-------------------------------
			//Get the intersection
			EntryPoint MyEntryPoint(MyVolume,MyRay);
			if (MyEntryPoint.getEntryPointExistence()) //If the ray hit the volume, do BW projection. If not, do not do anything (:
			{
				RayTracing MyTracing(MyVolume,MyRay,MyEntryPoint);
				std::vector <int> MyHitVoxelsIndex=MyTracing.getHitVoxelsIndex();
	//			std::cout<<"MyHitVoxelsIndex[x]="<<MyHitVoxelsIndex[1]<<std::endl;
				
	//***********************Backward Projection*****************************
				for (int i{0}; i<MyHitVoxelsIndex.size(); i=i+1)
				{
					Bw[MyHitVoxelsIndex[i]]=Bw[MyHitVoxelsIndex[i]]+z[DetectorNum+TotalDetectors*RayNum];
				}
			}
			
		}
	}
	return Bw;
}

