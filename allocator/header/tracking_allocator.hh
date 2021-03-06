#ifndef __TRACKING_ALLOCATOR_HH__
#define __TRACKING_ALLOCATOR_HH__

#include<algorithm>

#include<allocator.hh>

namespace gsw {

/*! Allocator which tracks the maximum object count during runtime
 *
 * @tparam T Type that will be allocated
 *
 * @tparam A Allocator to inherit base allocation behaviour from
 *
 * This allocator will track maximum memory usage, as well as exhibit any
 * allocation behaviour described by A.
 *
 * @todo add custom logging facility? (through callback)
 */
template<typename T, typename A = allocator <T>>
class tracking_allocator : public A {
public:
  using value_type = T;
  using pointer    = value_type*;
  using reference  = value_type&;
  using size_type  = unsigned long;
  using base       = A;

private:
  inline static size_type mMaxStored;

  inline static size_type mCurrentStored;

public:
  /*! Update tracking data, call base allocation
   *
   * @return Pointer to newly allocated objects
   */
  [[nodiscard]]
  pointer allocate(size_type number) {
    mCurrentStored += number;

    mMaxStored = std::max(mMaxStored, mCurrentStored);

    return base::allocate(number);
  }

  /*! Update tracking data, call base deallocation
   */
  void deallocate(pointer ptr, size_type number) {
    mCurrentStored -= number;

    base::deallocate(ptr, number);
  }

  /*! Get the current number of T objects
   *
   * @return The current usage value
   */
  [[nodiscard]]
  size_type usage() const {
    return mCurrentStored;
  }

  /*! Get the max usage thus far
   *
   * @return The maximum usage value
   *
   * Maximum number of objects of type T allocated at one time
   */
  [[nodiscard]]
  size_type max_usage() const {
    return mMaxStored;
  }
};

}

#endif
