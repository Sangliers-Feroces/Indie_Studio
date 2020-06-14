#include "Model.hpp"

namespace Bomberman {

Model::Model(const std::string &model_path, const std::string &texture_path) :
	AnimatedMesh(model_path),
	m_model_path(model_path),
	m_texture_path(texture_path)
{
	setMaterialTexture(0, world.session.driver.getTexture(texture_path.c_str()));
	setMaterialFlag(irr::video::EMF_LIGHTING, true);
	addShadowVolume();
}

void Model::write(std::ostream &o)
{
	en::util::write_string(o, m_model_path);
	en::util::write_string(o, m_texture_path);
}

Model::Model(std::istream &i, const std::string &model_path) :
	Model(model_path, en::util::read_string(i))
{
}

Model::Model(std::istream &i) :
	Model(i, en::util::read_string(i))
{
}

Model::~Model(void)
{
}

}