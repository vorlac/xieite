#pragma once

namespace xieite::system {
	void segmentationFault() noexcept {
		*static_cast<volatile int*>(nullptr);
	}
}
