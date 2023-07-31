#include <UgrCGL.hpp>

INT main(INT argv, LPSTR* argc)
{
	ugr::ConsoleWindow CW;
	CW.InitConsoleWindow();
	CW.CreateConsoleBufferWindow({ 128, 64 });
	CW.Display();
	return EXIT_SUCCESS;
}