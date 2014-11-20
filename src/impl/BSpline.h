#pragma once

#include "../Curve.h"

class BSpline : public Curve
{

public:

	explicit BSpline(const std::vector<vec3> & points, int order, bool open_uniform = true);

	virtual vec3 eval(float u) const;

	int order(void) const
	{
		return(m_iOrder);
	}

	bool openUniform(void) const
	{
		return(m_bOpenUniform);
	}

protected:

	int find_interval(float u) const;

	vec3 recurse_eval(std::vector<vec3> & points, std::vector<int> & knots, float u, int k) const;
	vec3 iterative_eval(std::vector<vec3> & points, std::vector<int> & knots, float u, int k) const;

	void compute_points(std::vector<vec3> & points, std::vector<int> & knots, float u, int k) const
	{
		for (int i = 0; i < k; ++i)
		{
			float alpha = (u - knots[i]) / (knots[i+k-1] - knots[i]);
			points[i] = (1.0f - alpha) * points[i] + alpha * points[i+1];
		}
	}

private:

	std::vector<int> m_aKnots;

	int m_iOrder; // = degree+1

	bool m_bOpenUniform;

};
