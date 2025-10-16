#include "../Core/Engine.h"
#include "../Core/Window.h"
#include "RuntimeContext.h"
#include "SystemManager.h"
#include "../Core/Timer.h"
#include "../Core/Logger.h"

int main()
{
	Orca::Engine engine;
	Orca::RuntimeContext ctx;
	Orca::Window* window = new Orca::Window(1280, 720, "Orca(R) Engine");;
	Orca::Timer timer;

	engine.Initialize(ctx);
	engine.SetWindow(window);

	if (!window || !window->GetNativeWindow())
	{
		delete window;
		return 1;
	}

	while (engine.IsRunning())
	{
		engine.Update(ctx);
		engine.Render(ctx);
	}

	if (window)
	{
		delete window;
	}

	engine.Shutdown();
	return 0;
}