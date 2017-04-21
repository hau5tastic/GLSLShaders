#include <GL/glew.h>
#include <SDL.h>
#include "Scene3.h"
#include <iostream>
#include "MMath.h"
#include "QuadSphere.h"
#include "Model1.h"
#include "Model3.h"
#include "Trackball.h"

using namespace GAME;
using namespace MATH;

Scene3::Scene3(Window & windowRef) : Scene(windowRef), model3(nullptr)
{
	trackball = new Trackball();
	projectionMatrix.loadIdentity();
	viewMatrix.loadIdentity();
}

Scene3::~Scene3()
{
	OnDestroy();
}

bool Scene3::OnCreate()
{
	OnResize(windowPtr->GetWidth(), windowPtr->GetHeight());

	/// Load Assets: as needed 
	lightPos = Vec3(0.0f, 0.0f, 0.0f);

	model3 = new Model3();
	model3->SetVel(Vec3(0.0f, 0.0f, 0.0f));
	model3->SetPos(Vec3(0.0f, 0.0f, 0.0f));

	model1 = new Model1();
	model1->SetVel(Vec3(0.0f));
	model1->SetVel(Vec3(0.0f));

	return true;
}

void Scene3::OnDestroy()
{
	/// Cleanup Assets
	if (model3) delete model3;
	model3 = nullptr;
	if (trackball) delete trackball;
	trackball = nullptr;
}

void Scene3::Update(const float deltaTime)
{
	model3->Update(deltaTime);
}

void Scene3::Render() const
{
	/// Draw your scene here
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model3->Render(projectionMatrix, MMath::scale(15.0f, 15.0f, 15.0f) * trackball->GetMatrix4() *  viewMatrix, trackball->GetMatrix3());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	model1->Render(projectionMatrix, MMath::scale(1.0f, 1.0f, 1.0f) * trackball->GetMatrix4() * viewMatrix, trackball->GetMatrix3());

	SDL_GL_SwapWindow(windowPtr->getSDLWindow());
}

void Scene3::HandleEvents(const SDL_Event & SDLEvent)
{
	if (SDLEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
		trackball->OnLeftMouseDown(SDLEvent.button.x, SDLEvent.button.y);
	}
	if (SDLEvent.type == SDL_EventType::SDL_MOUSEMOTION &&
		SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		trackball->OnMouseMove(SDLEvent.button.x, SDLEvent.button.y);
	}
}

void Scene3::OnResize(const int w_, const int h_)
{
	windowPtr->SetWindowSize(w_, h_);
	glViewport(0, 0, windowPtr->GetWidth(), windowPtr->GetHeight());
	float aspect = float(windowPtr->GetWidth()) / float(windowPtr->GetHeight());

	projectionMatrix = MMath::perspective(45.0f, aspect, 1.0f, 100.0f);

	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 10.0f),
		Vec3(0.0f, 0.0f, 0.0f),
		Vec3(0.0f, 1.0f, 0.0f));
}
