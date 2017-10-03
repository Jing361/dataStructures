#include<equation.hh>

using namespace std;
using namespace gsw;

double equation::variable::evaluate( const equation::data& variables ) const{
  return variables.at( name );
}

double equation::multiplication::evaluate( const equation::data& variables ) const{
  return lhs->evaluate( variables ) * rhs->evaluate( variables );
}

double equation::division::evaluate( const equation::data& variables ) const{
  return lhs->evaluate( variables ) / rhs->evaluate( variables );
}

double equation::addition::evaluate( const equation::data& variables ) const{
  return lhs->evaluate( variables ) + rhs->evaluate( variables );
}

double equation::subtraction::evaluate( const equation::data& variables ) const{
  return lhs->evaluate( variables ) - rhs->evaluate( variables );
}

double equation::inversion::evaluate( const equation::data& variables ) const{
  return -operand->evaluate( variables );
}

equation::equation( const equation::op_ptr value ):
  mValue( value ){
}

equation equation::operator*( const equation& multiplicand ) const{
  auto var = make_shared<equation::multiplication>();
  var->lhs = mValue;
  var->rhs = multiplicand.mValue;
  return {var};
}

equation equation::operator/( const equation& dividend ) const{
  auto var = make_shared<equation::division>();
  var->lhs = mValue;
  var->rhs = dividend.mValue;
  return {var};
}

equation equation::operator+( const equation& operand ) const{
  auto var = make_shared<equation::addition>();
  var->lhs = mValue;
  var->rhs = operand.mValue;
  return {var};
}

equation equation::operator-( const equation& operand ) const{
  auto var = make_shared<equation::subtraction>();
  var->lhs = mValue;
  var->rhs = operand.mValue;
  return {var};
}

equation equation::operator-() const{
  auto var = make_shared<equation::inversion>();
  var->operand = mValue;
  return {var};
}

equation equation::pow( const equation& operand ) const{
}

equation equation::derive( unsigned long long order ) const{
}

equation equation::integrate( unsigned long long min, unsigned long long max ) const{
}

double equation::evaluate( const equation::data& variables ) const{
  return mValue->evaluate( variables );
}

std::set<equation::data> equation::solve( const equation::data& variables ) const{
}

equation gsw::operator""_evar( const char* name, size_t sz ){
  auto var = std::make_shared<equation::variable>();
  var->name = std::string( name, sz );
  return {var};
}

