#include "pch.h"
#include "Main.h"
#include "Engine/Game.h"
#include "OrthographicDemo.h"
#include "ButtonDemo.h"
#include "BillBoardDemo.h"
#include "StaticMeshDemo.h"
#include "Client.h"
#include "Title.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameDesc desc;
	desc.appName = L"GameCoding";
	desc.hInstance = hInstance;
	desc.vsync = false;
	desc.hWnd = NULL;
	desc.width = 800;
	desc.height = 600;
	desc.clearColor = Color(0.f, 0.5f, 1.0f, 0.5f);
	desc.app = make_shared<ButtonDemo>();

	GAME->Run(desc);

	return 0;
}
