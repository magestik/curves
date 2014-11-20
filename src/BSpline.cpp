#include "BSpline.h"

#include <stdio.h>
#include <assert.h>

/**
 * @brief BSpline::BSpline
 * @param points
 * @param order
 */
BSpline::BSpline(const std::vector<vec3> & points, int order,  bool open_uniform)
: m_aControlPoints(points)
, m_aKnots()
, m_iOrder(order)
{
	int nbKnots = m_iOrder + m_aControlPoints.size(); // k + (n+1)

	int n = m_aControlPoints.size() - 1;

	if (!open_uniform)
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
vec3 BSpline::eval(float u)
{
	int interval = -1;

	int start		= m_iOrder;
	int end			= m_aControlPoints.size() + 1;

	float offset	= m_aKnots[start-1];
	float range		= m_aKnots[end-1] - m_aKnots[start-1];

	float u_in_range = offset + range * u;

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

	return(recurse_eval(points, knots, u_in_range, m_iOrder));
}

/**
 * @brief BSpline::recurse_eval
 * @param points
 * @param knots
 * @param u
 * @param k : order
 * @return
 */
vec3 BSpline::recurse_eval(std::vector<vec3> & points, std::vector<int> & knots, float u, int k)
{
	compute_points(points, knots, u, k--);

	points.pop_back();
	knots.pop_back();
	knots.erase(knots.begin());

	if (1 == k)
	{
		assert(1 == points.size());
		return(points[0]);
	}

	return recurse_eval(points, knots, u, k);
}

/**
 * @brief BSpline::iterative_eval
 * @param points
 * @param knots
 * @param u
 * @param k : order
 * @return
 */
vec3 BSpline::iterative_eval(std::vector<vec3> & points, std::vector<int> & knots, float u, int k)
{
	while (k > 1)
	{
		compute_points(points, knots, u, k--);

		points.pop_back();
		knots.pop_back();
		knots.erase(knots.begin());
	}

	assert(1 == points.size());

	return(points[0]);
}
