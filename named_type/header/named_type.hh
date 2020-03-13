#ifndef __NAMED_TYPE_HH__
#define __NAMED_TYPE_HH__

//#include<utility>

namespace gsw{

template<typename T, typename parameter>
class named_type{
public:
  using value_type = T;
  using reference = T&;
  using const_ref = T const &;

private:
  value_type mValue;

public:
  named_type()
    : mValue()
  {}

  named_type( const_ref value )
    : mValue( value ){
  }

  named_type( T&& value )
    : mValue( std::move( value ) ){
  }

  reference
  get(){
    return mValue;
  }

  const_ref
  get() const{
    return mValue;
  }

  explicit
  operator T() const{
    return mValue;
  }

  named_type&
  operator=( const named_type& name_t ){
    mValue = name_t;

    return *this;
  }

  named_type&
  operator=( const_ref value ){
    mValue = value;

    return *this;
  }

  bool
  operator==( const named_type& name_t ) const{
    return mValue == name_t.mValue;
  }

  bool
  operator==( const_ref value ) const{
    return mValue == value;
  }
};

}

#endif