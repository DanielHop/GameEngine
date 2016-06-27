/*
#include "MatrixHelper.h"



MatrixHelper::MatrixHelper()
{
}


MatrixHelper::~MatrixHelper()
{
}

Matrix4f MatrixHelper::GenerateWorldMatrix(const std::shared_ptr<TransformationComponent> transformationComponent)
{
	Matrix4f rMatrix;
	SetIdentity(rMatrix);

	rMatrix.matrix[3 ] = transformationComponent->pos.x;
	rMatrix.matrix[7 ] = transformationComponent->pos.y;
	rMatrix.matrix[14] = transformationComponent->pos.z;

	return rMatrix;
}

Matrix4f MatrixHelper::GenerateViewMatrix(const std::shared_ptr<CameraComponent> component)
{
	Matrix4f rMatrix;
	SetIdentity(rMatrix);

	rMatrix.matrix[3 ] = -component->pos.x;
	rMatrix.matrix[7 ] = -component->pos.y;
	rMatrix.matrix[14] = -component->pos.z;

	return rMatrix;
}

Matrix4f MatrixHelper::GenerateOrthProjMatrix(float right, float left, float top, float bottom, float far, float near)
{
	Matrix4f rMatrix;
	SetIdentity(rMatrix);

	float rl = right - left;
	float tb = top - bottom;
	float fn = far - near;

	rMatrix.matrix[0] = 2 / rl;
	rMatrix.matrix[3] = -((right + left) / rl);

	rMatrix.matrix[5] = 2 / tb;
	rMatrix.matrix[7] = -((top + bottom) / tb);

	rMatrix.matrix[10] = -2 / fn;
	rMatrix.matrix[11] = -((far + near) / fn);

	return rMatrix;
}

Matrix4f MatrixHelper::GenerateOrthProjMatrix(float right, float top, float far, float near)
{
	Matrix4f rMatrix;
	SetIdentity(rMatrix);
	float fn = far - near;

	rMatrix.matrix[0] = 1/right;

	rMatrix.matrix[5] = 1/top;

	rMatrix.matrix[10] = -2 / fn;
	rMatrix.matrix[11] = -((far + near) / fn);

	return rMatrix;
}
Matrix4f MatrixHelper::GenerateOrthProjMatrix(float ar, float far, float near)
{
	Matrix4f rMatrix;
	SetIdentity(rMatrix);
	float right = ar;
	float top = 1;

	float fn = far - near;

	rMatrix.matrix[0] = 1 / right;

	rMatrix.matrix[5] = 1 / top;

	rMatrix.matrix[10] = -2 / fn;
	rMatrix.matrix[11] = -((far + near) / fn);

	return rMatrix;
}


Matrix4f MatrixHelper::GeneratePersProjMatrix(float ar, float zNear, float zFar, float FOV)
{
	Matrix4f rMatrix;
	SetIdentity(rMatrix);

	float zRange = zNear - zFar;
	float tanHalfFov = tan((FOV / 2) * 3.1415926f / 180.f);

	rMatrix.matrix.at(0) = 1.0f / (tanHalfFov * ar);
	rMatrix.matrix.at(5) = 1.0f / tanHalfFov;
	rMatrix.matrix.at(10) = -((zNear + zFar) / (zFar - zNear));
	rMatrix.matrix.at(11) = -1;
	rMatrix.matrix.at(14) = -((2 * zFar * zNear) / (zFar - zNear));
	rMatrix.matrix.at(15) = 0;

	return rMatrix;
}

Matrix4f MatrixHelper::GenerateIdentityMatrix()
{
	Matrix4f mat{ 1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f };

	return mat;
}

void MatrixHelper::SetIdentity(Matrix4f &matrix)
{
	Matrix4f mat{ 1.f, 0.f, 0.f, 0.f,
				0.f, 1.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f};

	matrix = mat;
}*/