#include <atomic>

template<typename T>
void update_maximum(std::atomic<T>& max, T const& value) noexcept
{
    //
    // 1. compare_exchange_weak will update the pre_value if it's failed in compare.
    // 2. use weak version to gain a better performance (on some platform) due to that
    //    we are in a loop, no matter whatever failure (including "spurious" failure)
    //    we need to retry to handle that failures.
    // 3. use memory_order_relaxed since we have no requirement related to the variables visibility
    //
    T prev_value = max;
    while (prev_value < value &&
           !max.compare_exchange_weak(prev_value, value, std::memory_order_relaxed)) {
    }
}
