#include "physics\transform.hpp"

mat4 Physics::Transform::getModelMatrix() const
{
	using namespace Math3;

	mat4 T, R, S;
	T = translateMatrix(position);
	R = rotateXMatrix(rotation.x * TORAD) * rotateYMatrix(rotation.y * TORAD) * rotateZMatrix(rotation.z * TORAD);
	S = scaleMatrix(scale);

	return T * R * S;
}