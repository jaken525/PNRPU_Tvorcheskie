#include "Window.h"
#include <iostream>

using namespace BCCTool;

std::string currentPath = fs::current_path().string();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew Window);

    return 0;
}

