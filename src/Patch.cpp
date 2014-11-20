#include "Patch.h"

#include <assert.h>

/**
 * @brief Patch::Patch
 * @param dir
 * @param gen
 */
template<class T>
Patch<T>::Patch(const std::vector<T> & curves)
: m_aCurves(curves)
{
	for (const T & c : m_aCurves)
	{
		assert(c.size() == m_aCurves[0].size());
	}
}

/**
 * @brief Patch::eval
 * @param u
 * @param v
 * @return
 */
template<>
vec3 Patch<BSpline>::eval(float u, float v) const
{
	std::vector<vec3> gen;

	for (const BSpline & c : m_aCurves)
	{
		gen.push_back(c.eval(v));
	}

	BSpline b(gen, m_aCurves[0].order(), m_aCurves[0].openUniform());

	return(b.eval(u));
}

template class Patch<BSpline>;
