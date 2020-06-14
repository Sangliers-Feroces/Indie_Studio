#pragma once

#include <iostream>
#include "Engine/AnimatedMesh.hpp"

namespace Bomberman {

class Model : public en::AnimatedMesh
{
public:
	Model(const std::string &model_path, const std::string &texture_path, bool light = true);
	void write(std::ostream &o);
	Model(std::istream &i, const std::string &model_path);
	Model(std::istream &i);
	~Model(void);

private:
	std::string m_model_path;
	std::string m_texture_path;
};

}