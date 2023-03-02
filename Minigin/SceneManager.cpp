#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Init()
{
	for (auto& scene : m_scenes)
	{
		scene->Init();
	}
}

void dae::SceneManager::BeginUpdate()
{
	for(auto& scene : m_scenes)
	{
		scene->BeginUpdate();
	}
}

void dae::SceneManager::EndUpdate()
{
	for (auto& scene : m_scenes)
	{
		scene->EndUpdate();
	}
}

void dae::SceneManager::Render() const
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
