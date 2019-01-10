#include "TimerFacade.h"
#include <SDL.h>

namespace utils
{
	TimerFacade::TimerFacade()
	{
		reset();
	}

	void TimerFacade::reset()
	{
		start_ticks_ = SDL_GetTicks();
		elapsed_ticks_ = 0;
		delta_time_ = 0.0f;
	}

	void TimerFacade::update()
	{
		elapsed_ticks_ = SDL_GetTicks() - start_ticks_;
		delta_time_ = elapsed_ticks_ * 0.001f;
	}
}
