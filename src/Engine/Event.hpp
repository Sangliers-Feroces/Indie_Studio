#pragma once

#include <functional>
#include <optional>
#include "Bindings.hpp"

namespace Engine {
namespace Event {

template <typename SrcType, typename DstType, typename ExtractType>
class GenDispatcher
{
	using ListenerType = std::function<void (const DstType&)>;

public:
	using src_type = SrcType;
	using dst_type = DstType;
	using extract_type = ExtractType;

	GenDispatcher(void)
	{
	}
	virtual ~GenDispatcher(void)
	{
	}

	template <typename ...Args>
	void bind(Args &&...args)
	{
		m_listeners.bind(std::forward<Args>(args)...);
	}

protected:
	void newEvent(const SrcType &event)
	{
		auto got = extract(event);
		
		if (got)
			for (auto &l : m_listeners)
				l(convertExtracted(got));
	}

private:
	virtual extract_type extract(const src_type&) = 0;
	Bindings::Weak<ListenerType> m_listeners;

	virtual const DstType& convertExtracted(const ExtractType &value) = 0;
};

template <typename SrcType, typename DstType>
class Dispatcher : public GenDispatcher<SrcType, DstType, std::optional<std::reference_wrapper<const DstType>>>
{
public:
	Dispatcher(void)
	{
	}
	~Dispatcher(void)
	{
	}

private:
	const DstType& convertExtracted(const std::optional<std::reference_wrapper<const DstType>> &value)
	{
		return value->get();
	}
};

template <typename SrcType, typename DstType>
class CopyDispatcher : public GenDispatcher<SrcType, DstType, std::optional<DstType>>
{
public:
	CopyDispatcher(void)
	{
	}
	~CopyDispatcher(void)
	{
	}

private:
	const DstType& convertExtracted(const std::optional<DstType> &value)
	{
		return *value;
	}
};

}
}