#pragma once

#include <vector> 

struct Matrix4f
{
	Matrix4f()
	{
		for (int i = 0; i < 16; i++)
			matrix.push_back(0);

	}

	Matrix4f(float	aa, float ab, float ac, float ad,
		float ba, float bb, float bc, float bd,
		float ca, float cb, float cc, float cd,
		float da, float db, float dc, float dd) 
	{
		matrix.push_back(aa); matrix.push_back(ba); matrix.push_back(ca); matrix.push_back(da);
		matrix.push_back(ab); matrix.push_back(bb); matrix.push_back(cb); matrix.push_back(db);
		matrix.push_back(ac); matrix.push_back(bc); matrix.push_back(cc); matrix.push_back(dc);
		matrix.push_back(ad); matrix.push_back(bd); matrix.push_back(cd); matrix.push_back(dd);
	}

	std::vector<float>matrix;

};