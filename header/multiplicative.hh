#ifndef __MULTIPLICATIVE_HH__
#define __MULTIPLICATIVE_HH__

/*! Multiplicative utility class to provide multiplication and division operators
 *
 * @tparam LHS  Type of the left hand side of the * and / operators
 *
 * @tparam RHS  Type of the right hand side of the * and / operators
 *
 * Convenience class to simply allow the * and / operators to a class
 * implementing the *= and /= operators through inheritance.
 *
 * Intended usage:
 * class foo : public multiplicative{
 * private:
 *   int x;
 *
 * public:
 *   friend foo& operator*=( foo& lhs, const foo& rhs ){
 *     lhs.x *= rhs.x;
 *
 *     return lhs;
 *   }
 *   friend foo& operator/=( foo& lhs, const foo& rhs ){
 *     lhs.x /= rhs.x;
 *
 *     return lhs;
 *   }
 * };
 *
 * This will provide 'for free' the * and / operators as well.
 */
template<typename LHS, typename RHS = LHS>
class multiplicative{
public:
  typedef LHS lhs_type;
  typedef RHS rhs_type;

  /*! Multiplication operator
   *
   * @param lhs  Left hand side of * operator
   *
   * @param rhs  Right hand side of * operator
   *
   * @return Value of result of the multiplication
   *
   * Multiplies together lhs and rhs using the *= operator of the derived class.
   */
  friend lhs_type operator*( lhs_type t, const rhs_type& u ) noexcept{
    return ( t *= u );
  }

  /*! Division operator
   *
   * @param lhs  Left hand side of / operator
   *
   * @param rhs  Right hand side of / operator
   *
   * @return Value of result of the division
   *
   * Divides lhs by rhs using the /= operator of the derived class.
   */
  friend lhs_type operator/( lhs_type t, const rhs_type& u ) noexcept{
    return ( t /= u );
  }
};

#endif

