#include "core/math/math.hpp"
#include "core/math/quaternion.hpp"

#include <iostream>

Quaternion Core::Math::vec3::q() const
{
	Quaternion q = { 0, x, y, z };
	return q;
}

vec3 Core::Math::crossProduct(const vec3& a, const vec3& b)
{
	vec3 v;
	v.x = a.y * b.z - a.z * b.y;
	v.y = a.z * b.x - a.x * b.z;
	v.z = a.x * b.y - a.y * b.x;
	return v;
}

vec2 Core::Math::vec2Rotation(const vec2& v, const float& angle)
{
	float a = angle * TORAD;
	float x = cosf(a) * v.x - sinf(a) * v.y;
	float y = sinf(a) * v.x + cosf(a) * v.y;

	return { x, y };
}

mat4 Core::Math::translateMatrix(const vec3& pos)
{
	return mat4{
		1.f, 0.f, 0.f, pos.x,
		0.f, 1.f, 0.f, pos.y,
		0.f, 0.f, 1.f, pos.z,
		0.f, 0.f, 0.f, 1.f,
	};
}

mat4 Core::Math::rotateXMatrix(const float& pitch)
{
	float a = pitch * TORAD;
	return mat4{
		1.f, 0.f, 0.f, 0.f,
		0.f, cos(a), -sin(a), 0.f,
		0.f, sin(a), cos(a), 0.f,
		0.f, 0.f, 0.f, 1.f,
	};
}

mat4 Core::Math::rotateYMatrix(const float& yaw)
{
	float a = yaw * TORAD;
	return mat4{
		cos(a), 0.f, sin(a), 0.f,
		0.f, 1.f, 0.f, 0.f,
		-sin(a), 0.f, cos(a), 0.f,
		0.f, 0.f, 0.f, 1.f,
	};
}

mat4 Core::Math::rotateZMatrix(const float& roll)
{
	float a = roll * TORAD;
	return mat4{
		cos(a), -sin(a), 0.f, 0.f,
		sin(a), cos(a), 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f,
	};
}

mat4 Core::Math::scaleMatrix(const vec3& scale)
{
	return mat4{
		scale.x, 0.f, 0.f, 0.f,
		0.f, scale.y, 0.f, 0.f,
		0.f, 0.f, scale.z, 0.f,
		0.f, 0.f, 0.f, 1.f,
	};
}

void Core::Math::vec2::print() const
{
	std::cout << "---vec2---" << std::endl;
	std::cout << x << ", " << y << std::endl;
}

void Core::Math::vec3::print() const
{
	std::cout << "---vec3---" << std::endl;
	std::cout << x << ", " << y << ", " << z << std::endl;
}

void Core::Math::vec4::print() const
{
	std::cout << "---vec4---" << std::endl;
	std::cout << x << ", " << y << ", " << z << ", " << w << std::endl;
}

void Core::Math::mat3::print() const
{
	std::cout << "---mat3---" << std::endl;
	std::cout << c[0].x << ", " << c[0].y << ", " << c[0].z << std::endl;
	std::cout << c[1].x << ", " << c[1].y << ", " << c[1].z << std::endl;
	std::cout << c[2].x << ", " << c[2].y << ", " << c[2].z << std::endl;
}

void Core::Math::mat4::print() const
{
	std::cout << "---mat4---" << std::endl;
	std::cout << c[0].x << ", " << c[0].y << ", " << c[0].z << ", " << c[0].w << std::endl;
	std::cout << c[1].x << ", " << c[1].y << ", " << c[1].z << ", " << c[1].w << std::endl;
	std::cout << c[2].x << ", " << c[2].y << ", " << c[2].z << ", " << c[2].w << std::endl;
	std::cout << c[3].x << ", " << c[3].y << ", " << c[3].z << ", " << c[3].w << std::endl;
}