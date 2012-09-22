#include "stdafx.h"

#include "Registry.h"

namespace DesignPatterns
{
	namespace
	{
		std::list<std::string>
		split (const std::string& str, char sep)
		{
			std::list<std::string> ret;
			size_t start = 0;
			size_t end = 0;
			size_t len = str.length();

			for (end = 0; end < len; ++end)
			{
				if (str[end] == sep)
				{
					ret.push_back(str.substr(start, end - start));
					start = end + 1;
				}
			}
			ret.push_back(str.substr(start, end - start));

			return ret;
		}

		void
		print_indent (std::ostream& os, size_t indent)
		{
			for (size_t i = 0; i < indent; ++i)
			{
				os << '\t';
			}
		}
	}

	RegistryManager&
	RegistryManager::getInstance ()
	{
		static RegistryManager manager;
		return manager;
	}

	void 
	RegistryManager::addElement (const std::string& name, RegistryElement* element)
	{
		std::list<std::string> spath = split(name, DESIGNPATTERNS_REGISTRY_SEPARATOR);
		RegistryNode* node = getRoot();

		std::list<std::string>::iterator endList = spath.end();
		--endList;
		for (std::list<std::string>::iterator it = spath.begin();
			 it != endList;
			 ++it)
		{
			if (node->getNodes().find(*it) == node->getNodes().end())
			{
				node->getNodes()[*it] = new RegistryNode(*it);
			}
			std::map<std::string, RegistryBase*>::iterator tmp = node->getNodes().find(*it);
			node = static_cast<RegistryNode*>(tmp->second);
		}
		if (node->getNodes().find(*endList) != node->getNodes().end())
		{
			delete node->getNodes()[*endList];
		}
		node->getNodes()[*endList] = new RegistryLeaf(*endList, element);
	}
	
	void
	RegistryManager::removeElement (const std::string& name)
	{
		std::list<std::string> spath = split(name, DESIGNPATTERNS_REGISTRY_SEPARATOR);
		RegistryNode* node = getRoot();
	}

	RegistryElement*
	RegistryManager::getElement(const std::string& name) const
	{
		RegistryElement* ret = 0;
		std::list<std::string> spath = split(name, DESIGNPATTERNS_REGISTRY_SEPARATOR);
		const RegistryNode* node = getRoot();

		std::list<std::string>::iterator endList = spath.end();
		--endList;
		for (std::list<std::string>::iterator it = spath.begin();
			 it != endList;
			 ++it)
		{
			std::map<std::string, RegistryBase*>::const_iterator tmp = node->getNodes().find(*it);
			if (tmp == node->getNodes().end())
			{
				node = 0;
				break;
			}
			node = static_cast<RegistryNode*>(tmp->second);
		}
		if (0 != node)
		{
			std::map<std::string, RegistryBase*>::const_iterator tmp = node->getNodes().find(*endList);
			if (tmp != node->getNodes().end())
			{
				ret = tmp->second->getElement();
			}
		}

		return ret;
	}

	void
	RegistryManager::Dump (std::ostream& os) const
	{
		std::map<std::string, RegistryBase*>::const_iterator it;

		for (it = getRoot()->getNodes().begin();
			 it != getRoot()->getNodes().end();
			 ++it)
		{
			it->second->Dump(os, 0);
		}
	}

	RegistryManager::RegistryManager ()
		: m_tree("")//m_tree("Root")
	{
	}

	RegistryNode*
	RegistryManager::getRoot ()
	{
		return &m_tree;
	}

	const RegistryNode*
	RegistryManager::getRoot () const
	{
		return &m_tree;
	}

	RegistryBase::RegistryBase (const std::string& name)
		: m_name(name)
	{
	}

	std::map<std::string, RegistryBase*>& 
	RegistryBase::getNodes ()
	{
		throw std::runtime_error("NO SUB-NODES");
	}

	const std::map<std::string, RegistryBase*>& 
	RegistryBase::getNodes () const
	{
		throw std::runtime_error("NO SUB-NODES");
	}

	RegistryElement*
	RegistryBase::getElement ()
	{
		throw std::runtime_error("NO ELEMENT");
	}

	RegistryNode::RegistryNode (const std::string& name)
		: RegistryBase(name)
		, m_tree()
	{
	}

	RegistryNode::~RegistryNode ()
	{
		for (std::map<std::string, RegistryBase*>::iterator it = m_tree.begin();
			 it != m_tree.end();
			 ++it)
		{
			delete it->second;
		}
	}

	std::map<std::string, RegistryBase*>&
	RegistryNode::getNodes ()
	{
		return m_tree;
	}
	
	const std::map<std::string, RegistryBase*>&
	RegistryNode::getNodes () const
	{
		return m_tree;
	}

	void
	RegistryNode::Dump (std::ostream& os, size_t indent) const
	{
		std::map<std::string, RegistryBase*>::const_iterator it;

		print_indent(os, indent);

		os << '[' << m_name << ']' << std::endl;

		for (it = getNodes().begin(); it != getNodes().end(); ++it)
		{
			it->second->Dump(os, indent + 1);
		}
	}

	RegistryLeaf::RegistryLeaf (const std::string& name, RegistryElement* element)
		: RegistryBase(name)
		, m_element(element)
	{
	}

	RegistryLeaf::~RegistryLeaf ()
	{
	}

	RegistryElement*
	RegistryLeaf::getElement ()
	{
		return m_element;
	}

	void
	RegistryLeaf::Dump (std::ostream& os, size_t indent) const
	{
		print_indent(os, indent);

		os << m_name << " = " << m_element << std::endl;
	}
}