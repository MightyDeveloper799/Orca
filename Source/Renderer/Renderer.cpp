#include "Renderer.h"
#include <GL/glew.h>

namespace Orca
{
	void Renderer::Init()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}

	void Renderer::BeginFrame()
	{

	}

	void Renderer::DrawMesh(const Mesh& mesh, const Shader& shader, const glm::mat4& transform) 
	{
		shader.Bind();
		shader.SetMat4("u_Model", transform);
		
		mesh.Bind();
		mesh.Draw();
		mesh.Unbind();

		shader.Unbind();
	}
}