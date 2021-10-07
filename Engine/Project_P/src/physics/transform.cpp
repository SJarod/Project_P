#include "..\..\include\physics\transform.hpp"

mat4 Physics::Transform::getModelMatrix() const
{
	mat4 T, R, S;
	T = translateMatrix(m_position);
	R = rotateXMatrix(m_rotation.x * TORAD) * rotateYMatrix(m_rotation.y * TORAD) * rotateZMatrix(m_rotation.z * TORAD);
	S = scaleMatrix(m_scale);

	return T * R * S;
}