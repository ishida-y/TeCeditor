# include <Siv3D.hpp>
#include"Editor.h"

void Main()
{
	Window::Resize(1280, 720);

	Editor editor;

	while (System::Update())
	{
		ClearPrint();
		editor.update();
		editor.draw();
	}
}
