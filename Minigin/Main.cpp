#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//Disabled vld because of error
//#include <vld.h>
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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Background object
	auto bgObj = std::make_shared<dae::GameObject>();
	auto bgRender = bgObj->AddComponent<dae::RenderComponent>(bgObj);
	bgRender->SetTexture("background.tga");

	auto bgTrans = bgObj->AddComponent<dae::TransformComponent>(bgObj);
	bgTrans->SetTranslation(glm::vec2{ 0.f, 0.f });	
	scene.Add(bgObj);

	//Logo object
	bgObj = std::make_shared<dae::GameObject>();
	bgRender = bgObj->AddComponent<dae::RenderComponent>(bgObj);
	bgRender->SetTexture("logo.tga");	

	bgTrans = bgObj->AddComponent<dae::TransformComponent>(bgObj);
	bgTrans->SetTranslation(glm::vec2{ 216, 180 });
	scene.Add(bgObj);

	//Text Object
	auto textObj = std::make_shared<dae::GameObject>();

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComponent = textObj->AddComponent<dae::TextComponent>(textObj);
	textComponent->SetText("Programming 4 Assignment");
	textComponent->SetFont(font);
	textComponent->SetColor(255, 255, 255, 255);	

	auto textRender = textObj->AddComponent<dae::RenderComponent>(textObj);

	auto textTrans = textObj->AddComponent<dae::TransformComponent>(textObj);
	textTrans->SetTranslation(glm::vec2{ 80, 20 });
	scene.Add(textObj);

	//Fps Object
	auto fpsObj = std::make_shared<dae::GameObject>();
	auto fpsTrans = fpsObj->AddComponent<dae::TransformComponent>(fpsObj);
	fpsTrans->SetTranslation(glm::vec2{ 10.f, 10.f });	
	
	auto fpsRender = fpsObj->AddComponent<dae::RenderComponent>(fpsObj);

	auto fpsText = fpsObj->AddComponent<dae::TextComponent>(fpsObj);
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	fpsText->SetFont(font);
	fpsText->SetColor(255, 255, 0, 255);

	auto fpsComponent = fpsObj->AddComponent<dae::FPSComponent>(fpsObj);	
	scene.Add(fpsObj);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}