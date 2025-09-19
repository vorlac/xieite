# Functional API Reference

## Overview

The functional category contains 50+ header files providing functional programming utilities, including function composition, currying, memoization, scope guards, and combinators optimized for both compile-time and runtime use.

## Organization

The fn headers are organized into functional groups:

- **Function Composition** (10+ headers): Compose, pipe, and chain functions
- **Currying & Partial Application** (8+ headers): Transform function signatures
- **Memoization** (5+ headers): Cache function results
- **Scope Management** (8+ headers): RAII and scope guards
- **Combinators** (10+ headers): Higher-order function patterns
- **Utilities** (10+ headers): General functional helpers

## Function Composition

### compose
**Header**: `fn/compose.hpp`
**Synopsis**: `auto compose(F&& f, G&& g)`
**Purpose**: Compose two functions (mathematical order)
**Example**:
```cpp
auto add_one = [](int x) { return x + 1; };
auto double_it = [](int x) { return x * 2; };
auto f = xieite::compose(double_it, add_one);
// f(5) = double_it(add_one(5)) = 12
```

### pipe
**Header**: `fn/pipe.hpp`
**Synopsis**: `auto pipe(F&& f, G&& g)`
**Purpose**: Compose functions in pipeline order
**Example**:
```cpp
auto add_one = [](int x) { return x + 1; };
auto double_it = [](int x) { return x * 2; };
auto f = xieite::pipe(add_one, double_it);
// f(5) = double_it(add_one(5)) = 12
```

### chain
**Header**: `fn/chain.hpp`
**Synopsis**: `auto chain(Funcs&&... fs)`
**Purpose**: Chain multiple functions
**Example**:
```cpp
auto f = xieite::chain(
    [](int x) { return x + 1; },
    [](int x) { return x * 2; },
    [](int x) { return x - 3; }
);
// f(5) = ((5 + 1) * 2) - 3 = 9
```

### apply_all
**Header**: `fn/apply_all.hpp`
**Synopsis**: `auto apply_all(Funcs&&... fs, Arg&& arg)`
**Purpose**: Apply multiple functions to same argument
**Example**:
```cpp
auto results = xieite::apply_all(
    [](int x) { return x + 1; },
    [](int x) { return x * 2; },
    [](int x) { return x * x; },
    5
);  // results = {6, 10, 25}
```

### apply_n
**Header**: `fn/apply_n.hpp`
**Synopsis**: `auto apply_n(F&& f, std::size_t n, Arg&& arg)`
**Purpose**: Apply function n times
**Example**:
```cpp
auto inc = [](int x) { return x + 1; };
auto result = xieite::apply_n(inc, 3, 5);  // 8
```

### apply_until
**Header**: `fn/apply_until.hpp`
**Synopsis**: `auto apply_until(F&& f, Pred&& p, Arg&& arg)`
**Purpose**: Apply function until predicate is true
**Example**:
```cpp
auto double_it = [](int x) { return x * 2; };
auto too_big = [](int x) { return x > 100; };
auto result = xieite::apply_until(double_it, too_big, 3);  // 96
```

### apply_while
**Header**: `fn/apply_while.hpp`
**Synopsis**: `auto apply_while(F&& f, Pred&& p, Arg&& arg)`
**Purpose**: Apply function while predicate is true
**Example**:
```cpp
auto inc = [](int x) { return x + 1; };
auto small = [](int x) { return x < 10; };
auto result = xieite::apply_while(inc, small, 5);  // 10
```

## Currying & Partial Application

### curry
**Header**: `fn/curry.hpp`
**Synopsis**: `auto curry(F&& f)`
**Purpose**: Transform n-ary function to curried form
**Example**:
```cpp
auto add = [](int a, int b, int c) { return a + b + c; };
auto curried = xieite::curry(add);
auto f1 = curried(1);       // Partially applied
auto f2 = f1(2);            // Partially applied
auto result = f2(3);        // 6
```

### uncurry
**Header**: `fn/uncurry.hpp`
**Synopsis**: `auto uncurry(F&& f)`
**Purpose**: Transform curried function to n-ary
**Example**:
```cpp
auto curried = [](int a) {
    return [a](int b) {
        return [a, b](int c) { return a + b + c; };
    };
};
auto uncurried = xieite::uncurry(curried);
auto result = uncurried(1, 2, 3);  // 6
```

