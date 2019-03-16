#include "pch.h"
#include "Game.h"
#include "RenderData.h"
#include "GameStateData.h"
#include "InputData.h"
#include "WindowData.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "DebugScene.h"
#include "ServiceLocator.h"
#include "CollisionManager.h"
#include "GameDebugToggles.h"
#include <iostream>
#include <experimental/filesystem>

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

bool GameDebugToggles::show_debug_meshes = false;

Game::Game() :
	m_WD(new WindowData),
	m_ID(new InputData),
	m_GSD(new GameStateData),
	m_RD(new RenderData),
	m_featureLevel(D3D_FEATURE_LEVEL_11_0),
	m_backBufferIndex(0),
	m_fenceValues{}
{
	//Read in track config
	std::ifstream i(m_filepath.generateFilepath("GAME_CORE", m_filepath.CONFIG));
	game_config << i;

	m_WD->m_window = nullptr;
	m_WD->m_outputHeight = game_config["window_height"];
	m_WD->m_outputWidth = game_config["window_width"];

	//Setup service locator
	Locator::setupRD(m_RD);
	Locator::setupWD(m_WD);
	Locator::setupGSD(m_GSD);
	Locator::setupID(m_ID);
}

Game::~Game()
{
	if (m_audEngine)
	{
		m_audEngine->Suspend();
	}

	// Ensure that the GPU is no longer referencing resources that are about to be destroyed.
	WaitForGpu();

	////delete the GO2Ds
	//for (vector<GameObject2D *>::iterator it = m_2DObjects.begin(); it != m_2DObjects.end(); it++)
	//{
	//	delete (*it);
	//}

	//m_2DObjects.clear();

	////delete the GO3Ds
	//for (vector<GameObject3D *>::iterator it = m_3DObjects.begin(); it != m_3DObjects.end(); it++)
	//{
	//	delete (*it);
	//}
	//m_3DObjects.clear();

	//delete the sounds
	for (vector<Sound *>::iterator it = m_sounds.begin(); it != m_sounds.end(); it++)
	{
		delete (*it);
	}
	m_sounds.clear();

	delete m_RD;
	delete m_GSD;
	delete m_ID;
	delete m_WD;

	VBGO3D::CleanUp();
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND _window, int _width, int _height)
{
	//Make sure our assets are compiled at least to some degree!
	if (!dirExists("DATA")) {
		throw std::exception("ASSETS MUST BE COMPILED BEFORE RUNNING THE GAME");
	}

	//Initialise our DirectX systems
	initDX(_window, _width, _height);

	//Set our default font
	setDefaultFont("NeueHaasGroteskDisp Pro BD");

	GetDefaultSize(m_WD->m_width, m_WD->m_height);

	//Set Up VBGO render system
	if (!VBGO3D::SetUpVBGOs())
	{
		ExitGame();//if anything fails in setting up, QUIT!
	}

	//Configure localisation
	m_localiser.configure(game_config["language"]); 

	//Setup keybinds
	m_keybinds.setup(m_GSD);

	//Create all GameObjects
	//createAllObjects2D();
	//createAllObjects3D();

	//debug: output our current directory
	std::cout << std::experimental::filesystem::current_path() << std::endl;

	//Push back all our game objects to their associated arrays
	//pushBackObjects();

	// Setup our Platform
	//ultralight::Platform& platform = ultralight::Platform::instance();
	//platform.set_config(ultralight::Config());
	//platform.set_gpu_driver(new GPUDriverD3D(new D3DRenderer()));
	//platform.set_font_loader(new FontLoaderWin());

	// Create the Renderer
	//ultralight::Ref<ultralight::Renderer> renderer = ultralight::Renderer::Create();

	// Create the View
	//ultralight::Ref<ultralight::View> view = renderer->CreateView(800, 600, false);
	//view->LoadHTML("<h1>Hello World!</h1>");

	//Setup scene manager and all scenes
	m_sceneManager.addScene(new MenuScene(), Scenes::MENUSCENE);
	m_sceneManager.addScene(new GameScene(), Scenes::GAMESCENE);
	m_sceneManager.addScene(new DebugScene(), Scenes::DEBUGSCENE);
	m_sceneManager.setCurrentScene(Scenes::MENUSCENE);
}

/* Create all 2D game objects */
void Game::createAllObjects2D()
{
	//text example 2D objects
	//ImageGO2D *test = new ImageGO2D(m_RD, "twist");
	//test->SetOri(45);
	//test->SetPos(Vector2(200, 300));
	//test->CentreOrigin();
	//test->SetScale(0.5f*Vector2::One);
	//m_2DObjects.push_back(test);
	//test = new ImageGO2D(m_RD, "guides_logo");
	//test->SetPos(Vector2(100, 100));
	//test->SetScale(Vector2(5.0f, 0.5f));
	//test->SetColour(Color(1, 0, 0, 1));`
	//m_2DObjects.push_back(test);

	//Test Sounds
	Loop *loop = new Loop(m_audEngine.get(), "Course Intro Soundtrack");
	loop->SetVolume(0.1f);
	//loop->Play();
	m_sounds.push_back(loop);

	TestSound* TS = new TestSound(m_audEngine.get(), "Explo1");
	m_sounds.push_back(TS);
}

/* Create all 3d game objects */
void Game::createAllObjects3D()
{

}

/* Push misc objects around */
void Game::pushBackObjects()
{

}

/* Update is called once per frame */
void Game::Update(DX::StepTimer const& _timer)
{
	//Poll Keyboard and Mouse
	//More details here: https://github.com/Microsoft/DirectXTK/wiki/Mouse-and-keyboard-input
	//You can find out how to set up controllers here: https://github.com/Microsoft/DirectXTK/wiki/Game-controller-input
	m_GSD->m_prevKeyboardState = m_GSD->m_keyboardState; // keep previous state for just pressed logic
	m_GSD->m_keyboardState = m_ID->m_keyboard->GetState();
	m_GSD->m_mouseState = m_ID->m_mouse->GetState();


	m_GSD->m_dt = float(_timer.GetElapsedSeconds());
	m_sceneManager.Update();
}

/* render the scene */
void Game::Render()
{
	//// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	//// Prepare the command list to render a new frame.
	Clear();

	m_sceneManager.Render(m_commandList);
	// Show the new frame.
	Present();
	m_graphicsMemory->Commit(m_commandQueue.Get());
}

/* configure window size */
void Game::GetDefaultSize(int& _width, int& _height) const
{
	_width = game_config["window_width"];
	_height = game_config["window_height"];
}

/* setup a viewport */
void Game::SetViewport(int i_, float _TopLeftX, float _TopLeftY, float _Width, float _Height)
{
	m_WD->m_viewport[i_] = { _TopLeftX,_TopLeftY,_Width,_Height, D3D12_MIN_DEPTH, D3D12_MAX_DEPTH };
	m_WD->m_scissorRect[i_] = { (int)_TopLeftX,(int)_TopLeftY,(int)(_Width),(int)(_Height) };
}