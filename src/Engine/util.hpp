#pragma once

#include <stdexcept>
#include <memory>
#include <map>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace Engine {
namespace util {

template <typename T>
T& ptr_to_ref(T *ptr)
{
	if (ptr == nullptr)
		throw std::runtime_error("ptr_to_ref got nullptr as input");
	return *ptr;
}

template <typename T>
const T& ptr_to_ref(const T *ptr)
{
	if (ptr == nullptr)
		throw std::runtime_error("ptr_to_ref got nullptr as input");
	return *ptr;
}

template <class IrrRefCounted, bool isRemove = false>
class irr_shared
{
public:
	irr_shared(IrrRefCounted &obj) :
		m_obj(obj)
	{
	}
	irr_shared(IrrRefCounted *obj) :
		m_obj(ptr_to_ref(obj))
	{
	}
	~irr_shared(void)
	{
		if constexpr (isRemove)
			m_obj.remove();
		else
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

	IrrRefCounted* operator->(void)
	{
		return &m_obj;
	}

	const IrrRefCounted* operator->(void) const
	{
		return &m_obj;
	}

	IrrRefCounted& get(void)
	{
		return m_obj;
	}

	const IrrRefCounted& get(void) const
	{
		return m_obj;
	}

	operator IrrRefCounted&(void)
	{
		return m_obj;
	}

	operator const IrrRefCounted&(void) const
	{
		return m_obj;
	}

private:
	IrrRefCounted &m_obj;
};

template<typename T>
class unique_set
{
	using Map = std::map<const T*, std::unique_ptr<T>>;

public:
	unique_set(void)
	{
	}
	~unique_set(void)
	{
	}

	class const_iterator : public Map::const_iterator
	{
		using map_const_iterator = typename Map::const_iterator;

	public:
		using difference_type = std::ptrdiff_t;
		using value_type = const T;
		using pointer = const T*;
		using reference = const T&;
		using iterator_category = std::bidirectional_iterator_tag;

		const_iterator(const map_const_iterator &it) :
			Map::const_iterator(it)
		{
		}
		~const_iterator(void)
		{
		}

		reference operator*(void) const
		{
			return *(*this)->second;
		}
	};

	const_iterator begin(void) const
	{
		return m_map.cbegin();
	}

	const_iterator end(void) const
	{
		return m_map.cend();
	}

	const_iterator cbegin(void) const
	{
		return begin();
	}

	const_iterator cend(void) const
	{
		return end();
	}

	class iterator : public Map::iterator
	{
		using map_iterator = typename Map::iterator;

	public:
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::bidirectional_iterator_tag;

		iterator(const map_iterator &it) :
			Map::iterator(it)
		{
		}
		~iterator(void)
		{
		}

		reference operator*(void) const
		{
			return *(*this)->second;
		}
	};

	iterator begin(void)
	{
		return m_map.begin();
	}

	iterator end(void)
	{
		return m_map.end();
	}

	size_t size(void) const
	{
		return m_map.size();
	}

	T& insert(std::unique_ptr<T> &&to_insert)
	{
		auto ptr = to_insert.release();

		auto [it, success] = m_map.emplace(ptr, ptr);
		if (!success)
			throw std::runtime_error("Can't insert element in set");
		return *ptr;
	}

	template <typename ...Args>
	T& emplace(Args &&...args)
	{
		auto to_insert = new T(std::forward<Args>(args)...);

		auto [it, success] = m_map.emplace(to_insert, to_insert);
		if (!success)
			throw std::runtime_error("Can't emplace element in set");
		return *to_insert;
	}

	template <typename TDerived, typename ...Args>
	TDerived& emplace(Args &&...args)
	{
		auto to_insert = new TDerived(std::forward<Args>(args)...);

		auto [it, success] = m_map.emplace(to_insert, to_insert);
		if (!success)
			throw std::runtime_error("Can't emplace element in set");
		return *to_insert;
	}

	const_iterator find(const T &elem) const
	{
		return const_iterator(m_map.find(&elem));
	}

	iterator find(const T &elem)
	{
		return iterator(m_map.find(&elem));
	}

	void erase(const iterator &it)
	{
		m_map.erase(it);
	}

	void clear(void)
	{
		m_map.clear();
	}

private:
	Map m_map;
};

template <typename CallbackType>
void fatal_throw(const CallbackType &callback)
{
	try {
		callback();
	} catch (const std::exception &e) {
		std::terminate();
	}
}

template <typename Key, typename Value>
class cache
{
public:
	cache(const std::function<void (const Key &, Value&)> &constructor) :
		m_constructor(constructor)
	{
	}

	~cache(void)
	{
	}

	Value& resolve(const Key& key)
	{
		auto got = m_cache.find(key);

		if (got != m_cache.end())
			return got->second;
		else {
			Value value;
			m_constructor(key, value);
			return (*m_cache.emplace(key, value).first).second;
		}
	}

private:
	const std::function<void (const Key &, Value&)> m_constructor;
	std::map<Key, Value> m_cache;
};

template <typename T, typename Ostream>
void write(Ostream &&o, T &&t)
{
	o.write(reinterpret_cast<char*>(&t), sizeof(T));
}

template <typename T, typename Istream>
T read(Istream &&i)
{
	T res;

	i.read(reinterpret_cast<char*>(&res), sizeof(T));
	return res;
}

inline std::string read_string(std::istream &i)
{
	auto size = read<size_t>(i);

	std::string res;
	for (size_t it = 0; it < size; it++) {
		auto cur = read<char>(i);
		res.push_back(cur);
	}
	return res;
}

inline void write_string(std::ostream &o, const std::string &str)
{
	write(o, str.size());
	o.write(str.data(), str.size());
}

using type_id_t = size_t;

template<typename T>
type_id_t type_id(void)
{
	return typeid(T).hash_code();
}

inline std::string strip_string(const std::string &str)
{
	std::string res;

	for (auto &c : str)
		if (!(c == '\n' || c == ' ' || c == '\t' || c == '\r'))
			res.push_back(c);
	return res;
}

template <typename T>
T check_value_parsed(const std::string &str, size_t pos, T value)
{
	if (pos != str.size())
		throw std::runtime_error("Can't convert such number");
	else
		return value;
}

template <typename T>
T conv_safe(T (*conv)(const std::string&, size_t*), const std::string &str)
{
	size_t pos = 0;
	T res = conv(str, &pos);

	return check_value_parsed(str, pos, res);
}

template <typename T>
T conv_safe(T (*conv)(const std::string&, size_t*, int), const std::string &str)
{
	size_t pos = 0;
	T res = conv(str, &pos, 10);

	return check_value_parsed(str, pos, res);
}

}
}