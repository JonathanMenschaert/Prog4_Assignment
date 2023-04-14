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
#include "DearImGuiComponent.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "glm/glm.hpp"
#include "RectCollisionComponent.h"
#include "Gamepad.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& inputManager = dae::InputManager::GetInstance();
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
	auto pacmanCol = pacmanObj->AddComponent<dae::RectCollisionComponent>();
	pacmanCol->SetCollisionType(dae::RectCollisionComponent::CollisionType::DynamicCollision);
	pacmanCol->SetExtend(glm::vec2{ 10, 10 });
	pacmanCol->SetLayers(std::vector<std::string>{"enemy", "pickup", "wall1"});
	auto pacmanTrans = pacmanObj->AddComponent<dae::TransformComponent>();
	pacmanTrans->SetLocalPosition(glm::vec2{ 250.f, 300.f });

	auto pacmanRender = pacmanObj->AddComponent<dae::RenderComponent>();
	pacmanRender->SetTexture("pacman.png");
	scene.Add(pacmanObj);

	//Bind keys
	const float speed{ 100.f };
	inputManager.BindKeyboardCommand(dae::InputManager::InteractionType::Hold, SDLK_w, std::make_unique<dae::MoveCommand>(pacmanObj.get(), speed, glm::vec2{ 0.f, 1.f }));
	inputManager.BindKeyboardCommand(dae::InputManager::InteractionType::Hold, SDLK_a, std::make_unique<dae::MoveCommand>(pacmanObj.get(), speed, glm::vec2{ -1.f, 0.f }));
	inputManager.BindKeyboardCommand(dae::InputManager::InteractionType::Hold, SDLK_s, std::make_unique<dae::MoveCommand>(pacmanObj.get(), speed, glm::vec2{ 0.f, -1.f }));
	inputManager.BindKeyboardCommand(dae::InputManager::InteractionType::Hold, SDLK_d, std::make_unique<dae::MoveCommand>(pacmanObj.get(), speed, glm::vec2{ 1.f, 0.f }));
	
	//Ghost
	auto ghostObj = std::make_shared<dae::GameObject>();
	auto ghostCol = ghostObj->AddComponent<dae::RectCollisionComponent>();
	ghostCol->SetCollisionType(dae::RectCollisionComponent::CollisionType::Trigger);
	ghostCol->SetExtend(glm::vec2{ 10, 10 });
	ghostCol->SetLayers(std::vector<std::string>{"enemy", "wall2"});
	auto ghostTrans = ghostObj->AddComponent<dae::TransformComponent>();
	ghostTrans->SetLocalPosition(glm::vec2{ 350.f, 300.f });

	auto ghostRender = ghostObj->AddComponent<dae::RenderComponent>();
	ghostRender->SetTexture("pacman.png");
	scene.Add(ghostObj);

	//Bind Controller keys
	inputManager.BindDigitalCommand(0, dae::InputManager::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadUp, std::make_unique<dae::MoveCommand>(ghostObj.get(), speed * 2.f, glm::vec2{ 0.f, 1.f }));
	inputManager.BindDigitalCommand(0, dae::InputManager::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadDown, std::make_unique<dae::MoveCommand>(ghostObj.get(), speed * 2.f, glm::vec2{ 0.f, -1.f }));
	inputManager.BindDigitalCommand(0, dae::InputManager::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadLeft, std::make_unique<dae::MoveCommand>(ghostObj.get(), speed * 2.f, glm::vec2{ -1.f, 0.f }));
	inputManager.BindDigitalCommand(0, dae::InputManager::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadRight, std::make_unique<dae::MoveCommand>(ghostObj.get(), speed * 2.f, glm::vec2{ 1.f, 0.f }));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}