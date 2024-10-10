module;

#include <concepts>
#include <iterator>

export module xieite:concepts.NoThrowOperableIterator;

export namespace xieite::concepts {
    template <typename Iterator>
    concept NoThrowOperableIterator = std::input_or_output_iterator<Iterator> && std::is_nothrow_constructible_v<Iterator, Iterator> && std::is_nothrow_assignable_v<Iterator&, Iterator> && std::is_nothrow_convertible_v<Iterator, Iterator> && requires(Iterator iterator) {
        requires(noexcept(++iterator));
        requires(noexcept(--iterator));
        requires(noexcept(iterator++));
        requires(noexcept(iterator--));
        requires(noexcept(*iterator));
    };
}
