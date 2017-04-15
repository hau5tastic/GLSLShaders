#include <GL/glew.h>
#include <SDL.h>
#include "Scene2.h"
#include <iostream>
#include "MMath.h"
#include "QuadSphere.h"
#include "Model2.h"
#include "Trackball.h"

using namespace GAME;
using namespace MATH;

Scene2::Scene2(Window & windowRef): Scene(windowRef), model2(nullptr)
{
	trackball = new Trackball();
	projectionMatrix.loadIdentity();
	viewMatrix.loadIdentity();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

Scene2::~Scene2()
{
	OnDestroy();
}

bool Scene2::OnCreate()
{
	OnResize(windowPtr->GetWidth(), windowPtr->GetHeight());

	/// Load Assets: as needed 
	lightPos = Vec3(0.0f, 1.0f, 0.0f);
	model2 = new Model2();
	model2->SetVel(Vec3(0.0f, 0.0f, 0.0f));
	model2->SetPos(Vec3(0.0f, 0.0f, 0.0f));
	return true;
}

void Scene2::OnDestroy()
{
	/// Cleanup Assets
	if (model2) delete model2;
	model2 = nullptr;
	if (trackball) delete trackball;
	trackball = nullptr;
}

void Scene2::Update(const float deltaTime)
{
	model2->Update(deltaTime);
}

void Scene2::Render() const
{
	/// Draw your scene here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	model2->SetLightPos(viewMatrix * lightPos);
	model2->Render(projectionMatrix, trackball->GetMatrix4() *  viewMatrix, trackball->GetMatrix3());
	SDL_GL_SwapWindow(windowPtr->getSDLWindow());
}

void Scene2::HandleEvents(const SDL_Event & SDLEvent)
{
	if (SDLEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
		trackball->OnLeftMouseDown(SDLEvent.button.x, SDLEvent.button.y);
	}
	if (SDLEvent.type == SDL_EventType::SDL_MOUSEMOTION &&
		SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		trackball->OnMouseMove(SDLEvent.button.x, SDLEvent.button.y);
	}
}

void Scene2::OnResize(const int w_, const int h_)
{
	windowPtr->SetWindowSize(w_, h_);
	glViewport(0, 0, windowPtr->GetWidth(), windowPtr->GetHeight());
	float aspect = float(windowPtr->GetWidth()) / float(windowPtr->GetHeight());

	projectionMatrix = MMath::perspective(45.0f, aspect, 1.0f, 100.0f);

	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 10.0f),
		Vec3(0.0f, 0.0f, 0.0f),
		Vec3(0.0f, 1.0f, 0.0f));
}
