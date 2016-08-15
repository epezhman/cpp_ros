#include "OnTheFlyMx.h"

float OnTheFlyMx::ForwardProjection(std::vector <int> FlyHitVoxelsIndex, Eigen::VectorXf FlyVol2ForwardData) //FlyHitVoxelsIndex per ray . A*x
{
	float fi=0;
	for (int i{0}; i<FlyHitVoxelsIndex.size(); i=i+1)
	{
		fi=fi+FlyVol2ForwardData[FlyHitVoxelsIndex[i]];
	}
	return fi;
}

float OnTheFlyMx::BackwardProjection(std::vector <int> FlyHitVoxelsIndexB, Eigen::VectorXf zi) //zi "value per ray". A'*z
{
	float bi=0;
	/*for (int i{0}; i<FlyHitVoxelsIndex.size(); i=i+1)
	{
		fi=fi+FlyVol2ForwardData[FlyHitVoxelsIndex[i]];
	}*/
	return bi;
}
