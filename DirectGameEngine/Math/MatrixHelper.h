#pragma once

#include <memory>
#include <math.h>

#include "Matrix4f.h"
#include "../Engine/Components/TransformationComponent.h"
#include "../Engine/Components/CameraComponent.h"

class MatrixHelper
{
public:
	MatrixHelper();
	~MatrixHelper();

	static Matrix4f GenerateWorldMatrix(const std::shared_ptr<TransformationComponent> component);
	static Matrix4f GenerateViewMatrix(const std::shared_ptr<CameraComponent> component);

	static Matrix4f GenerateOrthProjMatrix(float right, float left, float top, float bottom, float far, float near);
	static Matrix4f GenerateOrthProjMatrix(float right, float top, float far, float near);
	static Matrix4f GenerateOrthProjMatrix(float ar, float far, float near);
	static Matrix4f GeneratePersProjMatrix(float ar, float zNear, float zFar, float FOV);
	
	static Matrix4f GenerateIdentityMatrix();

	static void SetIdentity(Matrix4f &matrix);
};

