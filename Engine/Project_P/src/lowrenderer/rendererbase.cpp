#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utils/memleaks.hpp"

#include "lowrenderer/rendererbase.hpp"

struct GPUMeshBase : GPUMesh
{
	GLuint VAO;
};

struct GPUTextureBase : GPUTexture
{
	GLuint data;
};

struct GPUMaterialBase : GPUMaterial
{

};

LowRenderer::RendererBase::RendererBase(const char* shader)
{
	this->shader = new Shader(shader);
}

LowRenderer::RendererBase::~RendererBase()
{
	delete shader;
}

void LowRenderer::RendererBase::render()
{
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST);
}

GPUMesh* LowRenderer::RendererBase::generateGPUMesh(const Mesh& mesh)
{
	GPUMeshBase* gpu = new GPUMeshBase();

	//VBO
	GLuint VBO;
	glGenBuffers(1, &VBO);

	//VAO
	glGenVertexArrays(1, &gpu->VAO);
	glBindVertexArray(gpu->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data(), GL_STATIC_DRAW);
	//vertex position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//vertex normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	glDeleteBuffers(1, &VBO);

	return gpu;
}

GPUTexture* LowRenderer::RendererBase::generateGPUTexture(const Texture& tex)
{
	GPUTextureBase* gpu = new GPUTextureBase();

	glGenTextures(1, &gpu->data);

	glBindTexture(GL_TEXTURE_2D, gpu->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (tex.data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex.dim.width, tex.dim.height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex.data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	return gpu;
}

GPUMaterial* LowRenderer::RendererBase::generateGPUMaterial(const Material& mat)
{
	return nullptr;
}