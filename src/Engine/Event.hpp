#pragma once

#include <functional>
#include <optional>
#include "Bindings.hpp"

namespace Engine {
namespace Event {

template <typename SrcType, typename DstType>
class Dispatcher
{
	using ListenerType = std::function<void (const DstType&)>;

public:
	Dispatcher(void)
	{
	}
	virtual ~Dispatcher(void)
	{
	}

	template <typename ...Args>
	void bind(Args &&...args)
	{
		m_listeners.bind(std::forward<Args>(args)...);
	}

	void newEvent(const SrcType &event)
	{
		auto got = extract(event);
		
		if (got)
			for (auto &l : m_listeners)
				l(got->get());
	}

private:
	virtual std::optional<const std::reference_wrapper<DstType>> extract(const SrcType&) = 0;
	Bindings::Weak<ListenerType> m_listeners;
};

template <typename SrcType, typename DstType>
class CopyDispatcher
{
	using ListenerType = std::function<void (const DstType&)>;

public:
	CopyDispatcher(void)
	{
	}
	virtual ~CopyDispatcher(void)
	{
	}

	template <typename ...Args>
	void bind(Args &&...args)
	{
		m_listeners.bind(std::forward<Args>(args)...);
	}

	void newEvent(const SrcType &event)
	{
		auto got = extract(event);
		
		if (got)
			for (auto &l : m_listeners)
				l(*got);
	}

private:
	virtual std::optional<DstType> extract(const SrcType&) = 0;
	Bindings::Weak<ListenerType> m_listeners;
};

}
}