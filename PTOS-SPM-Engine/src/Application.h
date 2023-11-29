#pragma once

#include "Core.h"

namespace PTOS {
	class PTOS_API Application
	{
	public:
		Application();
		virtual ~Application();

	};

	Application* createApplication(void);
}
