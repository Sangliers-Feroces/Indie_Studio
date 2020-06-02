/* ==================== NOTICE ==================== */
// THE CODE IN THIS FILE "Bindings.hpp" IS GAX SOFTWARE PROPERTY.
// IT IS USED EXCLUSIVELY IN THIS PROJECT AS "FAIR-USE" FOR EDUCATIONAL PURPOSES.
// GAX SOFTWARE GRACIOUSLY PROVIDED THIS INTELLECTUAL WORK AS IT, WITHOUT ANY GUARRANTY OF ANY KIND.
// YOU MAY NOT USE OR CLAIM THIS CODE FOR YOURSELF OR YOUR COMPANY WITHOUT THE AGREEMENT OF GAX SOFTWARE.
// BY USING THIS CODE ANYWAYS, YOU HAVE READ THIS NOTICE AND ARE AWARE OF LEGAL CONSEQUENCES.
// contact@gaxsoftware.com

#pragma once

#include "util.hpp"

namespace Engine {
namespace Bindings {

class Dependency;

class Source
{
public:
	template <typename T>
	class WeakElement;

	Source(void)
	{
	}
	virtual ~Source(void)
	{
	}

private:
	friend Dependency;
	virtual void depDestroyed(Dependency &dep) = 0;
};

template <typename T>
class Weak;

class Dependency
{
public:
	class Point;

	class Socket
	{
	public:
		Socket(void)
		{
		}
		~Socket(void)
		{
			for (auto &d : m_deps)
				d.destroyBound();
		}
	
	protected:
		template <typename Bindable, typename ...Args>
		void bind(Bindable &&bindable, Args &&...args)
		{
			bindable.bind(*this, std::forward<Args>(args)...);
		}

	private:
		friend Point;
		template <typename T>
		friend class Weak;
		util::unique_set<Dependency> m_deps;

		Dependency& add(Source &source)
		{
			return m_deps.emplace(source);
		}

		void destroy(Dependency &dep)
		{
			auto got = m_deps.find(dep);

			if (got == m_deps.end())
				throw std::runtime_error("Can't destroy dependency");
			m_deps.erase(got);
		}
	};

	class Point
	{
	public:
		Point(Socket &socket, Dependency &dependency) :
			m_socket(socket),
			m_dependency(&dependency)
		{
		}
		~Point(void)
		{
		}

		Dependency& getDependency(void)
		{
			if (m_dependency == nullptr)
				throw std::runtime_error("Empty dependency, can't resolve");
			return *m_dependency;
		}

		void destroyBound(void)
		{
			if (m_dependency)
				m_socket.destroy(*m_dependency);
		}

		void clear(void)
		{
			m_dependency = nullptr;
		}

	private:
		friend Socket;
		Socket &m_socket;
		Dependency *m_dependency;
	};

public:
	Dependency(Source &source) :
		m_source(source)
	{
	}
	~Dependency(void)
	{
	}

	void destroyBound(void)
	{
		m_source.depDestroyed(*this);
	}

private:
	Source &m_source;
};

template <typename Element>
class StorageBase
{
	using UniqueSet = util::unique_set<Element>;

public:
	StorageBase(void)
	{
	}
	~StorageBase(void)
	{
	}

	class iterator : public UniqueSet::iterator
	{
		using unique_set_iterator = typename UniqueSet::iterator;

	public:
		using difference_type = std::ptrdiff_t;
		using value_type = typename Element::value_type;
		using pointer = value_type*;
		using reference = value_type&;
		using iterator_category = std::bidirectional_iterator_tag;

		iterator(const unique_set_iterator &it) :
			UniqueSet::iterator(it)
		{
		}
		~iterator(void)
		{
		}

		reference operator*(void) const
		{
			return UniqueSet::iterator::operator*();
		}
	};

	iterator begin(void)
	{
		return m_elements.begin();
	}

	iterator end(void)
	{
		return m_elements.end();
	}

protected:
	UniqueSet m_elements;
};

template <typename Element>
class StorageBasic : public StorageBase<Element>
{
public:
	StorageBasic(void)
	{
	}
	~StorageBasic(void)
	{
	}

protected:
	friend Element;

	void destroyElement(Element &elem)
	{
		auto got = this->m_elements.find(elem);

		if (got == this->m_elements.end())
			throw std::runtime_error("Can't destroy element");
		this->m_elements.erase(got);
	}
};

template <typename Element>
class Storage : public StorageBasic<Element>
{
	using InheritedStorage = StorageBasic<Element>;

public:
	template <typename ...Args>
	Storage(Args &&...args) :
		InheritedStorage(std::forward<Args>(args)...)
	{
	}
	~Storage(void)
	{
	}
};

template <typename T>
class Weak : public Storage<Source::WeakElement<T>>
{
public:
	template <typename ...Args>
	Weak(Args &&...args) :
		Storage<Source::WeakElement<T>>(std::forward<Args>(args)...)
	{
	}
	~Weak(void)
	{
		if (this->m_elements.size() > 0)
			util::fatal_throw([](){
				throw std::runtime_error("Elements still in weak socket");
			});
	}

	template <typename ...Args>
	void bind(Dependency::Socket &socket, Args &&...args)
	{
		socket.add(this->m_elements.emplace(*this, std::forward<Args>(args)...));
	}
};

template <typename T>
class Source::WeakElement : public Source
{
public:
	using value_type = T;

	template <typename ...Args>
	WeakElement(Weak<T> &socket, Args &&...args) :
		m_socket(socket),
		m_obj(std::forward<Args>(args)...)
	{
	}
	~WeakElement(void)
	{
	}

	operator T&(void)
	{
		return m_obj;
	}

private:
	Weak<T> &m_socket;
	T m_obj;

	void depDestroyed(Dependency&) override
	{
		m_socket.destroyElement(*this);
	}
};

}
}