#include <windows.h>
#include "dxmain.h"

class TestApp : public dxmain
{
public:
	TestApp(HINSTANCE hInstance);
	~TestApp() = default;

	bool Init() override;
	bool Update(float dt) override;
	void Render(float dt) override;
};

TestApp::TestApp(HINSTANCE hInstance) : dxmain(hInstance)
{

}

bool TestApp::Init()
{
	return dxmain::Init();
}

bool TestApp::Update(float dt)
{
	return false;
}

void TestApp::Render(float dt)
{
}

/* Entry point */
int WINAPI WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd)
{
	//MessageBox(NULL, "Hello world", "Test", 0);

	TestApp tApp(hInstance);
	if (!tApp.Init()) 
	{
		return 1;
	}

	return tApp.Run();
}

