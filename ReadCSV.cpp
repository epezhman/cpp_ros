#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>
#include <eigen3/Eigen/Dense>

using namespace std;

int main()
{

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
			allValues.push_back(std::stof(value));
		}
	}
	
	/*
	std::cout<<"totalData="<<allValues.size()/15<<std::endl;
	std::cout<<"Source:"<<std::endl;
	std::cout<<allValues[1]<<allValues[2]<<allValues[3]<<std::endl;
	std::cout<<allValues[4]<<allValues[5]<<allValues[6]<<allValues[7]<<std::endl;
		
	std::cout<<"Detector"<<std::endl;
	std::cout<<allValues[8]<<allValues[9]<<allValues[10]<<std::endl;
	std::cout<<allValues[11]<<allValues[12]<<allValues[13]<<allValues[14]<<std::endl;
	*/
	
	/*cout<<"This is a line 1:"<<line<<endl;
	std::getline(ist,line,'\n');
	cout<<"This is a line 2:"<<line<<endl;
	//ist.open(filename,ios_base::in);
	cout<<"!ist="<<!ist<<endl;
	
	if(!ist)
	std::cout<<"Can't open input file: "<<filename<<std::endl;
	
	*/
	
	return 0;
}
