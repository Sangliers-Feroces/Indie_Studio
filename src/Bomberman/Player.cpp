#include "Player.hpp"

#include <iostream>

namespace Bomberman {

int an_int = 3;

class IntDispatcher : public en::Event::Dispatcher<int, int>
{
public:
	IntDispatcher(void) = default;
	~IntDispatcher(void) = default;

private:
	std::optional<const std::reference_wrapper<int>> extract(const int &in) override
	{
		return an_int;
	}
};

Player::Player(void)
{
	setPos(irr::core::vector3df(0, 0, 1000));
	for (size_t i = 0; i < 10; i++)
		for (size_t j = 0; j < 10; j++)
			for (size_t k = 0; k < 10; k++)
				add<Sub>(i * 1000, j * 1000, k * 1000);

	IntDispatcher disp;

	bind(disp, [](const int &got){
		std::cout << "got: " << got << std::endl;
	});

	disp.newEvent(5);
	disp.newEvent(7);
}

Player::~Player(void)
{
}

}