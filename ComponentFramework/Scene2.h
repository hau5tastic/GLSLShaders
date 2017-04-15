#ifndef SCENE2_H
#define SCENE2_H
#include "Scene.h"
#include "Window.h"

namespace GAME {
	/// Forward casting
	class Trackball;
	class Model2;

	class Scene2 : public Scene {
	protected:

	public:
		explicit Scene2(Window& windowRef);
		virtual ~Scene2();

		/// Delete these possible default constructors and operators  
		Scene2(const Scene2&) = delete;
		Scene2(Scene2 &&) = delete;
		Scene2& operator=(const Scene2 &) = delete;
		Scene2& operator=(Scene2 &&) = delete;

		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float deltaTime);
		virtual void Render() const;
		virtual void HandleEvents(const SDL_Event &SDLEvent);
		virtual void OnResize(const int, const int);

	private:
		Vec3 lightPos;
		Model2 *model2;
		Trackball *trackball;
	};
}
#endif