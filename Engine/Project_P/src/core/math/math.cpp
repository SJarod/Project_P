#include "core/math/math.hpp"
#include "core/math/quaternion.hpp"

Quaternion Math::vec3::q() const
{
	Quaternion q = { 0, x, y, z };
	return q;
}

vec3 Math::crossProduct(const vec3& a, const vec3& b)
{
	vec3 v;
	v.x = a.y * b.z - a.z * b.y;
	v.y = a.z * b.x - a.x * b.z;
	v.z = a.x * b.y - a.y * b.x;
	return v;
}

vec2 Math::vec2Rotation(const vec2& v, const float& angle)
{
	float a = angle * TORAD;
	float x = cosf(a) * v.x - sinf(a) * v.y;
	float y = sinf(a) * v.x + cosf(a) * v.y;

	return { x, y };
}

mat4 Math::translateMatrix(const vec3& pos)
{
	return mat4{
		1.f, 0.f, 0.f, pos.x,
		0.f, 1.f, 0.f, pos.y,
		0.f, 0.f, 1.f, pos.z,
		0.f, 0.f, 0.f, 1.f,
	};
}

mat4 Math::rotateXMatrix(const float& pitch)
{
	float a = pitch * TORAD;
	return mat4{
		1.f, 0.f, 0.f, 0.f,
		0.f, cos(a), -sin(a), 0.f,
		0.f, sin(a), cos(a), 0.f,
		0.f, 0.f, 0.f, 1.f,
	};
}

mat4 Math::rotateYMatrix(const float& yaw)
{
	float a = yaw * TORAD;
	return mat4{
		cos(a), 0.f, sin(a), 0.f,
		0.f, 1.f, 0.f, 0.f,
		-sin(a), 0.f, cos(a), 0.f,
		0.f, 0.f, 0.f, 1.f,
	};
}

mat4 Math::rotateZMatrix(const float& roll)
{
	float a = roll * TORAD;
	return mat4{
		cos(a), -sin(a), 0.f, 0.f,
		sin(a), cos(a), 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f,
	};
}

mat4 Math::scaleMatrix(const vec3& scale)
{
	return mat4{
		scale.x, 0.f, 0.f, 0.f,
		0.f, scale.y, 0.f, 0.f,
		0.f, 0.f, scale.z, 0.f,
		0.f, 0.f, 0.f, 1.f,
	};
}

std::ostream& Math::operator<<(std::ostream& os, const vec2& v)
{
	os << "---vec2---" << std::endl;
	os << v.x << ", " << v.y;
	return os;
}

std::ostream& Math::operator<<(std::ostream& os, const vec3& v)
{
	os << "---vec3---" << std::endl;
	os << v.x << ", " << v.y << ", " << v.z;
	return os;
}

std::ostream& Math::operator<<(std::ostream& os, const vec4& v)
{
	os << "---vec4---" << std::endl;
	os << v.x << ", " << v.y << ", " << v.z << ", " << v.w;
	return os;
}

std::ostream& Math::operator<<(std::ostream& os, const mat3& m)
{
	os << "---mat3---" << std::endl;
	os << m.c[0].x << ", " << m.c[0].y << ", " << m.c[0].z << std::endl;
	os << m.c[1].x << ", " << m.c[1].y << ", " << m.c[1].z << std::endl;
	os << m.c[2].x << ", " << m.c[2].y << ", " << m.c[2].z;

	return os;
}

std::ostream& Math::operator<<(std::ostream& os, const mat4& m)
{
	os << "---mat4---" << std::endl;
	os << m.c[0].x << ", " << m.c[0].y << ", " << m.c[0].z << ", " << m.c[0].w << std::endl;
	os << m.c[1].x << ", " << m.c[1].y << ", " << m.c[1].z << ", " << m.c[1].w << std::endl;
	os << m.c[2].x << ", " << m.c[2].y << ", " << m.c[2].z << ", " << m.c[2].w << std::endl;
	os << m.c[3].x << ", " << m.c[3].y << ", " << m.c[3].z << ", " << m.c[3].w;

	return os;
}