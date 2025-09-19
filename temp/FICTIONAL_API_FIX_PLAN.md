# Fictional API Fix Plan

## Problem Scope

Over 25% of documented APIs are fictional. The documentation cannot be trusted and needs complete overhaul.

## Fix Strategy

### Phase 1: Document What Actually Exists
1. Generate accurate list of all headers that exist
2. Map actual function names to headers
3. Understand actual API structure

### Phase 2: Remove All Fiction
1. Delete migration.md entirely (mostly fictional)
2. Remove all references to master headers (xieite.hpp, math.hpp, etc.)
3. Fix all include paths to match actual headers
4. Remove references to non-existent functions

### Phase 3: Rebuild Documentation
1. Start with actual headers as source of truth
2. Write examples that actually compile
3. No speculation about "old" versions
4. No fictional migration scenarios

## Specific Fixes Needed

### Include Path Corrections

#### Math Headers
```cpp
// WRONG (documented)
#include <xieite/math/min.hpp>
#include <xieite/math/max.hpp>

// CORRECT (actual)
#include <xieite/math/minmax.hpp>
// Returns an interval, not separate min/max
```

```cpp
// WRONG
#include <xieite/math/fact.hpp>
#include <xieite/math/fibonacci.hpp>

// CORRECT
#include <xieite/math/factorial.hpp>
#include <xieite/math/fib.hpp>
```

#### System Headers
```cpp
// WRONG
#include <xieite/sys/arch.hpp>
#include <xieite/sys/os.hpp>

// CORRECT
#include <xieite/pp/arch.hpp>
#include <xieite/pp/os.hpp>
```

### Functions That Don't Exist
Remove all references to:
- `xieite::min()` - use `xieite::minmax()`
- `xieite::max()` - use `xieite::minmax()`
- `xieite::gcd()` - DOESN'T EXIST
- `xieite::lcm()` - DOESN'T EXIST
- `xieite::clamp()` - DOESN'T EXIST
- `xieite::enumerate()` - DOESN'T EXIST
- `xieite::filter()` - DOESN'T EXIST
- `xieite::zip()` - DOESN'T EXIST

### Migration.md
**Recommendation**: DELETE ENTIRELY
- Pre-1.0 versions may be fictional
- static_array never existed
- Most "old" syntax examples are made up
- Cannot verify any historical claims

### Getting Started Guide
Needs complete rewrite:
1. Use actual headers that exist
2. Show actual functions that exist
3. Test all examples compile

## Files Requiring Major Surgery

1. `docs/src/appendix/migration.md` - DELETE or completely rewrite
2. `docs/src/examples/basic/getting_started.md` - Fix all includes
3. `docs/src/reference/api/*.md` - Fix all header references
4. `docs/src/categories/*/README.md` - Remove master header refs
5. All example files - Fix includes and function calls

## Validation Required

After fixes:
1. Extract every include path from docs
2. Verify each exists in include/xieite/
3. Extract every xieite:: function call
4. Verify each exists in the headers
5. Compile all code examples

## Severity

This is a **DOCUMENTATION EMERGENCY**. The docs are so inaccurate they're harmful. Users will:
- Get immediate compilation errors
- Be unable to follow basic tutorials
- Think the library is broken
- Lose trust in the project

## Recommendation

1. **Mark documentation as "UNDER REPAIR"**
2. **Warn users not to use current docs**
3. **Systematically fix everything**
4. **Re-validate completely**
5. **Test all examples compile**

The documentation needs to be treated as completely unreliable until comprehensively fixed and validated.

---

*This is not a minor issue - this is a fundamental documentation failure.*