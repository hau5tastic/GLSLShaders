#ifndef SCENE3_H
#define SCENE3_H
#include "Scene.h"
#include "Window.h"

namespace GAME {
	/// Forward casting
	class Trackball;
	class Model1;
	class Model3;

	class Scene3 : public Scene {
	protected:

	public:
		explicit Scene3(Window& windowRef);
		virtual ~Scene3();

		/// Delete these possible default constructors and operators  
		Scene3(const Scene3&) = delete;
		Scene3(Scene3 &&) = delete;
		Scene3& operator=(const Scene3 &) = delete;
		Scene3& operator=(Scene3 &&) = delete;

		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float deltaTime);
		virtual void Render() const;
		virtual void HandleEvents(const SDL_Event &SDLEvent);
		virtual void OnResize(const int, const int);

	private:
		Vec3 lightPos;
		Model3 *model3; // skybox
		Model1 *model1; // skull
		Trackball *trackball;
	};
}
#endif