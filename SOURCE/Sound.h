#pragma once
#include "pch.h"
#include "Audio.h"
#include "GameFilepaths.h"
#include <string>
#include <codecvt>

class Sound
{
public:
	Sound(DirectX::AudioEngine* _audEngine, std::string _filename);
	virtual ~Sound();

	virtual void Tick();

	virtual void Play();

	virtual void Stop();

	void SetVolume(float _vol) { m_volume = _vol; }
	float GetVolume() { return m_volume; }

	void SetPitch(float _pitch) { m_pitch = _pitch; }
	float GetPitch() { return m_pitch; }

	void SetPan(float _pan) { m_pan = _pan; }
	float GetPan() { return m_pan; }

	void SetLoop(bool _loop);

	bool IsPlaying() { return m_sfx->IsInUse(); }

	void Pause();
	const std::string& GetTag() { return tag; }
	void SetTag(const std::string& _tag) { tag = _tag; }

protected:
	std::unique_ptr<DirectX::SoundEffect> m_sfx;
	std::unique_ptr<DirectX::SoundEffectInstance> m_loop;

	float m_volume = 1.0f;
	float m_pitch = 0.0f;
	float m_pan = 0.0f;

	bool loop = false;
	bool m_playing = false;
	std::string filename = "";
	std::string tag = "";

	GameFilepaths m_filepath;
};

