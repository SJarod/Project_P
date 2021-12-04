#pragma once

#include "lowrenderer/object.hpp"
#include "core/math/math.hpp"

namespace LowRenderer
{
	class Camera : public Object
	{
	private:
		bool	active = false;

		float	mouseSensitivity = 0.1f;
		float	moveSpeed = 1.f;
		double	mouseX = 0.f, mouseY = 0.f;
		float	oldX = 0.f, oldY = 0.f;

		//aspect ratio
		float	aspect = 16.f / 9.f;
		float	fovY = 75.f;

		float	near = 0.001f;
		float	far = 1000.f;

		mat4	frustum(const float& left, const float& right, const float& bot, const float& top, bool orthographic) const;

		mat4	getViewMatrix() const;

		//projection matrix (using frustum and 3D)
		mat4	getProjMatrix() const;
		//orthographic matrix
		mat4	getOrthMatrix() const;
		//choose perspective matrix
		mat4	getPerspective(const bool orthographic) const;

	public:
		virtual void	start() override;
		virtual void	update() override;

	public:
		Camera();

		inline void		setActive(bool active);

		mat4			getVPMatrix() const;
		mat4			getMVPMatrix(const mat4& modelMatrix) const;
	};
}

using namespace LowRenderer;

inline void LowRenderer::Camera::setActive(bool active)
{
	this->active = active;
}