#include "BSpline.h"

#include <assert.h>

#define SAFE 0

#ifndef USE_RECURSIVE_EVAL
#define USE_RECURSIVE_EVAL 0
#endif

/**
 * @brief BSpline::BSpline
 * @param points
 * @param order
 * @param open_uniform
 */
BSpline::BSpline(const std::vector<vec3> & points, int order,  bool open_uniform)
: Curve(points)
, m_aKnots()
, m_iOrder(order)
, m_bOpenUniform(open_uniform)
{
	int nbKnots = m_iOrder + m_aControlPoints.size(); // k + (n+1)

	int n = m_aControlPoints.size() - 1;

	if (!m_bOpenUniform)
	{
		for (int i = 0; i < nbKnots; ++i)
		{
			m_aKnots.push_back(i);
		}
	}
	else
	{
		for (int i = 0; i < m_iOrder - 1; ++i)
		{
			m_aKnots.push_back(0);
		}

		for (int i = m_iOrder - 1; i <= n+1; ++i)
		{
			m_aKnots.push_back(i - m_iOrder + 1);
		}

		for (int i = n+2; i < nbKnots; ++i)
		{
			m_aKnots.push_back(m_aKnots[n+1]);
		}
	}
}

/**
 * @brief BSpline::eval
 * @param u
 * @return
 */
vec3 BSpline::eval(float u) const
{
	int interval = -1;

	int start		= m_iOrder;
	int end			= m_aControlPoints.size() + 1;

	float offset	= m_aKnots[start-1];
	float range		= m_aKnots[end-1] - m_aKnots[start-1];

	float u_in_range = offset + range * u; // u is in [0,1] so we have to put u in knots range

	for (int i = start; i < end; ++i)
	{
		if (m_aKnots[i] >= u_in_range)
		{
			interval = i - 1;
			break;
		}
	}

	assert(-1 != interval);

	std::vector<vec3> points (m_aControlPoints.begin() + interval - (m_iOrder - 1), m_aControlPoints.begin() + interval + 1);
	std::vector<int> knots (m_aKnots.begin() + interval - (m_iOrder - 2), m_aKnots.begin() + interval + m_iOrder);

#if USE_RECURSIVE_EVAL
	return(recurse_eval(points, knots, u_in_range, m_iOrder));
#else
	return(iterative_eval(points, knots, u_in_range, m_iOrder));
#endif
}

#if USE_RECURSIVE_EVAL

/**
 * @brief BSpline::recurse_eval
 * @param points
 * @param knots
 * @param u
 * @param k
 * @return
 */

vec3 BSpline::recurse_eval(std::vector<vec3> & points, std::vector<int> & knots, float u, int k) const
{
	compute_points(points, knots, u, k--);

#if SAFE
	points.pop_back();
	knots.pop_back();
#endif // SAFE

	knots.erase(knots.begin());

	if (1 == k)
	{
#if SAFE
		assert(1 == points.size());
#endif // SAFE
		return(points[0]);
	}

	return recurse_eval(points, knots, u, k);
}

#else

/**
 * @brief BSpline::iterative_eval
 * @param points
 * @param knots
 * @param u
 * @param k
 * @return
 */
vec3 BSpline::iterative_eval(std::vector<vec3> & points, std::vector<int> & knots, float u, int k) const
{
	while (k > 1)
	{
		compute_points(points, knots, u, k--);

#if SAFE
		points.pop_back();
		knots.pop_back();
#endif // SAFE

		knots.erase(knots.begin());
	}

#if SAFE
	assert(1 == points.size());
#endif // SAFE

	return(points[0]);
}

#endif