### partial
**Header**: `fn/partial.hpp`
**Synopsis**: `auto partial(F&& f, Args&&... args)`
**Purpose**: Partially apply function from left
**Example**:
```cpp
auto add = [](int a, int b, int c) { return a + b + c; };
auto add_5 = xieite::partial(add, 5);
auto result = add_5(10, 15);  // 30
```

### partial_right
**Header**: `fn/partial_right.hpp`
**Synopsis**: `auto partial_right(F&& f, Args&&... args)`
**Purpose**: Partially apply function from right
**Example**:
```cpp
auto divide = [](int a, int b) { return a / b; };
auto divide_by_2 = xieite::partial_right(divide, 2);
auto result = divide_by_2(10);  // 5
```

### bind_front
**Header**: `fn/bind_front.hpp`
**Synopsis**: `auto bind_front(F&& f, Args&&... args)`
**Purpose**: Bind arguments at front (like std::bind_front)
**Example**:
```cpp
auto sub = [](int a, int b) { return a - b; };
auto sub_from_10 = xieite::bind_front(sub, 10);
auto result = sub_from_10(3);  // 7
```

### bind_back
**Header**: `fn/bind_back.hpp`
**Synopsis**: `auto bind_back(F&& f, Args&&... args)`
**Purpose**: Bind arguments at back
**Example**:
```cpp
auto sub = [](int a, int b) { return a - b; };
auto sub_5 = xieite::bind_back(sub, 5);
auto result = sub_5(10);  // 5
```

### flip
**Header**: `fn/flip.hpp`
**Synopsis**: `auto flip(F&& f)`
**Purpose**: Flip function arguments
**Example**:
```cpp
auto divide = [](int a, int b) { return a / b; };
auto flipped = xieite::flip(divide);
auto result = flipped(2, 10);  // 5 (10/2)
```

### rotate_args
**Header**: `fn/rotate_args.hpp`
**Synopsis**: `auto rotate_args(F&& f)`
**Purpose**: Rotate function arguments
**Example**:
```cpp
auto f = [](int a, int b, int c) {
    return std::vector{a, b, c};
};
auto rotated = xieite::rotate_args(f);
auto result = rotated(1, 2, 3);  // {2, 3, 1}
```

## Memoization

### memoize
**Header**: `fn/memoize.hpp`
**Synopsis**: `auto memoize(F&& f)`
**Purpose**: Cache function results
**Example**:
```cpp
auto fib = xieite::memoize([](auto& self, int n) -> int {
    if (n <= 1) return n;
    return self(n - 1) + self(n - 2);
});
auto result = fib(40);  // Fast computation
```

### memoize_recursive
**Header**: `fn/memoize_recursive.hpp`
**Synopsis**: `auto memoize_recursive(F&& f)`
**Purpose**: Memoize recursive functions
**Example**:
```cpp
auto factorial = xieite::memoize_recursive(
    [](auto& self, int n) -> int {
        return n <= 1 ? 1 : n * self(n - 1);
    }
);
```

### memoize_limited
**Header**: `fn/memoize_limited.hpp`
**Synopsis**: `auto memoize_limited(F&& f, std::size_t max_cache)`
**Purpose**: Memoize with cache size limit
**Example**:
```cpp
auto expensive = xieite::memoize_limited(
    [](int x) { /* expensive computation */ return x * x; },
    100  // Cache up to 100 entries
);
```

### memoize_timed
**Header**: `fn/memoize_timed.hpp`
**Synopsis**: `auto memoize_timed(F&& f, Duration ttl)`
**Purpose**: Memoize with time-to-live
**Example**:
```cpp
using namespace std::chrono_literals;
auto cached = xieite::memoize_timed(
    [](int x) { return fetch_data(x); },
    5min  // Cache for 5 minutes
);
```

### clear_memoization
**Header**: `fn/clear_memoization.hpp`
**Synopsis**: `void clear_memoization(MemoizedFunc& f)`
**Purpose**: Clear memoization cache
**Example**:
```cpp
auto memo = xieite::memoize(expensive_func);
// ... use memo ...
xieite::clear_memoization(memo);  // Clear cache
```

## Scope Guards

