#include <stdio.h>
#include <stdlib.h>

#include <Curve.h>

int main (int argc, char ** argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage : ./benchmark [number of control points] [number of samples]");
		return -1;
	}

	int nb_points = atoi(argv[1]);
	int nb_samples = atoi(argv[2]);

	std::vector<vec3> control_points;

	for (int i = 0; i < nb_points; ++i)
	{
		control_points.push_back(vec3(i,i,i));
	}

	BSpline spline(control_points, 4);

	for (int i = 0; i <= nb_samples; ++i)
	{
		vec3 p = spline.eval(i/float(nb_samples));
		//printf("%d = %f ; %f ; %f \n", i, p.x, p.y, p.z);
	}

	return 0;
}
