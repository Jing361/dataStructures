#ifndef __EQUATION_HH__
#define __EQUATION_HH__

#include<vector>
#include<functional>
#include<cmath>

class equation{
private:
  typedef std::vector<double> storage_type;
  storage_type mCoeff;

  template<class operation>
  storage_type merge( const storage_type& small, const storage_type& large, bool swapOperands = false, operation op = operation() ){
    storage_type vec;
    int i = 0;

    vec = large;

    for( auto it : small ){
      if( swapOperands ){
        vec[i] = op( vec[i], it );
      } else {
        vec[i] = op( it, vec[i] );
      }
      ++i;
    }

    return vec;
  }

public:
  equation() = default;

  template<class inputIter>
  equation( inputIter first, inputIter last ):
    mCoeff( first, last ){
  }

  equation( const equation& eq );

  equation( equation&& eq );

  equation& operator=( const equation& eq );

  equation& operator=( equation&& eq );

  equation operator+( const equation& rhs );

  equation& operator+=( const equation& rhs );

  equation operator-( const equation& rhs );

  equation& operator-=( const equation& rhs );

  equation operator*( const equation& rhs );

  equation& operator*=( const equation& rhs );

  equation operator*( double d );

  equation& operator*=( double d );

  equation operator/( const equation& rhs );

  equation operator/( double d );

  equation& operator/=( double d );

  double operator()( const double X );

  friend equation derive( const equation& eq, unsigned int order = 1 );
  friend equation antiderive( const equation& eq );
  friend double integrate( const equation& eq, double upperBound, double lowerBound );
};

#endif

