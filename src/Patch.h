#pragma once

#include "Curve.h"

template<class T>
class Patch
{

public:

	explicit Patch (const std::vector<T> & curves);

	vec3 eval (float u, float v) const;

private:

	std::vector<T> m_aCurves;

};
