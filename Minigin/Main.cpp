#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)

#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "RotatorComponent.h"
#include "TrashTheCacheComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Background object
	auto bgObj = std::make_shared<dae::GameObject>();
	auto bgRender = bgObj->AddComponent<dae::RenderComponent>();
	bgRender->SetTexture("background.tga");

	auto bgTrans = bgObj->AddComponent<dae::TransformComponent>();
	bgTrans->SetLocalPosition(glm::vec3{ 0.f, 0.f, 0.f });	
	scene.Add(bgObj);

	//Logo object
	bgObj = std::make_shared<dae::GameObject>();
	bgRender = bgObj->AddComponent<dae::RenderComponent>();
	bgRender->SetTexture("logo.tga");	

	bgTrans = bgObj->AddComponent<dae::TransformComponent>();
	bgTrans->SetLocalPosition(glm::vec2{ 216.f, 180.f });
	scene.Add(bgObj);

	//Text Object
	auto textObj = std::make_shared<dae::GameObject>();

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComponent = textObj->AddComponent<dae::TextComponent>();
	textComponent->SetText("Programming 4 Assignment");
	textComponent->SetFont(font);
	textComponent->SetColor(255, 255, 255, 255);	

	auto textRender = textObj->AddComponent<dae::RenderComponent>();

	auto textTrans = textObj->AddComponent<dae::TransformComponent>();
	textTrans->SetLocalPosition(glm::vec2{ 80.f, 20.f});
	scene.Add(textObj);

	//Fps Object
	auto fpsObj = std::make_shared<dae::GameObject>();
	auto fpsTrans = fpsObj->AddComponent<dae::TransformComponent>();
	fpsTrans->SetLocalPosition(glm::vec2{ 10.f, 10.f });	
	
	auto fpsRender = fpsObj->AddComponent<dae::RenderComponent>();

	auto fpsText = fpsObj->AddComponent<dae::TextComponent>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	fpsText->SetFont(font);
	fpsText->SetColor(255, 255, 0, 255);

	auto fpsComponent = fpsObj->AddComponent<dae::FPSComponent>();	
	scene.Add(fpsObj);

	//Pacman root
	auto pacmanRootObj = std::make_shared<dae::GameObject>();
	auto rootTrans = pacmanRootObj->AddComponent<dae::TransformComponent>();
	rootTrans->SetLocalPosition(glm::vec2{ 280.f, 280.f });
	scene.Add(pacmanRootObj);

	//Pacman
	auto pacmanObj = std::make_shared<dae::GameObject>();
	auto pacmanTrans = pacmanObj->AddComponent<dae::TransformComponent>();
	pacmanTrans->SetLocalPosition(glm::vec2{ 30.f, 0.f });

	auto pacmanRender = pacmanObj->AddComponent<dae::RenderComponent>();
	pacmanRender->SetTexture("pacman.png");

	auto pacmanRot = pacmanObj->AddComponent<dae::RotatorComponent>();
	pacmanRot->SetRotationSpeed(90.f);
	pacmanObj->SetParent(pacmanRootObj, false);
	scene.Add(pacmanObj);

	//Ghostman
	auto ghostObj = std::make_shared<dae::GameObject>();
	auto ghostTrans = ghostObj->AddComponent<dae::TransformComponent>();
	ghostTrans->SetLocalPosition(glm::vec2{ 30.f, 0.f });

	auto ghostRender = ghostObj->AddComponent<dae::RenderComponent>();
	ghostRender->SetTexture("ghost.png");

	ghostObj->SetParent(pacmanObj, false);

	auto ghostRot = ghostObj->AddComponent<dae::RotatorComponent>();
	ghostRot->SetRotationSpeed(-120.f);
	scene.Add(ghostObj);

	auto guiObj = std::make_shared<dae::GameObject>();
	guiObj->AddComponent<dae::TrashTheCacheComponent>();
	scene.Add(guiObj);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}