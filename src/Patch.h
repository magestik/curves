#pragma once

#include <vector>

#include <Vector.h>

class Curve;
class BSpline;

class Patch
{

public:

	explicit Patch (void);
	explicit Patch (const std::vector<Curve*> & curves);

	template<class T, class ... Types>
	vec3 eval (float u, float v, Types ... args) const;

private:

	std::vector<Curve*> m_aCurves;

};

template<>
vec3 Patch::eval<BSpline>(float u, float v, int order, bool open_uniform) const;
