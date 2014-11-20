#pragma once

#include <vector>

#include <Vector.h>

class Curve
{

public:

	explicit Curve (const std::vector<vec3> & points);

	virtual vec3 eval (float u) const = 0;

	int size(void) const
	{
		return(m_aControlPoints.size());
	}

protected:

	std::vector<vec3> m_aControlPoints;
};

#include "impl/BSpline.h"
