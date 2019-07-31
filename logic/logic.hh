#ifndef __LOGIC_HH__
#define __LOGIC_HH__

/*!
 * @example test-logic.cc
 */

#include<string>
#include<set>
#include<memory>

namespace gsw{

namespace detail{

  template<typename T>
  std::set<T>
  merge( std::set<T> lhs, std::set<T> rhs ){
    //lhs.merge( rhs );
    for( auto var : lhs ){
      rhs.insert( var );
    }

    return rhs;
  }

}

/*! Logical proposition
 */
class proposition{
private:
  struct operation{
    virtual
    bool
    evaluate( const std::set<std::string>& facts ) const = 0;

    virtual
    std::set<std::set<std::string> >
    solve( std::set<std::string> data ) const = 0;
  };

  using op_ptr = std::shared_ptr<operation>;

  struct variable : public operation{
    std::string name;

    bool
    evaluate( const std::set<std::string>& facts ) const;

    std::set<std::set<std::string> >
    solve( std::set<std::string> data ) const;
  };

  struct conjunction : public operation{
    op_ptr lhs;
    op_ptr rhs;

    bool
    evaluate( const std::set<std::string>& facts ) const;

    std::set<std::set<std::string> >
    solve( std::set<std::string> data ) const;
  };

  struct disjunction : public operation{
    op_ptr lhs;
    op_ptr rhs;

    bool
    evaluate( const std::set<std::string>& facts ) const;

    std::set<std::set<std::string> >
    solve( std::set<std::string> data ) const;
  };

  struct exDisjunction : public operation{
    op_ptr lhs;
    op_ptr rhs;

    bool
    evaluate( const std::set<std::string>& facts ) const;

    std::set<std::set<std::string> >
    solve( std::set<std::string> data ) const;
  };

  struct negation : public operation{
    op_ptr operand;

    bool
    evaluate( const std::set<std::string>& facts ) const;

    std::set<std::set<std::string> >
    solve( std::set<std::string> data ) const;
  };

  proposition( const op_ptr value );

  op_ptr mValue;

public:
  /*! Conjunction operator
   *
   * @param conjunct
   *
   * @return A new proposition of the conjunction of this and conjunct
   */
  proposition
  operator&&( const proposition& conjunct ) const;

  /*! Disjunction operator
   *
   * @param disjunct
   *
   * @return A new proposition of the disjunction of this and disjunct
   */
  proposition
  operator||( const proposition& disjunct ) const;

  /*! Xor operator
   *
   * @param operand
   *
   * @return A new proposition of the exclusive disjunction of this and operand
   */
  proposition
  operator^( const proposition& operand ) const;

  /*! Negation operator
   *
   * @return A new proposition of the negation of this
   *
   * @todo automatically optimize double negation?
   * when a negation prop receives a negation, instead return the original
   * negation's child
   */
  proposition
  operator!() const;

  /*! Implication operation
   *
   * @param consequent
   *
   * @return A new proposition of the implication of this and consequent
   */
  proposition
  implies( const proposition& consequent ) const;

  /*! If and only if
   *
   * @param equivalent proposition to evaluate against
   *
   * @return A new proposition of the tautology of this and equivalent
   */
  proposition
  iff( const proposition& equivalent ) const;

  /*! Evaluate proposition using given facts
   *
   * @param facts Set of established truths.
   *
   * @return Whether the proposition is true given facts
   */
  bool
  evaluate( const std::set<std::string>& facts ) const;

  /*! Evaluation operator
   *
   * @param facts Set of established truths.
   *
   * @return Whether the proposition is true given facts
   *
   * Alias for bool proposition::evaluate( set<string> )
   */
  bool
  operator()( const std::set<std::string>& facts ) const{
    return evaluate( facts );
  }

  /*! Reverse evaluation
   *
   * @param variables set of variables to work with
   *
   * @return set of all possible solutions to proposition
   *
   * Determine what combinations of given variables make proposition true.
   * Provided solutions only consist of those that can be made up from vars
   * provided in variables.
   */
  std::set<std::set<std::string> >
  solve( const std::set<std::string>& variables ) const;

  std::set<std::set<std::string> >
  solve2( std::set<std::string> variables ) const;

  /*! Creates basic proposition that consists only of a variable named name
   *
   * @return A proposition representing a variable named name
   *
   * User string literal operator.
   * Used as:
   * @code{.cpp}
   * auto foo = "bar"_lvar;
   * @endcode
   *
   * To create a variable proposition named bar, and assigned to a variable
   * named foo.
   */
  friend
  proposition
  operator""_lvar( const char* name, size_t sz );
};

proposition
operator""_lvar( const char* name, size_t sz );

}

#endif
