#pragma once


#include <vector>
#include <memory>
#include <deque>
#include "../Systems/System.h"
#include "../Renderers/Renderer.h"
#include "../Shaders/ShaderProgram.h"

template<typename T>
struct NameClass
{
	std::shared_ptr<T> t;
	std::string name;
};

class SystemManager
{
public:
	SystemManager();
	~SystemManager();

	void Init();
	void OnTickUpdate(std::vector<std::shared_ptr<Entity>> entities, float dt);
	void RenderUpdate(std::vector<std::shared_ptr<Entity>> entities, ID3D11Device* device, ID3D11DeviceContext* context);


	template<typename T, typename... TArgs>
	void AddSystem(TArgs... args) {  m_systems.emplace_back(std::unique_ptr<T>(new T(args...))); }

	template<typename T, typename... TArgs>
	void Addrenderer(ID3D11Device* device, ID3D11DeviceContext* context, TArgs... args) { m_renderer.emplace_back(std::unique_ptr<T>(new T())); m_renderer.back()->Init(device, context, args...); }

	template<typename T, typename... TArgs>
	void AddShader(std::string name, ID3D11Device* device, ID3D11DeviceContext* context, TArgs... args)
	{
		m_shaders.emplace_back(std::shared_ptr<T>(new T()));
		m_shaders.back()->name = name;
		m_shaders.back()->InitShader(device, context, args...);

	}

	template<typename T>
	std::shared_ptr<T> GetShader(std::string name)
	{
		for (auto s : m_shaders)if (s->name == name)return std::static_pointer_cast<T>(s);
		return nullptr;
	}
	void Shutdown();
private:
	std::vector<std::unique_ptr<System>>	m_systems;
	std::vector<std::unique_ptr<Renderer>>	m_renderer;
	std::vector<std::shared_ptr<ShaderProgram>>	m_shaders;
	bool m_isInit{false};
};

