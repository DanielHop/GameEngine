#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "DirectXTex.lib")
#pragma comment(lib, "Xinput.lib")

//SHADERS
#include "Engine/Shaders/SimpleShader.h"

//DXApps
#include "Engine/Core/SimpleGameApp.h"

//RENDERERS
#include "Engine/Renderers/BatchRenderer2D.h"

//ENTITIES
#include "Engine/GameObjects/Sprite.h"
#include "Engine/GameObjects/Camera.h"
#include "Engine/GameObjects/EmptyGameObject.h"

//COMPONENTS
#include "Engine/Components/CameraComponent.h"
#include "Engine/Components/Component.h"
#include "Engine/Components/TransformComponent.h"
#include "Engine/Components/ScriptComponent.h"
#include "Engine/Components/SpriteComponent.h"

//SYSTEMS
#include "Engine/Systems/CameraSystem.h"
#include "Engine/Systems/InputSystem.h"