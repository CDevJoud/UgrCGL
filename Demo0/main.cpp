#include <Windows.h>
#include <UgrCGL.hpp>

int main(int argv, char** argc)
{
	ugr::ConsoleWindow CW;
	CW.InitConsoleWindow();
	CW.CreateConsoleBufferWindow({ 128, 64 });
	CW.SetPixel({10, 20 });
	CW.Display();
	return 0;
}