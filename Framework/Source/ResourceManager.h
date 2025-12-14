#pragma once

namespace fw
{
	class Mesh;
	class ShaderProgram;

	class Resource
	{
	public:
		virtual ~Resource() {}
	};

	class ResourceManager
	{
	public:
		~ResourceManager()
		{
			for (const auto& listPair : m_resources)
			{
				for (const auto& pair : listPair.second)
				{
					delete pair.second;
				}
			}
		}

		template <class Type>
		void add(std::string name, Type* pResource)
		{
			assert(m_resources[Type::getResourceTypeID()].count(name) == 0);
			m_resources[Type::getResourceTypeID()][name] = pResource;
		}

		template <class Type>
		Type* get(std::string name)
		{
			assert(m_resources[Type::getResourceTypeID()].count(name) == 1);
			return static_cast<Type*>(m_resources[Type::getResourceTypeID()][name]);
		}

	protected:
		using ResourceList = std::unordered_map<std::string, Resource*>;
		std::unordered_map<std::string, ResourceList> m_resources;
	};
}


//  m_resources["Mesh"]["Grass"] = new Mesh;
//  m_resources["Mesh"]["Mud"] = new Mesh;
//  m_resources["Mesh"]["Rock"] = new Mesh;
//  m_resources["Texture"]["Grass_Green"] = new Texture;
//  m_resources["Texture"]["Grass_Yellow1"] = new Texture;
//  m_resources["Texture"]["Grass_Yellow2"] = new Texture;
//  m_resources["Texture"]["Grass_Yellow3"] = new Texture;
//  m_resources["Texture"]["Grass"] = new Texture;
//  m_resources["Texture"]["Mud"] = new Texture;
//  m_resources["Texture"]["Rock"] = new Texture;