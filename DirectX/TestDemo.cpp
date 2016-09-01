#include "d3dApp.h"
#include "d3dx11Effect.h"
#include "GeometryGenerator.h"
#include "MathHelper.h"
#include "LightHelper.h"
#include "Effects.h"
#include "Vertex.h"
#include "Camera.h"
#include "RenderStates.h"
//#include "FontMgr.h"
#include "vld.h"

//#include "BoxMesh.h"
#include "DirectXMy2DCollision\CasesDataHolder.h"
#include "DirectXMy2DCollision\CollisionCheck.h"

class TestDemoApp : public D3DApp
{
public:
	TestDemoApp(HINSTANCE hInstance);
	~TestDemoApp();

	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();

	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);

private:

private:
	
//	FontMgr mFontMgr;
//	FontClass * mTestFont;
	CasesDataHolder cdh;

	DirectionalLight mDirLights[3];

	Camera mCam;

	POINT mLastMousePos;

//	BoxMesh * mBox;

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	TestDemoApp theApp(hInstance);

	if (!theApp.Init())
		return 0;

	return theApp.Run();
}


TestDemoApp::TestDemoApp(HINSTANCE hInstance)
	: D3DApp(hInstance)
	//	mTestFont(0), mBox(0)
{
	mMainWndCaption = L"Test Demo";

	mLastMousePos.x = 0;
	mLastMousePos.y = 0;

	//mCam.SetPosition(0.0f, 2.0f, -15.0f);
	mCam.LookAt(XMFLOAT3(0.0f, 500.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));

	mDirLights[0].Ambient = XMFLOAT4(0.6f, 0.6f, 0.6f, 1.0f);
	mDirLights[0].Diffuse = XMFLOAT4(0.8f, 0.7f, 0.7f, 1.0f);
	mDirLights[0].Specular = XMFLOAT4(0.6f, 0.6f, 0.7f, 1.0f);
	mDirLights[0].Direction = XMFLOAT3(-0.57735f, -0.57735f, 0.57735f);

	mDirLights[1].Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mDirLights[1].Diffuse = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
	mDirLights[1].Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mDirLights[1].Direction = XMFLOAT3(0.707f, -0.707f, 0.0f);

	mDirLights[2].Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mDirLights[2].Diffuse = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	mDirLights[2].Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mDirLights[2].Direction = XMFLOAT3(0.0f, 0.0, -1.0f);

}

TestDemoApp::~TestDemoApp()
{
	Effects::DestroyAll();
	InputLayouts::DestroyAll();
	RenderStates::DestroyAll();
	
//	SafeDelete(mBox);
	
}

bool TestDemoApp::Init()
{
	if (!D3DApp::Init())
		return false;

	// Must init Effects first since InputLayouts depend on shader signatures.
	Effects::InitAll(md3dDevice);
	InputLayouts::InitAll(md3dDevice);
	RenderStates::InitAll(md3dDevice);

//	mFontMgr.Init(md3dDevice);
//	mTestFont = mFontMgr.CreateFontClass(L"Default");

//	mBox = new BoxMesh(md3dDevice, md3dImmediateContext, 1.0f, 1.0f, 1.0f);

	cdh.ReadFilePath(md3dDevice, L"input1.txt");

	return true;
}

void TestDemoApp::OnResize()
{
	D3DApp::OnResize();

	mCam.SetLens(0.25f*MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);

	Convert::SetScreenSize(mClientWidth, mClientHeight);
}

void TestDemoApp::UpdateScene(float dt)
{
	//
	// Control the camera.
	//
	if (GetAsyncKeyState('W') & 0x8000)
		mCam.Walk(10.0f*dt);

	if (GetAsyncKeyState('S') & 0x8000)
		mCam.Walk(-10.0f*dt);

	if (GetAsyncKeyState('A') & 0x8000)
		mCam.Strafe(-10.0f*dt);

	if (GetAsyncKeyState('D') & 0x8000)
		mCam.Strafe(10.0f*dt);

	mCam.UpdateViewMatrix();

	cdh.CreateBuffers(md3dDevice);

}

void TestDemoApp::DrawScene()
{
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::LightSteelBlue));
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	XMMATRIX view = mCam.View();
	XMMATRIX proj = mCam.Proj();
	XMMATRIX viewProj = mCam.ViewProj();

	RECT rc;
	rc.bottom = 100.0f;
	rc.left = 100.0f;
	rc.right = 100.0f;
	rc.top = 100.0f;

	XMMATRIX world = XMMatrixIdentity();
	XMMATRIX worldViewProj = world*view*proj;

//	Effects::FontFX->SetWorldViewProj(worldViewProj);
//	mBox->Draw(worldViewProj);

//	for (UINT i = 0; i < 100; i++)
//	{
//		mTestFont->Draw(md3dImmediateContext, L"Hello World!", rc, reinterpret_cast<const float*>(&Colors::Black));
//		rc.top += 1.0f;
//	}
//	rc.top += 100.0f;
//	mTestFont->Draw(md3dImmediateContext, L"Hi!", rc, reinterpret_cast<const float*>(&Colors::Red));

//	mBox->Draw(worldViewProj);


	D3DX11_TECHNIQUE_DESC techDesc;
	ID3DX11EffectTechnique* tech = Effects::TestFX->ColorTech;
	Effects::TestFX->SetWorldViewProj(worldViewProj);

	md3dImmediateContext->RSSetState(RenderStates::WireframeRS);

	tech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		std::shared_ptr<CaseData> cd(cdh.GetCaseData(0));
		std::shared_ptr<DamageZonePolygon> dzp(cdh.GetCaseData(0)->GetDZP());

		// dzp draw
		Effects::TestFX->SetObjectColor(Colors::Magenta);
		tech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
		dzp->Draw(md3dImmediateContext);

		for (int i = 0; i < cdh.GetCaseData(0)->GetPolygonsCnt(); i++)
		{
			Effects::TestFX->SetObjectColor(Colors::Black);
			std::shared_ptr<MyPolygon> polygon(cdh.GetCaseData(0)->GetPolygon(i));
			
			//if (AABBCollisionCheck(dzp, polygon)) Effects::TestFX->SetObjectColor(Colors::Cyan);
			if (SATCollisionCheck(dzp, polygon)) Effects::TestFX->SetObjectColor(Colors::Cyan);
			tech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
			polygon->Draw(md3dImmediateContext);
		}

	}

	HR(mSwapChain->Present(0, 0));
}

void TestDemoApp::OnMouseDown(WPARAM btnState, int x, int y)
{
	mLastMousePos.x = x;
	mLastMousePos.y = y;

	SetCapture(mhMainWnd);
}

void TestDemoApp::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}

void TestDemoApp::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON) != 0)
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = XMConvertToRadians(0.25f*static_cast<float>(x - mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f*static_cast<float>(y - mLastMousePos.y));

		mCam.Pitch(dy);
		mCam.RotateY(dx);
	}

	mLastMousePos.x = x;
	mLastMousePos.y = y;
}
