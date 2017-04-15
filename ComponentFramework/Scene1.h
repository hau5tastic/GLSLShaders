#ifndef SCENE1_H
#define SCENE1_H
#include "Scene.h"
#include "Window.h"

namespace GAME {
	/// Forward casting
	class Trackball;
	class Model1;

	class Scene1 : public Scene {
	protected:

	public:
		explicit Scene1(Window& windowRef);
		virtual ~Scene1();

		/// Delete these possible default constructors and operators  
		Scene1(const Scene1&) = delete;
		Scene1(Scene1 &&) = delete;
		Scene1& operator=(const Scene1 &) = delete;
		Scene1& operator=(Scene1 &&) = delete;

		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float deltaTime);
		virtual void Render() const;
		virtual void HandleEvents(const SDL_Event &SDLEvent);
		virtual void OnResize(const int, const int);

	private:
		Vec3 lightPos;
		Model1 *model1;
		Trackball *trackball;
	};
}
#endif