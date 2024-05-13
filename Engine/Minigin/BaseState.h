#pragma once
#include <memory>
namespace dae 
{
	class BaseState
	{
	public:
		virtual ~BaseState() = default;

		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;

		virtual void Update() = 0;

	private:
		BaseState() = default;
	};
}
