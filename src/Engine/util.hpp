#pragma once

#include <stdexcept>

namespace Engine {
namespace util {

template <class IrrRefCounted>
class irr_shared
{
public:
	irr_shared(IrrRefCounted &obj) :
		m_obj(obj)
	{
	}
	irr_shared(IrrRefCounted *obj) :
		m_obj(*obj)
	{
		if (obj == nullptr)
			throw std::runtime_error("irr_shared got nullptr as input");
	}
	~irr_shared(void)
	{
		m_obj.drop();
	}

	IrrRefCounted& operator*(void)
	{
		return m_obj;
	}

	const IrrRefCounted& operator*(void) const
	{
		return m_obj;
	}

	IrrRefCounted& operator->(void)
	{
		return m_obj;
	}

	const IrrRefCounted& operator->(void) const
	{
		return m_obj;
	}

private:
	IrrRefCounted &m_obj;
};

}
}