#include <iostream>
#include <fstream>
#include <sstream>
#include <QImage>
#include <QtWidgets/QPushButton>
#include <string>
#include <vector>
#include <numeric>
#include <QtWidgets/QApplication> 
#include <QtWidgets/QMainWindow>

//#include "MHDHandler.h"
//#include "GetRay.h" //#include "SourceDetectorPair.h"
//#include "EntryPoint.h"//#include "GetRay.h" 
//#include "RayTracing.h"
//#include "OnTheFlyMx.h"
#include "OnTheFlySystemMx.h"
#include "window.h"


using namespace std;

int main(int argc, char **argv) //argv[0]=./Part2, argv[1]=vol.mhd, argv[2]=traj.csv, argv[3]=CG/SIRT, argv[4]=rvol.mhd
//int main()
{
	
	if (argc!=5)
	{
		std::cout<<"Error in arguments. Respect the order!!! e.g. ./Part2  ''vol.mhd'' ''trajectory.csv'' ''CG'' ''rvol.mhd''";
	}
	
	
	//--------------------------Read .mhd-------------------------------
	MHDHandler MyHandler;
	//std::string name ("box.mhd");
	std::string name=argv[1];
	Volume MyVolume=MyHandler.read(name);
	Eigen::VectorXf MyData=MyVolume.getContent();
	std::cout<<"Number of voxels=NX*NY*NZ="<<MyData.size()<<std::endl;

	//--------------------------Geometry--------------------------------
	//Read .cvs
	//std::string filename {"ws15cpp_trajectory.csv"};
	std::string filename=argv[2];
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
		
	//------------------------OnTheFlySystemMx--------------------------
	OnTheFlySystemMx MyFly;
	
	std::vector<float> y=MyFly.ForwardProjection(MyVolume, allValues, MyData);
	
			
	/*Eigen::VectorXf back=Eigen::VectorXf::Zero(MyData.size());
	std::vector<float> z=y;
	back=MyFly.BackwardProjection(MyVolume, allValues, z);*/
	
	//------------------R-E-C-O-N-S-T-R-U-C-T-I-O-N---------------------
	//...result
	Eigen::VectorXf result=Eigen::VectorXf::Zero(MyData.size());

	
	if (std::string (argv[3])=="CG")
	{
		//-------------------------------CG---------------------------------
		

		
		//...r
		std::vector<float> Aresult=MyFly.ForwardProjection(MyVolume, allValues, result);
		
		std::cout<<"y.size()="<<y.size()<<std::endl;
		std::cout<<"Aresult.size()="<<Aresult.size()<<std::endl;
		std::vector<float> yAresult;
		for(int indvec=0;indvec<y.size();indvec=indvec+1)
		{
			yAresult.push_back(y[indvec]-Aresult[indvec]);
			//std::cout<<indvec<<") yAresult=y-Aresult="<<y[indvec]<<"-"<<Aresult[indvec]<<"="<<yAresult[indvec]<<std::endl;
		}	
		
		Eigen::VectorXf r=MyFly.BackwardProjection(MyVolume, allValues, yAresult);

		//...d
		Eigen::VectorXf d=r;
		
		//...rtr
		float rtr=r.dot(r);
		std::cout<<"r.size(),d.size(),rtr="<<r.size()<<","<<d.size()<<","<<rtr<<std::endl;
		std::vector<float> rtrVector;
		rtrVector.push_back(rtr);
		//...Main Loop
		const int IterationsNum=200;
		std::vector<float> q;
		float alpha;
		float oldRtr;
		float qdotq;
		Eigen::VectorXf Atq;
		for (int iterator=0;iterator<IterationsNum;iterator=iterator+1)
		{
			q=MyFly.ForwardProjection(MyVolume,allValues,d);
			float acc=0;
			qdotq=std::inner_product(q.begin(),q.end(),q.begin(),acc);
			alpha=rtr/qdotq;
			result+=alpha*d;
			Atq=MyFly.BackwardProjection(MyVolume,allValues,q);
			r-=alpha*Atq;
			
			oldRtr=rtr;
			rtr=r.dot(r); rtrVector.push_back(rtr);
			d=r+(rtr/oldRtr)*d;
			
			//std::cout<<"q[20]="<<q[20]<<",q[50]="<<q[50]<<std::endl;
			//std::cout<<"qdotq="<<qdotq<<std::endl;
			//std::cout<<"alpha="<<alpha<<std::endl;
			//std::cout<<"rtr="<<rtr<<std::endl;
			//std::cout<<"rtrVector="<<rtrVector[iterator+1]<<std::endl;
			
		}
		
		std::cout<<"MyData-result="<<result.dot(MyData)<<std::endl;
	}
	
	
	if (std::string(argv[3])=="SIRT")
	//---------------------------SIRT-----------------------------------
	{
		float m=y.size();
		int SIRTIterations=200;
		std::vector<float> AXk;
		std::vector<float> yAXk;
		Eigen::VectorXf rSIRT;
		
		for (int SIRTIterator=0;SIRTIterator<SIRTIterations;SIRTIterator=SIRTIterator+1)
		{
			AXk=MyFly.ForwardProjection(MyVolume,allValues,result);
			for (int no=0;no<y.size();no=no+1)
			{
				yAXk.push_back(y[no]-AXk[no]);
			}
			rSIRT=MyFly.BackwardProjection(MyVolume,allValues,yAXk);
			result=result+(1/m)*rSIRT;
		}
	}
	
	//----------------------SAVE RESULTS--------------------------------
	
	Eigen::Vector3f lowLeftCorner=MyVolume.getLowerLeft();
	Eigen::Vector3f upRightCorner=MyVolume.getUpperRight();
	Eigen::VectorXf dimension=MyVolume.getDimSpacing();
	Volume OutputVol(lowLeftCorner,upRightCorner,dimension);
	OutputVol.setContent(result);
	
	MyHandler.write(argv[4],OutputVol);
//----------------------------------------------------------------------
// Part3
//----------------------------------------------------------------------
// QApplication manages the GUI applications control flow 
	QApplication a(argc, argv);

	// create a main window 
	QMainWindow qmw;
	// create a widget that spans the entire main window 
	window* mainWidget = new window();
	qmw.setCentralWidget(mainWidget);
	qmw.showMaximized();
	qmw.activateWindow();
	qmw.raise();
	qmw.show();
	// start the applications event loop 
	return a.exec();
	
	//return 0;
}
