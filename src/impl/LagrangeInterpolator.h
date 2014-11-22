#pragma once

#include "../Curve.h"

class LagrangeInterpolator : public Curve
{

public:

	explicit LagrangeInterpolator(const std::vector<vec3> & points);

	virtual vec3 eval(float u) const;

protected:

	inline float L(int i, float u) const;

private:

};
