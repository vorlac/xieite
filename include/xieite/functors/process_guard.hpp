#ifndef XIEITE_HEADER_FUNCTORS_PROCESS_GUARD
#	define XIEITE_HEADER_FUNCTORS_PROCESS_GUARD

#	include <concepts>
#	include "../functors/function.hpp"
#	include "../macros/forward.hpp"

namespace xieite::functors {
	struct ProcessGuard {
	public:
		template<std::invocable<> Functor, auto = [] {}>
		ProcessGuard(Functor&& callback) noexcept {
			struct Guard {
				const xieite::functors::Function<void()> callback;
				bool released = false;

				~Guard() {
					if (!this->released) {
						this->callback();
					}
				}
			};

			static Guard guard = Guard(XIEITE_FORWARD(callback));
			this->released = &guard.released;
		}

		void release() noexcept {
			*this->released = true;
		}

	private:
		bool* released;
	};
}

#endif
