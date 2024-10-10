#pragma once

#include <concepts>
#include "../functors/function.hpp"
#include "../preprocessor/forward.hpp"

namespace xieite::functors {
	struct ScopeGuard {
	public:
		template<std::invocable<> Functor>
		constexpr ScopeGuard(Functor&& callback) noexcept
		: callback(XIEITE_FORWARD(callback)) {}

		constexpr ~ScopeGuard() {
			if (!this->released) {
				this->callback();
			}
		}

		constexpr void release() noexcept {
			this->released = true;
		}

	private:
		xieite::functors::Function<void()> callback;
		bool released = false;
	};
}
