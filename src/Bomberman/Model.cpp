#include "Model.hpp"

namespace Bomberman {

Model::Model(const std::string &model_path, const std::string &texture_path) :
	AnimatedMesh(model_path)
{
	setMaterialTexture(0, world.session.driver.getTexture(texture_path.c_str()));
	setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

Model::~Model(void)
{
}

}