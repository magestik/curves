#include <stdio.h>

#include <Curve.h>

int main (int argc, char ** argv)
{
	std::vector<vec3> control_points;

	control_points.push_back(vec3(0,0,0));
	control_points.push_back(vec3(1,1,1));
	control_points.push_back(vec3(2,2,2));
	control_points.push_back(vec3(3,3,3));
	control_points.push_back(vec3(4,4,4));
	control_points.push_back(vec3(5,5,5));

	LagrangeInterpolator interp(control_points);

	for (int i = 0; i <= 100; ++i)
	{
		vec3 p = interp.eval(i/100.0f);
		printf("%d = %f ; %f ; %f \n", i, p.x, p.y, p.z);
	}

	return 0;
}
