#include "triangle.h"

//In C++, implementing a class member declared in a header is done
//by specifying the parent class using CLASS:: before the function name.
Triangle::Triangle()
{
	v[0] = v[1] = v[2] = 0;
}

Triangle::Triangle(const Triangle& t)
{
	v[0] = t.v[0];
	v[1] = t.v[1];
	v[2] = t.v[2];
}

Triangle::Triangle(unsigned int v0, unsigned int v1, unsigned int v2)
{
	v[0] = v0;
	v[1] = v1;
	v[2] = v2;
}

Triangle::~Triangle()
{
}

unsigned int& Triangle::operator [] (unsigned int iv)
{
	return v[iv];
}

unsigned int Triangle::operator [] (unsigned int iv) const
{
	return v[iv];
}

Triangle& Triangle::operator = (const Triangle& t)
{
	v[0] = t.v[0];
	v[1] = t.v[1];
	v[2] = t.v[2];
	return (*this);
}