### scope_exit
**Header**: `fn/scope_exit.hpp`
**Synopsis**: `class scope_exit<F>`
**Purpose**: Execute function on scope exit
**Example**:
```cpp
{
    auto guard = xieite::scope_exit([]{
        std::cout << "Cleanup\n";
    });
    // ... code ...
}  // Cleanup executed here
```

### scope_fail
**Header**: `fn/scope_fail.hpp`
**Synopsis**: `class scope_fail<F>`
**Purpose**: Execute function on exception
**Example**:
```cpp
{
    auto guard = xieite::scope_fail([]{
        std::cout << "Error occurred\n";
    });
    throw std::runtime_error("oops");
}  // "Error occurred" printed
```

### scope_success
**Header**: `fn/scope_success.hpp`
**Synopsis**: `class scope_success<F>`
**Purpose**: Execute function on normal exit
**Example**:
```cpp
{
    auto guard = xieite::scope_success([]{
        std::cout << "Success\n";
    });
    // Normal execution
}  // "Success" printed
```

### defer
**Header**: `fn/defer.hpp`
**Synopsis**: `auto defer(F&& f)`
**Purpose**: Defer execution (Go-style)
**Example**:
```cpp
{
    xieite::defer([]{ cleanup(); });
    // ... code ...
}  // cleanup() called here
```

### finally
**Header**: `fn/finally.hpp`
**Synopsis**: `auto finally(F&& f)`
**Purpose**: Java-style finally block
**Example**:
```cpp
auto guard = xieite::finally([]{
    close_resources();
});
```

### with_cleanup
**Header**: `fn/with_cleanup.hpp`
**Synopsis**: `auto with_cleanup(Init&& init, Cleanup&& cleanup)`
**Purpose**: Resource with cleanup
**Example**:
```cpp
auto file = xieite::with_cleanup(
    []{ return open_file("data.txt"); },
    [](auto* f){ close_file(f); }
);
```

### raii
**Header**: `fn/raii.hpp`
**Synopsis**: `class raii<Resource, Deleter>`
**Purpose**: Generic RAII wrapper
**Example**:
```cpp
xieite::raii file(fopen("data.txt", "r"), fclose);
```

### unique_resource
**Header**: `fn/unique_resource.hpp`
**Synopsis**: `class unique_resource<R, D>`
**Purpose**: Unique ownership with custom deleter
**Example**:
```cpp
xieite::unique_resource handle(
    CreateHandle(),
    [](HANDLE h){ CloseHandle(h); }
);
```

## Combinators

### identity
**Header**: `fn/identity.hpp`
**Synopsis**: `auto identity(T&& t)`
**Purpose**: Identity function
**Example**:
```cpp
auto x = xieite::identity(42);  // 42
```

### constant
**Header**: `fn/constant.hpp`
**Synopsis**: `auto constant(T&& t)`
**Purpose**: Constant function
**Example**:
```cpp
auto always_42 = xieite::constant(42);
auto x = always_42();      // 42
auto y = always_42(1, 2);  // 42
```

### ignore
**Header**: `fn/ignore.hpp`
**Synopsis**: `auto ignore(Args&&...)`
**Purpose**: Ignore all arguments
**Example**:
```cpp
xieite::ignore(expensive_calc(), other_calc());
// Both calculated but results ignored
```

### y_combinator
**Header**: `fn/y_combinator.hpp`
**Synopsis**: `auto y_combinator(F&& f)`
**Purpose**: Fixed-point combinator
**Example**:
```cpp
auto factorial = xieite::y_combinator(
    [](auto self, int n) -> int {
        return n <= 1 ? 1 : n * self(n - 1);
    }
);
```

### fix
**Header**: `fn/fix.hpp`
**Synopsis**: `auto fix(F&& f)`
**Purpose**: Fixed-point operator
**Example**:
```cpp
auto gcd = xieite::fix([](auto self, int a, int b) -> int {
    return b == 0 ? a : self(b, a % b);
});
```

### iterate
**Header**: `fn/iterate.hpp`
**Synopsis**: `auto iterate(F&& f, T&& init)`
**Purpose**: Generate infinite sequence
**Example**:
```cpp
auto powers_of_2 = xieite::iterate(
    [](int x) { return x * 2; },
    1
);
// Generates: 1, 2, 4, 8, 16, ...
```

