module;

#include <xieite/arrow.hpp>
#include <xieite/forward.hpp>

export module xieite:functors.Mixfix;

import :concepts.Invocable;
import :containers.MaybeCopyAssignable;
import :containers.MaybeMoveAssignable;
import :functors.Function;

export namespace xieite::functors {
    template <typename>
    struct Mixfix;

    template <typename Return, typename Argument>
    struct Mixfix<Return(Argument)>
        : xieite::functors::Function<Return(Argument)> {
        using xieite::functors::Function<Return(Argument)>::Function;

        template <std::convertible_to<Argument> ArgumentReference>
        /* discardable */ friend constexpr Return operator->*(const Mixfix& mixfix, ArgumentReference&& argument)
            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                template <std::convertible_to<Argument> ArgumentReference>
                /* discardable */ friend constexpr Return operator*(const Mixfix& mixfix, ArgumentReference&& argument)
                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                        template <std::convertible_to<Argument> ArgumentReference>
                        /* discardable */ friend constexpr Return operator/(const Mixfix& mixfix, ArgumentReference&& argument)
                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                template <std::convertible_to<Argument> ArgumentReference>
                                /* discardable */ friend constexpr Return operator%(const Mixfix& mixfix, ArgumentReference&& argument)
                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                        template <std::convertible_to<Argument> ArgumentReference>
                                        /* discardable */ friend constexpr Return operator+(const Mixfix& mixfix, ArgumentReference&& argument)
                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                template <std::convertible_to<Argument> ArgumentReference>
                                                /* discardable */ friend constexpr Return operator-(const Mixfix& mixfix, ArgumentReference&& argument)
                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                        /* discardable */ friend constexpr Return operator<<(const Mixfix& mixfix, ArgumentReference&& argument)
                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                /* discardable */ friend constexpr Return operator>>(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                        /* discardable */ friend constexpr Return operator<=>(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                /* discardable */ friend constexpr Return operator<(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                        /* discardable */ friend constexpr Return operator<=(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                /* discardable */ friend constexpr Return operator>(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                        /* discardable */ friend constexpr Return operator>=(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                /* discardable */ friend constexpr Return operator==(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                        /* discardable */ friend constexpr Return operator!=(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                /* discardable */ friend constexpr Return operator&(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                        /* discardable */ friend constexpr Return operator^(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                /* discardable */ friend constexpr Return operator|(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                        /* discardable */ friend constexpr Return operator&&(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                /* discardable */ friend constexpr Return operator||(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                        /* discardable */ friend constexpr Return operator*=(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                /* discardable */ friend constexpr Return operator/=(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                        /* discardable */ friend constexpr Return operator%=(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                /* discardable */ friend constexpr Return operator+=(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator-=(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator<<=(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator>>=(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator&=(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator^=(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator|=(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator,(const Mixfix& mixfix, ArgumentReference&& argument)
                                                                                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator->*(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator*(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator/(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator%(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator+(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator-(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator<<(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator>>(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator<=>(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator<(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator<=(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator>(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator>=(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator==(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator!=(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator&(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator^(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator|(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator&&(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator||(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator*=(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator/=(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator%=(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator+=(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator-=(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator<<=(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator>>=(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator&=(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator^=(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator|=(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                template <std::convertible_to<Argument> ArgumentReference>
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator,(ArgumentReference&& argument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(mixfix(std::forward<decltype(argument)>(argument)))
    };

    template <typename Return, typename LeftArgument, typename RightArgument>
    struct Mixfix<Return(LeftArgument, RightArgument)>
        : xieite::functors::Function<Return(LeftArgument, RightArgument)> {
    private:
        template <typename LeftArgumentReference>
        struct Intermediate
            : xieite::containers::MaybeCopyAssignable<false>,
              xieite::containers::MaybeMoveAssignable<false> {
        public:
            constexpr Intermediate(const Mixfix& mixfix, LeftArgumentReference&& leftArgument) noexcept
                : mixfix(mixfix)
                , leftArgument(std::forward<decltype(leftArgument)>(leftArgument)) {
            }

        template <std::convertible_to<RightArgument> RightArgumentReference>
        /* discardable */ friend constexpr Return operator->*(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
            XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                template <std::convertible_to<RightArgument> RightArgumentReference>
                /* discardable */ friend constexpr Return operator*(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                    XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                        template <std::convertible_to<RightArgument> RightArgumentReference>
                        /* discardable */ friend constexpr Return operator/(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                            XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                template <std::convertible_to<RightArgument> RightArgumentReference>
                                /* discardable */ friend constexpr Return operator%(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                    XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                        template <std::convertible_to<RightArgument> RightArgumentReference>
                                        /* discardable */ friend constexpr Return operator+(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                            XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                template <std::convertible_to<RightArgument> RightArgumentReference>
                                                /* discardable */ friend constexpr Return operator-(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                    XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                        template <std::convertible_to<RightArgument> RightArgumentReference>
                                                        /* discardable */ friend constexpr Return operator<<(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                            XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                /* discardable */ friend constexpr Return operator>>(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                    XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                        template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                        /* discardable */ friend constexpr Return operator<=>(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                            XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                /* discardable */ friend constexpr Return operator<(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                    XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                        template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                        /* discardable */ friend constexpr Return operator<=(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                            XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                /* discardable */ friend constexpr Return operator>(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                    XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                        template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                        /* discardable */ friend constexpr Return operator>=(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                            XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                                template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                                /* discardable */ friend constexpr Return operator==(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                                    XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                                        template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                                        /* discardable */ friend constexpr Return operator!=(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                                            XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                                                template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                                                /* discardable */ friend constexpr Return operator&(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                                                    XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                                                        template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                                                        /* discardable */ friend constexpr Return operator^(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                                                            XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                                                                template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                                                                /* discardable */ friend constexpr Return operator|(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                                                                    XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                                                                        template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                                                                        /* discardable */ friend constexpr Return operator&&(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                                                                            XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                                                                                template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                                                                                /* discardable */ friend constexpr Return operator||(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                                                                                    XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                                                                                        template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                                                                                        /* discardable */ friend constexpr Return operator*=(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                                                                                            XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                                                                                                template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                                                                                                /* discardable */ friend constexpr Return operator/=(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                                                                                                    XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                                                                                                        template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                                                                                                        /* discardable */ friend constexpr Return operator%=(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                                                                                                            XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                                                                                                                template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                                                                                                                /* discardable */ friend constexpr Return operator+=(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                                                                                                                    XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                                                                                                                        template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator-=(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                                                                                                                            XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                                                                                                                                template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator<<=(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                                                                                                                                    XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                                                                                                                                        template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator>>=(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                                                                                                                                            XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                                                                                                                                                template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator&=(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                                                                                                                                                        template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator^=(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                                                                                                                                                            XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                                                                                                                                                                template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                                                                                                                                                                /* discardable */ friend constexpr Return operator|=(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                                                                                                                                                                    XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                                                                                                                                                                        template <std::convertible_to<RightArgument> RightArgumentReference>
                                                                                                                                                                                                                                                        /* discardable */ friend constexpr Return operator,(const Intermediate&& intermediate, RightArgumentReference&& rightArgument)
                                                                                                                                                                                                                                                            XIEITE_ARROW_BASE(intermediate.mixfix(std::forward<decltype(intermediate.leftArgument)>(intermediate.leftArgument), std::forward<decltype(rightArgument)>(rightArgument)))

                                                                                                                                                                                                                                                                private : const Mixfix& mixfix;
            LeftArgumentReference&& leftArgument;
        };

    public:
        using xieite::functors::Function<Return(LeftArgument, RightArgument)>::Function;

        template <std::convertible_to<LeftArgument> LeftArgumentReference>
        [[nodiscard]] friend constexpr auto operator->*(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
            XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                template <std::convertible_to<LeftArgument> LeftArgumentReference>
                [[nodiscard]] friend constexpr auto operator*(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                    XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                        template <std::convertible_to<LeftArgument> LeftArgumentReference>
                        [[nodiscard]] friend constexpr auto operator/(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                            XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                [[nodiscard]] friend constexpr auto operator%(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                    XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                        template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                        [[nodiscard]] friend constexpr auto operator+(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                            XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                [[nodiscard]] friend constexpr auto operator-(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                    XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                        template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                        [[nodiscard]] friend constexpr auto operator<<(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                            XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                [[nodiscard]] friend constexpr auto operator>>(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                    XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                        template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                        [[nodiscard]] friend constexpr auto operator<=>(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                            XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                [[nodiscard]] friend constexpr auto operator<(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                    XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                        template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                        [[nodiscard]] friend constexpr auto operator<=(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                            XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                [[nodiscard]] friend constexpr auto operator>(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                    XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                        template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                        [[nodiscard]] friend constexpr auto operator>=(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                            XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                                template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                                [[nodiscard]] friend constexpr auto operator==(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                                    XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                                        template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                                        [[nodiscard]] friend constexpr auto operator!=(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                                            XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                                                template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                                                [[nodiscard]] friend constexpr auto operator&(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                                                    XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                                                        template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                                                        [[nodiscard]] friend constexpr auto operator^(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                                                            XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                                                                template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                                                                [[nodiscard]] friend constexpr auto operator|(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                                                                    XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                                                                        template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                                                                        [[nodiscard]] friend constexpr auto operator&&(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                                                                            XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                                                                                template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                                                                                [[nodiscard]] friend constexpr auto operator||(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                                                                                    XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                                                                                        template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                                                                                        [[nodiscard]] friend constexpr auto operator*=(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                                                                                            XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                                                                                                template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                                                                                                [[nodiscard]] friend constexpr auto operator/=(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                                                                                                    XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                                                                                                        template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                                                                                                        [[nodiscard]] friend constexpr auto operator%=(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                                                                                                            XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                                                                                                                template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                                                                                                                [[nodiscard]] friend constexpr auto operator+=(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                                                                                                                    XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                                                                                                                        template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                                                                                                                        [[nodiscard]] friend constexpr auto operator-=(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                                                                                                                            XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                                                                                                                                template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                                                                                                                                [[nodiscard]] friend constexpr auto operator<<=(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                                                                                                                                    XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                                                                                                                                        template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                                                                                                                                        [[nodiscard]] friend constexpr auto operator>>=(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                                                                                                                                            XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                                                                                                                                                template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                                                                                                                                                [[nodiscard]] friend constexpr auto operator&=(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                                                                                                                                                    XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                                                                                                                                                        template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                                                                                                                                                        [[nodiscard]] friend constexpr auto operator^=(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                                                                                                                                                            XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                                                                                                                                                                template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                                                                                                                                                                [[nodiscard]] friend constexpr auto operator|=(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                    XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))

                                                                                                                                                                                                                                                        template <std::convertible_to<LeftArgument> LeftArgumentReference>
                                                                                                                                                                                                                                                        [[nodiscard]] friend constexpr auto operator,(LeftArgumentReference&& leftArgument, const Mixfix& mixfix)
                                                                                                                                                                                                                                                            XIEITE_ARROW(Mixfix::Intermediate<LeftArgumentReference>(mixfix, std::forward<decltype(leftArgument)>(leftArgument)))
    };
}
