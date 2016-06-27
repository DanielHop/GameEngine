#pragma once

struct Vector3f
{
	Vector3f() {}
	Vector3f(float v, float z = 0) : x{ v }, y{ v }, z{ z } {}
	Vector3f(float px, float py, float pz): x{ px }, y{ py }, z{ pz }{}
	float x, y, z;
};