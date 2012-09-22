#pragma once

#include <map>
#include <ostream>
#include <string>

#include "DesignPatternsExport.h"

#if !defined(DESIGNPATTERNS_REGISTRY_SEPARATOR)
# define DESIGNPATTERNS_REGISTRY_SEPARATOR ':'
#endif

namespace DesignPatterns
{
	// Forward declarations
	class RegistryNode;

	class DESIGNPATTERNS_API RegistryElement
	{
	public:
		virtual ~RegistryElement () {}
		inline virtual void Dump (std::ostream& os) { os << this; }
	protected:
	private:
	};

	class DESIGNPATTERNS_API RegistryBase
	{
	public:
		RegistryBase (const std::string& name);
		virtual ~RegistryBase () {}
		virtual std::map<std::string, RegistryBase*>& getNodes ();
		virtual const std::map<std::string, RegistryBase*>& getNodes () const;
		virtual RegistryElement* getElement ();
		virtual void Dump (std::ostream& os, size_t indent) const = 0;
	protected:
		std::string m_name;
	private:
	};

	class DESIGNPATTERNS_API RegistryNode
		: public RegistryBase
	{
	public:
		RegistryNode (const std::string& name);
		virtual ~RegistryNode ();
		virtual std::map<std::string, RegistryBase*>& getNodes ();
		virtual const std::map<std::string, RegistryBase*>& getNodes () const;
		virtual void Dump (std::ostream& os, size_t indent) const;
	protected:
	private:
		std::map<std::string, RegistryBase*> m_tree;
	};

	class DESIGNPATTERNS_API RegistryManager
	{
	public:
		static RegistryManager& getInstance ();
		void addElement (const std::string& name, RegistryElement* element);
		void removeElement (const std::string& name);
		RegistryElement* getElement(const std::string& name) const;
		void Dump (std::ostream& os) const;
	protected:
	private:
		RegistryManager ();
		RegistryManager (const RegistryManager&);
		RegistryNode* getRoot ();
		const RegistryNode* getRoot () const;

		RegistryNode m_tree;
	};

	class DESIGNPATTERNS_API RegistryLeaf
		: public RegistryBase
	{
	public:
		RegistryLeaf (const std::string& name, RegistryElement* element);
		virtual ~RegistryLeaf ();
		virtual RegistryElement* getElement ();
		virtual void Dump (std::ostream& os, size_t indent) const;
	protected:
	private:
		RegistryElement* m_element;
	};
}