#include "Model3.h"
#include "QuadSphere.h"
#include "Shader.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "LoadTextureRAW.h"

using namespace GAME;

Model3::Model3() : shader(nullptr)
{
	OnCreate();
}


bool Model3::OnCreate()
{
	ObjLoader obj("cube.obj");

	meshes.push_back(new Mesh(GL_TRIANGLES, obj.vertices, obj.normals, obj.uvCoords));

	/// Create a shader with attributes
	shader = new Shader("skyBoxVert.glsl", "skyBoxFrag.glsl", 1, 0, "vVertex", NULL);

	projectionMatrixID = glGetUniformLocation(shader->getProgram(), "projectionMatrix");
	modelViewMatrixID = glGetUniformLocation(shader->getProgram(), "modelViewMatrix");

	GLuint loc = loadCubeMapRAW("posx.raw", "negx.raw", "posy.raw", "negy.raw", "posz.raw", "negz.raw", 2048, 2048);

	GLuint texture0 = glGetUniformLocation(shader->getProgram(), "skyBox");
	glUniform1i(texture0, loc);

	return true;
}

void Model3::OnDestroy()
{
	glDeleteBuffers(1, &vbo);
	if (shader) delete shader;

	for (Mesh* mesh : meshes) {
		if (mesh) delete mesh;
	}
}

void Model3::Update(const float deltaTime)
{
}

void Model3::Render(const Matrix4 & projectionMatrix, const Matrix4 & viewMatrix, const Matrix3 & normalMatrix) const
{
	glUseProgram(shader->getProgram());
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(modelViewMatrixID, 1, GL_FALSE, viewMatrix *  modelMatrix);

	for (Mesh* mesh : meshes) {
		mesh->Render();
	}
	glEnableVertexAttribArray(0); // Disable the VAO
}

Model3::~Model3()
{
	OnDestroy();
}

void Model3::SetLightPos(const Vec3 & lightPos_)
{
	lightPos = lightPos_;
}
