#include <stdio.h>

#include <Curve.h>
#include <Patch.h>

int main (int argc, char ** argv)
{
	std::vector<BSpline> splines;

	{
		std::vector<vec3> control_points;

		control_points.push_back(vec3(0,0,0));
		control_points.push_back(vec3(1,0,0));
		control_points.push_back(vec3(2,0,0));
		control_points.push_back(vec3(3,0,0));
		control_points.push_back(vec3(4,0,0));
		control_points.push_back(vec3(5,0,0));

		splines.push_back(BSpline(control_points, 4));
	}

	{
		std::vector<vec3> control_points;

		control_points.push_back(vec3(0,1,0));
		control_points.push_back(vec3(1,1,0));
		control_points.push_back(vec3(2,1,0));
		control_points.push_back(vec3(3,1,0));
		control_points.push_back(vec3(4,1,0));
		control_points.push_back(vec3(5,1,0));

		splines.push_back(BSpline(control_points, 4));
	}

	{
		std::vector<vec3> control_points;

		control_points.push_back(vec3(0,2,0));
		control_points.push_back(vec3(1,2,0));
		control_points.push_back(vec3(2,2,0));
		control_points.push_back(vec3(3,2,0));
		control_points.push_back(vec3(4,2,0));
		control_points.push_back(vec3(5,2,0));

		splines.push_back(BSpline(control_points, 4, true));
	}

	{
		std::vector<vec3> control_points;

		control_points.push_back(vec3(0,3,0));
		control_points.push_back(vec3(1,3,0));
		control_points.push_back(vec3(2,3,0));
		control_points.push_back(vec3(3,3,0));
		control_points.push_back(vec3(5,3,0));

		splines.push_back(BSpline(control_points, 3));
	}

	std::vector<Curve*> curves;
	curves.push_back(&(splines[0]));
	curves.push_back(&(splines[1]));
	curves.push_back(&(splines[2]));
	curves.push_back(&(splines[3]));

	Patch patch(curves);

	for (int i = 0; i <= 100; ++i)
	{
		for (int j = 0; j <= 100; ++j)
		{
			vec3 p = patch.eval<BSpline>(i/100.0f, j/100.0f, 3, true);
			printf("%d,%d = %f ; %f ; %f \n", i, j, p.x, p.y, p.z);
		}
	}

	return 0;
}
