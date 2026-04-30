#pragma once
#include "Entity.h"


namespace Parasite
{
	class CScriptableEntity
	{
	public:
		template<typename T>
		T& GetComponent();

	private:
		CEntity Entity;
		friend class CScene;
	};


	template<typename T>
	T& CScriptableEntity::GetComponent()
	{
		return Entity.GetComponent<T>();
	}
}