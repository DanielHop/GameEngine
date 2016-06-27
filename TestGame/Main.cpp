#include <windows.h>

#include "Instances/Test.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nShowCmd)
{
	Test test{hInstance, nShowCmd};
	test.Start();
}