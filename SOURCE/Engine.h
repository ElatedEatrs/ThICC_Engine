//--------------------------------------------------------------------------------------
// File: Game.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------

#pragma once

#include "StepTimer.h"
#include "ArcBall.h"
#include "RenderTexture.h"

#include "DeviceResourcesPC.h"

#include "GameFilepaths.h"
#include "RenderData.h"
#include "GameStateData.h"

#include "Game.h"

#include "InputData.h"


// A basic game implementation that creates a D3D12 device and
// provides a game loop.
class ThICC_Engine
	: public DX::IDeviceNotify
{
public:

	ThICC_Engine() noexcept(false);
	~ThICC_Engine();

	// Initialization and management
	void Initialize(HWND window, int width, int height);

	// Basic game loop
	void Tick();

	// IDeviceNotify
	virtual void OnDeviceLost() override;
	virtual void OnDeviceRestored() override;

	// Messages
	void OnActivated();
	void OnDeactivated();
	void OnSuspending();
	void OnResuming();
	void OnWindowMoved();
	void OnWindowSizeChanged(int width, int height);

	// Properties
	void GetDefaultSize(int& width, int& height) const;
	bool RequestHDRMode() const { return m_render_data.m_deviceResources ? (m_render_data.m_deviceResources->GetDeviceOptions() & DX::DeviceResources::c_EnableHDR) != 0 : false; }

private:

	void Update(DX::StepTimer const& timer);
	void Render();

	void Clear();

	void CreateDeviceDependentResources();
	void CreateWindowSizeDependentResources();

	void LoadModel(std::string filename);

	void CameraHome();

	void CreateProjection();

	GameFilepaths m_filepath;

	ThICC_Game m_game_inst;
	ThICC_InputData m_input_data;
	ThICC_RenderData m_render_data;
	ThICC_GameStateData m_gamestate_data;

	// Rendering loop timer.
	DX::StepTimer                                   m_timer;

	uint32_t                                        m_ibl;

	std::unique_ptr<DirectX::GraphicsMemory>        m_graphicsMemory;
	std::unique_ptr<DirectX::DescriptorPile>        m_resourceDescriptors;
	std::unique_ptr<DirectX::DescriptorHeap>        m_renderDescriptors;

	std::unique_ptr<DirectX::BasicEffect>                                   m_lineEffect;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>  m_lineBatch;

	std::unique_ptr<DirectX::ToneMapPostProcess>    m_toneMapACESFilmic;

	std::unique_ptr<DirectX::EffectTextureFactory>  m_gameMapResources;
	std::unique_ptr<DirectX::Model>                 m_gameMap;
	std::vector<std::shared_ptr<DirectX::IEffect>>  m_gameMapEffects;

	static const size_t s_nIBL = 3;

	Microsoft::WRL::ComPtr<ID3D12Resource>          m_radianceIBL[s_nIBL];
	Microsoft::WRL::ComPtr<ID3D12Resource>          m_irradianceIBL[s_nIBL];

	enum Descriptors
	{
		ConsolasFont,
		ComicFont,
		SceneTex,
		RadianceIBL1,
		RadianceIBL2,
		RadianceIBL3,
		IrradianceIBL1,
		IrradianceIBL2,
		IrradianceIBL3,
		Reserve,
		Count = 1024
	};

	enum RTVDescriptors
	{
		HDRScene,
		RTVCount
	};

	DirectX::SimpleMath::Matrix                     m_world;
	DirectX::SimpleMath::Matrix                     m_view;
	DirectX::SimpleMath::Matrix                     m_proj;

	DirectX::SimpleMath::Vector3                    m_cameraFocus;
	DirectX::SimpleMath::Vector3                    m_lastCameraPos;
	DirectX::SimpleMath::Quaternion                 m_cameraRot;
	DirectX::SimpleMath::Quaternion                 m_viewRot;

	DirectX::SimpleMath::Quaternion                 m_modelRot;

	float                                           m_fov;
	float                                           m_zoom;
	float                                           m_distance;
	float                                           m_farPlane;
	float                                           m_sensitivity;

	bool                                            m_reloadModel;

	int                                             m_toneMapMode;

	ArcBall                                         m_ballCamera;
	ArcBall                                         m_ballModel;
};