### unfold
**Header**: `fn/unfold.hpp`
**Synopsis**: `auto unfold(F&& f, Seed&& seed)`
**Purpose**: Generate sequence from seed
**Example**:
```cpp
auto fibs = xieite::unfold(
    [](auto [a, b]) {
        return std::pair{a, std::pair{b, a + b}};
    },
    std::pair{0, 1}
);
```

### fold_left
**Header**: `fn/fold_left.hpp`
**Synopsis**: `auto fold_left(F&& f, Init&& init, Range&& r)`
**Purpose**: Left fold over range
**Example**:
```cpp
std::vector<int> v{1, 2, 3, 4};
auto sum = xieite::fold_left(std::plus{}, 0, v);  // 10
```

### fold_right
**Header**: `fn/fold_right.hpp`
**Synopsis**: `auto fold_right(F&& f, Range&& r, Init&& init)`
**Purpose**: Right fold over range
**Example**:
```cpp
std::vector<int> v{1, 2, 3, 4};
auto result = xieite::fold_right(
    [](int x, int acc) { return x - acc; },
    v, 0
);  // 1 - (2 - (3 - (4 - 0))) = -2
```

### scan_left
**Header**: `fn/scan_left.hpp`
**Synopsis**: `auto scan_left(F&& f, Init&& init, Range&& r)`
**Purpose**: Cumulative left fold
**Example**:
```cpp
std::vector<int> v{1, 2, 3, 4};
auto sums = xieite::scan_left(std::plus{}, 0, v);
// sums = {0, 1, 3, 6, 10}
```

## Function Utilities

### overload
**Header**: `fn/overload.hpp`
**Synopsis**: `auto overload(Fs&&... fs)`
**Purpose**: Create overload set from lambdas
**Example**:
```cpp
auto visitor = xieite::overload(
    [](int x) { return x * 2; },
    [](double x) { return x / 2; },
    [](const std::string& s) { return s.size(); }
);
```

### invoke
**Header**: `fn/invoke.hpp`
**Synopsis**: `auto invoke(F&& f, Args&&... args)`
**Purpose**: INVOKE operation
**Example**:
```cpp
struct S { int value = 42; };
S s;
auto v = xieite::invoke(&S::value, s);  // 42
```

### invoke_result
**Header**: `fn/invoke_result.hpp`
**Synopsis**: `using invoke_result_t<F, Args...>`
**Purpose**: Result type of invocation
**Example**:
```cpp
using R = xieite::invoke_result_t<decltype(std::plus{}), int, int>;
// R is int
```

### is_invocable
**Header**: `fn/is_invocable.hpp`
**Synopsis**: `concept is_invocable<F, Args...>`
**Purpose**: Check if invocable
**Example**:
```cpp
static_assert(xieite::is_invocable<decltype(std::plus{}), int, int>);
```

### function_ref
**Header**: `fn/function_ref.hpp`
**Synopsis**: `class function_ref<Sig>`
**Purpose**: Non-owning function reference
**Example**:
```cpp
void process(xieite::function_ref<int(int)> f) {
    auto result = f(42);
}
```

### move_only_function
**Header**: `fn/move_only_function.hpp`
**Synopsis**: `class move_only_function<Sig>`
**Purpose**: Move-only type-erased function
**Example**:
```cpp
xieite::move_only_function<void()> f = [p = std::make_unique<int>(42)](){
    std::cout << *p;
};
```

### small_function
**Header**: `fn/small_function.hpp`
**Synopsis**: `template<typename Sig, std::size_t Size> class small_function`
**Purpose**: Function with small buffer optimization
**Example**:
```cpp
xieite::small_function<int(int), 32> f = [](int x) { return x * 2; };
// No heap allocation for small lambdas
```

## Lazy Evaluation

### lazy
**Header**: `fn/lazy.hpp`
**Synopsis**: `class lazy<F>`
**Purpose**: Lazy evaluation wrapper
**Example**:
```cpp
xieite::lazy expensive = []{
    return compute_expensive();
};
// Not computed yet
auto value = expensive.get();  // Computed now
auto again = expensive.get();  // Cached
```

### lazy_val
**Header**: `fn/lazy_val.hpp`
**Synopsis**: `class lazy_val<T>`
**Purpose**: Lazy-initialized value
**Example**:
```cpp
xieite::lazy_val<Config> config = []{
    return load_config();
};
```

