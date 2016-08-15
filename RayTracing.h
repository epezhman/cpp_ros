#include <iostream>
#include "EntryPoint.h"

class RayTracing
{
public:
	RayTracing(Volume,GetRay,EntryPoint);
	std::vector<int> getHitVoxelsIndex();

private:
	std::vector<int> HitVoxelsIndex;

};
