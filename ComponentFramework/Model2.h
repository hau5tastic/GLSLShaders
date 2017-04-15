#ifndef MODEL2_H
#define MODEL2_H
#include <GL\glew.h>
#include "Model.h"

namespace GAME {
	/// Forward declarations;
	class Shader;
	class QuadSphere;

	class Model2 :public Model
	{
	public:
		Model2();


		Model2(const Model2&) = delete;
		Model2(Model2&&) = delete;
		Model2& operator = (const Model2&) = delete;
		Model2& operator = (Model2&&) = delete;

		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float deltaTime);
		virtual void Render(const Matrix4& projectionMatrix, const Matrix4& modelViewMatrix, const Matrix3& normalMatrix) const;
		virtual ~Model2();

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