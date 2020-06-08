#pragma once

#include "Engine/AnimatedMesh.hpp"

namespace Bomberman {

class Model : public en::AnimatedMesh
{
public:
	Model(const std::string &model_path, const std::string &texture_path);
	~Model(void);
};

}