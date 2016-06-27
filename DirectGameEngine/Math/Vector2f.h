#pragma once

struct Vector2f 
{
	Vector2f() {}
	Vector2f(float v) : x{ v },y{ v }{}
	float x, y;
};