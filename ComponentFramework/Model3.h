#ifndef MODEL3_H
#define MODEL3_H
#include <GL\glew.h>
#include "Model.h"

namespace GAME {
	/// Forward declarations;
	class Shader;
	class QuadSphere;

	class Model3 :public Model
	{
	public:
		Model3();


		Model3(const Model3&) = delete;
		Model3(Model3&&) = delete;
		Model3& operator = (const Model3&) = delete;
		Model3& operator = (Model3&&) = delete;

		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float deltaTime);
		virtual void Render(const Matrix4& projectionMatrix, const Matrix4& modelViewMatrix, const Matrix3& normalMatrix) const;
		virtual ~Model3();

		void SetLightPos(const Vec3&);

	private:

		Shader *shader;
		GLuint vbo;
		GLuint vao;
		GLint verticiesID;
		GLint normalsID;
		GLint uvCoordsID;

		GLint projectionMatrixID;
		GLint modelViewMatrixID;
		GLint normalMatrixID;
		GLint lightPosID;
		Vec3 lightPos;
	};
}
#endif