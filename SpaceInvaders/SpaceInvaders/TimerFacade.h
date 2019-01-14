#ifndef GAME_UTILS_TIMER_FACADE_H
#define GAME_UTILS_TIMER_FACADE_H

namespace utils
{
	class TimerFacade
	{
	public:
		TimerFacade();
		void reset();
		void update();
		float delta_time() const noexcept { return delta_time_; }

	private:
		unsigned int start_ticks_{};
		unsigned int elapsed_ticks_{};
		float delta_time_{};
	};
}

#endif