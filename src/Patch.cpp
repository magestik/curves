#include "Patch.h"

#include "Curve.h"

#include <assert.h>

/**
 * @brief Patch::Patch
 * @param dir
 * @param gen
 */
Patch::Patch()
{
	// ...
}

/**
 * @brief Patch::Patch
 * @param curves
 */
Patch::Patch(const std::vector<Curve*> & curves)
: m_aCurves(curves)
{
	// ...
}

/**
 * @brief Patch::eval
 * @param u
 * @param v
 * @return
 */
template<class T, class ... Types>
vec3 Patch::eval(float u, float v, Types ... args) const
{
	std::vector<vec3> gen;

	for (const Curve * c : m_aCurves)
	{
		gen.push_back(c->eval(v));
	}

	T b(gen);

	return(b.eval(u));
}

/**
 * @brief Patch::eval<BSpline>
 * @param u
 * @param v
 * @param order
 * @param open_uniform
 * @return
 */
template<>
vec3 Patch::eval<BSpline>(float u, float v, int order, bool open_uniform) const
{
	std::vector<vec3> gen;

	for (const Curve * c : m_aCurves)
	{
		gen.push_back(c->eval(v));
	}

	BSpline b(gen, order, open_uniform);

	return(b.eval(u));
}

/**
 * @brief Patch::eval<BSpline>
 * @param u
 * @param v
 * @param order
 * @param open_uniform
 * @return
 */
template<>
vec3 Patch::eval<LagrangeInterpolator>(float u, float v, int order, bool open_uniform) const
{
	std::vector<vec3> gen;

	for (const Curve * c : m_aCurves)
	{
		gen.push_back(c->eval(v));
	}

	LagrangeInterpolator b(gen);

	return(b.eval(u));
}
