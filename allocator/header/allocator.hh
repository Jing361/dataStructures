#ifndef __ALLOCATOR_HH__
#define __ALLOCATOR_HH__

namespace gsw {

/*! Basic allocator, using new and delete
 *
 * @tparam T Type of objects allocated and constructed by this allocator
 */
template<typename T>
class allocator {
public:
  using value_type = T;
  using pointer    = value_type*;
  using reference  = value_type&;
  using size_type  = unsigned long;

private:

public:
  allocator() = default;
  allocator(const allocator&) = default;
  allocator(allocator&&) noexcept = default;

  /*! Allocate memory
   *
   * @param number Number of objects to allocate space for
   *
   * Allocate enough memory for number objects of type T
   */
  [[nodiscard]]
  pointer allocate(size_type number) {
    return pointer(new unsigned char[number * sizeof(value_type)]);
  }

  /*! Deallocate memory
   *
   * @param ptr
   *
   * @param numebr
   *
   * Deallocate/delete memory previously allocated by this allocator
   */
  void deallocate(pointer ptr, size_type) {
    delete[] (unsigned char*) (ptr);
  }
};

}

#endif
