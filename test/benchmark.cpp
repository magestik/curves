#include <stdio.h>
#include <stdlib.h>

#include <Curve.h>

int main (int argc, char ** argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Argument required : number of samples");
		return -1;
	}

	int nb_sample = atoi(argv[1]);

	std::vector<vec3> control_points;

	control_points.push_back(vec3(0,0,0));
	control_points.push_back(vec3(1,1,1));
	control_points.push_back(vec3(2,2,2));
	control_points.push_back(vec3(3,3,3));
	control_points.push_back(vec3(4,4,4));
	control_points.push_back(vec3(5,5,5));

	BSpline spline(control_points, 4);

	for (int i = 0; i <= nb_sample; ++i)
	{
		vec3 p = spline.eval(i/float(nb_sample));
		//printf("%d = %f ; %f ; %f \n", i, p.x, p.y, p.z);
	}

	return 0;
}
