#pragma once

#include "Core/EngineSettings.h"

#include "WindowManagement/Win32Window.h"
#include "GraphicsEngine/GraphicsFrameworks/DX11Framework.h"
#include "GraphicsEngine/GraphicsEngine.h"

#include "Application/Application.h"

#include <Math/Math.hpp>
#include <Math/Matrix.h>
#include <Math/Quaternion.h>
#include <Math/Transform.h>
#include <Math/Vector.h>
#include <Math/Vertex.h>
#include <Math/Matrix4x4.h>

#include <Models/ModelInstance.h>
#include <Models/Model.h>

#include <Core/EngineCore.h>

template <typename T>
using ref = std::shared_ptr<T>;
template <typename T>
using local = std::unique_ptr<T>;