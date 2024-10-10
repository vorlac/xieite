#pragma once

#include <chrono>
#include "../time/centuries.hpp"
#include "../time/decades.hpp"
#include "../time/eons.hpp"
#include "../time/epochs.hpp"
#include "../time/millenniums.hpp"

namespace xieite::literals::durations {
	[[nodiscard]] constexpr auto operator""_nanoseconds(const unsigned long long int value) noexcept {
		return std::chrono::nanoseconds(value);
	}

	[[nodiscard]] constexpr auto operator""_microseconds(const unsigned long long int value) noexcept {
		return std::chrono::microseconds(value);
	}

	[[nodiscard]] constexpr auto operator""_milliseconds(const unsigned long long int value) noexcept {
		return std::chrono::milliseconds(value);
	}

	[[nodiscard]] constexpr auto operator""_seconds(const unsigned long long int value) noexcept {
		return std::chrono::seconds(value);
	}

	[[nodiscard]] constexpr auto operator""_minutes(const unsigned long long int value) noexcept {
		return std::chrono::minutes(value);
	}

	[[nodiscard]] constexpr auto operator""_hours(const unsigned long long int value) noexcept {
		return std::chrono::hours(value);
	}

	[[nodiscard]] constexpr auto operator""_days(const unsigned long long int value) noexcept {
		return std::chrono::days(value);
	}

	[[nodiscard]] constexpr auto operator""_weeks(const unsigned long long int value) noexcept {
		return std::chrono::weeks(value);
	}

	[[nodiscard]] constexpr auto operator""_months(const unsigned long long int value) noexcept {
		return std::chrono::months(value);
	}

	[[nodiscard]] constexpr auto operator""_years(const unsigned long long int value) noexcept {
		return std::chrono::years(value);
	}

	[[nodiscard]] constexpr auto operator""_decades(const unsigned long long int value) noexcept {
		return xieite::time::Decades(value);
	}

	[[nodiscard]] constexpr auto operator""_centuries(const unsigned long long int value) noexcept {
		return xieite::time::Centuries(value);
	}

	[[nodiscard]] constexpr auto operator""_millenniums(const unsigned long long int value) noexcept {
		return xieite::time::Millenniums(value);
	}

	[[nodiscard]] constexpr auto operator""_epochs(const unsigned long long int value) noexcept {
		return xieite::time::Epochs(value);
	}

	[[nodiscard]] constexpr auto operator""_eons(const unsigned long long int value) noexcept {
		return xieite::time::Eons(value);
	}
}
