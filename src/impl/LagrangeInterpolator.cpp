#include "LagrangeInterpolator.h"

#include <assert.h>

/**
 * @brief LagrangeInterpolator::LagrangeInterpolator
 * @param points
 */
LagrangeInterpolator::LagrangeInterpolator(const std::vector<vec3> & points)
: Curve(points)
{
	// ...
}

/**
 * @brief LagrangeInterpolator::eval
 * @param u
 * @return
 */
vec3 LagrangeInterpolator::eval(float u) const
{
	int n = m_aControlPoints.size();

	float u_in_range = (n-1) * u; // u is in [0,1] so we have to put u in knots range

	vec3 p(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < n; ++i)
	{
		p = p + (L(i, u_in_range) * m_aControlPoints[i]);
	}

	return(p);
}

/**
 * @brief L
 * @param i
 * @param u
 * @return
 */
inline float LagrangeInterpolator::L(int i, float u) const
{
	int n = m_aControlPoints.size();

	float p = 1.0f;

	for (int j = 0; j < n; ++j)
	{
		if (i != j)
		{
			p *= (u - j) / (i - j);
		}
	}

	return(p);
}
