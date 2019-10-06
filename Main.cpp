#include "MyWinHeader.h"

#include <string>
#include <sstream>

#include "Triangle.h"
#include "TriangleWobbler.h"

#include "Window.h"
#include "Keyboard.h"
#include "KeyboardWindowConnector.h"
#include "WindowToKeyboardPipe.h"
#include <iostream>

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE pInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	try
	{
		Window wnd(800, 300, "My first custom window");
		Keyboard keyboard;
		auto connector = std::make_shared<KeyboardWindowConnector>(wnd);
		keyboard.Subscribe(connector);

		auto connector2 = std::make_shared<WindowToKeyboardPipe>(keyboard);
		wnd.Subscribe(connector2);
		
		Triangle t = Triangle(wnd.GetWindowHandle(),Position(0,0.5f),1.0f,1.0f);
		TriangleWobbler wobble = TriangleWobbler(t,1.0f,1.0f);
		MSG msg = { 0 };

		BOOL result = { 0 };
		
		while (true)
		{
			wobble.Tick();
		}

		while ((result = PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) > 0 && msg.message != WM_QUIT)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			
		}
		if (msg.message == WM_QUIT)
		{
			return msg.wParam;
		}
	}
	catch (const WindowException& e)
	{
		MessageBox(nullptr, e.what(), "Window exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Unknown exception :'(", MB_OK | MB_ICONEXCLAMATION);
	}
	
	return EXIT_SUCCESS;
}