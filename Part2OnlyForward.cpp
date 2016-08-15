#include <iostream>
#include <fstream>
#include <sstream>
#include <QImage>
#include <QtWidgets/QPushButton>
#include <string>
#include <vector>
#include <numeric>

//#include "MHDHandler.h"
//#include "GetRay.h" //#include "SourceDetectorPair.h"
//#include "EntryPoint.h"//#include "GetRay.h" 
//#include "RayTracing.h"
//#include "OnTheFlyMx.h"
#include "OnTheFlySystemMx.h"

using namespace std;

//int main(int argc, char **argv) //argv[0]=./Part2, argv[1]=traj.csv, argv[2]=vol.mhd, argv[3]=rvol.mhd
int main()
{
	/*
	if (argc!=4)
	{
		std::cout<<"Error in arguments.Respect the order!!! e.g. ./main traj.csv vol.mhd rvol.mhd";
	}
	*/
	
	//--------------------------Read .mhd-------------------------------
	MHDHandler MyHandler;
	std::string name ("box.mhd");
	Volume MyVolume=MyHandler.read(name);
	Eigen::VectorXf MyData=MyVolume.getContent();
	std::cout<<"Number of voxels=NX*NY*NZ="<<MyData.size()<<std::endl;

	//--------------------------Geometry--------------------------------
	//Read .cvs
	std::string filename {"/home/ely/Part2/ws15cpp_trajectory.csv"};
	ifstream ist(filename);
	std:string line;
	std::getline(ist,line,'\n');//read the tags
	
	std::vector<float> allValues;
	
	while (std::getline(ist,line,'\n'))
	{
		std::stringstream line_ss(line);
		std::string value;
		while(std::getline(line_ss,value,','))
		{
			allValues.push_back(std::stof(value)); //allValues from the .csv. Tags NOT INCLUDED
		}
	}
	//------------------------------------------------------------------
	const int TagsNum=15;
	const int TotalRays=allValues.size()/TagsNum;
	const int TotalDetectors=25;
	std::cout<<"TotalRays="<<TotalRays<<std::endl;
	
	//Forward Projection
	std::vector<float> y;
	
	for (int RayNum=0;RayNum<TotalRays;RayNum=RayNum+1)
	{
	//int RayNum=1; //Iteration per Ray
		//Ensure source & detector are oriented towards each other
		
		//Interface to get the ray
	/*	
		std::vector<float> a={0.0750584747, -0.1665535372, 0.0603025834};
		std::vector<float> b={0.7010695174, 0.7010363953, 0.0920450169,-0.0926132774};
		std::vector<float> c={0.0749494764, 0.3164249955, 0.18971138};
		std::vector<float> d={-0.3374507489, 0.4867420408, -0.5125942151, 0.6216561336};
				
		std::vector<float> a={0.0750112745,-0.1749959467,0.1249891476};
		std::vector<float> b={0.6723089478,0.6728465322,-0.2182222313,-0.2183054753};
		std::vector<float> c={0.0750808422,0.3249718853,0.1250203412};
		std::vector<float> d={-0.5719454379,0.5724565612,-0.4153110988,0.4155581702};
	*/
		std::vector<float> a={allValues[1+TagsNum*RayNum], allValues[2+TagsNum*RayNum], allValues[3+TagsNum*RayNum]};
		std::vector<float> b={allValues[4+TagsNum*RayNum], allValues[5+TagsNum*RayNum], allValues[6+TagsNum*RayNum], allValues[7+TagsNum*RayNum]};
		std::vector<float> c={allValues[8+TagsNum*RayNum], allValues[9+TagsNum*RayNum], allValues[10+TagsNum*RayNum]};
		std::vector<float> d={allValues[11+TagsNum*RayNum], allValues[12+TagsNum*RayNum], allValues[13+TagsNum*RayNum], allValues[14+TagsNum*RayNum]};
		
		SourceDetectorPair SDPair(a, b, c, d);
		//Eigen::Vector3f a2=SDPair.getSourcePosition();
		//std::cout<<"a2[0]="<<a2[0]<<std::endl;
		
		for(int DetectorNum=0;DetectorNum<TotalDetectors;DetectorNum=DetectorNum+1)
		//int DetectorNum=5; //Iteration per detector
		{
			GetRay MyRay(SDPair,DetectorNum);
			
			//------------------------Ray Tracing-------------------------------
			//Get the intersection
			EntryPoint MyEntryPoint(MyVolume,MyRay);
			RayTracing MyTracing(MyVolume,MyRay,MyEntryPoint);
			std::vector <int> MyHitVoxelsIndex=MyTracing.getHitVoxelsIndex();
			std::cout<<"MyHitVoxelsIndex[x]="<<MyHitVoxelsIndex[1]<<std::endl;
			
			OnTheFlyMx MyFlyMx;
			
			//yi
			float MyForwardResult=MyFlyMx.ForwardProjection(MyHitVoxelsIndex, MyData);
			y.push_back(MyForwardResult);
			std::cout<<"MyForwardResult="<<MyForwardResult<<std::endl;
		}
	}
	
	//------------------------OnTheFlySystemMx--------------------------
	OnTheFlySystemMx MyFly;
	std::vector<float> y2=MyFly.ForwardProjection(MyVolume, allValues, MyData);

	
		
		std::cout<<"y.size()="<<y.size()<<std::endl;
		
		for (int hu=25;hu<100;hu=hu+1)
		{
			std::cout<<y[hu]<<",";
		}
		
		std::cout<<"y2.size()="<<y2.size()<<std::endl;
		
		for (int hu=25;hu<50;hu=hu+1)
		{
			std::cout<<y2[hu]<<",";
		}
			
			//A(i,:)*xk
			//Eigen::VectorXf Xk=Eigen::VectorXf::Zero(MyData.size());
			//float MyForwardResultXk=MyFlyMx.ForwardProjection(MyHitVoxelsIndex,Xk);
			
			/*//Testing Forward per ray
			for(int bla=0;bla<MyHitVoxelsIndex.size();bla=bla+1)
			{
				std::cout<<MyData[MyHitVoxelsIndex[bla]]<<std::endl;
			}*/
	
	return 0;
}