### thunk
**Header**: `fn/thunk.hpp`
**Synopsis**: `auto thunk(F&& f, Args&&... args)`
**Purpose**: Delay computation
**Example**:
```cpp
auto computation = xieite::thunk(expensive_func, arg1, arg2);
// ... later ...
auto result = computation();  // Execute now
```

## Monadic Operations

### maybe
**Header**: `fn/maybe.hpp`
**Synopsis**: `class maybe<T>`
**Purpose**: Optional with monadic interface
**Example**:
```cpp
xieite::maybe<int> m = 42;
auto result = m.map([](int x) { return x * 2; })
               .filter([](int x) { return x > 50; })
               .value_or(0);  // 84
```

### result
**Header**: `fn/result.hpp`
**Synopsis**: `class result<T, E>`
**Purpose**: Result type with error
**Example**:
```cpp
xieite::result<int, std::string> divide(int a, int b) {
    if (b == 0) return xieite::err("Division by zero");
    return xieite::ok(a / b);
}
```

### either
**Header**: `fn/either.hpp`
**Synopsis**: `class either<L, R>`
**Purpose**: Sum type
**Example**:
```cpp
xieite::either<std::string, int> value = 42;
value.match(
    [](const std::string& s) { std::cout << "String: " << s; },
    [](int n) { std::cout << "Number: " << n; }
);
```

## Pipeline Operations

### operator|
**Header**: `fn/pipe_operator.hpp`
**Synopsis**: Range pipe operator overload
**Purpose**: Enable pipeline syntax
**Example**:
```cpp
auto result = data
    | xieite::filter([](int x) { return x > 0; })
    | xieite::map([](int x) { return x * 2; })
    | xieite::take(10);
```

### tap
**Header**: `fn/tap.hpp`
**Synopsis**: `auto tap(F&& f)`
**Purpose**: Side effect in pipeline
**Example**:
```cpp
auto result = data
    | xieite::tap([](auto x) { std::cout << x; })
    | xieite::filter(pred);
```

## Thread-Safe Functions

### once
**Header**: `fn/once.hpp`
**Synopsis**: `auto once(F&& f)`
**Purpose**: Execute function only once
**Example**:
```cpp
auto init = xieite::once([]{
    initialize_system();
});
// Can be called from multiple threads
init();  // Executes
init();  // No-op
```

### synchronized
**Header**: `fn/synchronized.hpp`
**Synopsis**: `auto synchronized(F&& f)`
**Purpose**: Thread-safe function wrapper
**Example**:
```cpp
auto safe_inc = xieite::synchronized([](int& x) { ++x; });
```

## Usage Examples

### Function Composition
```cpp
#include <xieite/fn/compose.hpp>
#include <xieite/fn/curry.hpp>

auto add = xieite::curry([](int a, int b) { return a + b; });
auto mul = xieite::curry([](int a, int b) { return a * b; });
auto add_then_mul = xieite::compose(mul(2), add(3));
auto result = add_then_mul(5);  // (5 + 3) * 2 = 16
```

### Memoization
```cpp
#include <xieite/fn/memoize.hpp>

auto fib = xieite::memoize([](auto& self, int n) -> int {
    if (n <= 1) return n;
    return self(n - 1) + self(n - 2);
});
auto result = fib(100);  // Fast even for large numbers
```

### Scope Guards
```cpp
#include <xieite/fn/scope_exit.hpp>

void process_file(const std::string& path) {
    auto* file = fopen(path.c_str(), "r");
    auto guard = xieite::scope_exit([file]{
        if (file) fclose(file);
    });
    // Process file...
    // File automatically closed
}
```

### Pipeline
```cpp
#include <xieite/fn/pipe_operator.hpp>

std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
auto result = nums
    | xieite::filter([](int x) { return x % 2 == 0; })
    | xieite::map([](int x) { return x * x; })
    | xieite::take(3);
// result = {4, 16, 36}
```

## Performance Notes

- Small function optimization reduces allocations
- Memoization trades memory for speed
- Lazy evaluation defers computation
- Move-only functions avoid reference counting
- Function_ref avoids type erasure overhead

## See Also

- [Functional Overview](../../categories/fn/README.md)
- [Function Composition](../../categories/fn/composition.md)
- [Currying Patterns](../../categories/fn/currying.md)
- [Data Structures API](./data.md)