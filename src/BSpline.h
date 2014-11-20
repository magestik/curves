#pragma once

#include <vector>

#include <Vector.h>

class BSpline
{

public:

	explicit BSpline(const std::vector<vec3> & points, int order, bool open_uniform = true);

	vec3 eval(float u);

protected:

	int find_interval(float u);

	vec3 recurse_eval(std::vector<vec3> & points, std::vector<int> & knots, float u, int k);
	vec3 iterative_eval(std::vector<vec3> & points, std::vector<int> & knots, float u, int k);

	void compute_points(std::vector<vec3> & points, std::vector<int> & knots, float u, int k)
	{
		for (int i = 0; i < k; ++i)
		{
			float alpha = (u - knots[i]) / (knots[i+k-1] - knots[i]);
			points[i] = (1.0f - alpha) * points[i] + alpha * points[i+1];
		}
	}

private:

	std::vector<vec3>	m_aControlPoints;
	std::vector<int>	m_aKnots;

	int m_iOrder; // = degree+1

};
