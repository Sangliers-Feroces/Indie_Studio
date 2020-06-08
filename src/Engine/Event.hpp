#pragma once

#include <functional>
#include <optional>
#include "Bindings.hpp"

namespace Engine {
namespace Event {

template <typename src_type, typename extract_type>
class GenDispatcherPureExtract
{
public:
	GenDispatcherPureExtract(void)
	{
	}
	~GenDispatcherPureExtract(void)
	{
	}

protected:
	virtual extract_type extract(const src_type&) = 0;
};

template <typename src_type>
class GenDispatcherExtract
{
public:
	GenDispatcherExtract(void)
	{
	}
	~GenDispatcherExtract(void)
	{
	}

protected:
	virtual src_type extract(const src_type &src)
	{
		return src;
	}
};

template <typename SrcType, typename DstType, typename ExtractType>
class GenDispatcher : public std::conditional<std::is_convertible<SrcType, ExtractType>::value, GenDispatcherExtract<SrcType>, GenDispatcherPureExtract<SrcType, ExtractType>>::type
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
		auto got = this->extract(event);
		
		if (got)
			for (auto &l : m_listeners)
				l(convertExtracted(got));
	}

private:
	Bindings::Strong<ListenerType> m_listeners;

	virtual const DstType& convertExtracted(const ExtractType &value) = 0;
};

template <typename SrcType, typename DstType = SrcType>
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
	const DstType& convertExtracted(const std::optional<std::reference_wrapper<const DstType>> &value) override
	{
		return value->get();
	}
};

template <typename SrcType, typename DstType = SrcType>
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
	const DstType& convertExtracted(const std::optional<DstType> &value) override
	{
		return *value;
	}
};

template <typename ...Payload>
class Generator
{
	using ListenerType = std::function<void (const Payload &...payload)>;

public:
	Generator(void)
	{
	}
	~Generator(void)
	{
	}

	template <typename ...Args>
	void bind(Args &&...args)
	{
		m_listeners.bind(std::forward<Args>(args)...);
	}

	template <typename ...Args>
	void emit(Args &&...payload)
	{
		for (auto &l : m_listeners)
			l(std::forward<Args>(payload)...);
	}

private:
	Bindings::Strong<ListenerType> m_listeners;
};

}
}