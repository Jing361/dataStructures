#include<catch/catch.hpp>

#include<menu.hh>

TEST_CASE( "Menu allows option selection and provides callbacks on selection.", "[menu]" ){
  std::stringstream ss;
  auto pm = std::make_shared<menu<int>>();
  auto pm0 = std::make_shared<menu<int>>();
  std::shared_ptr<menu<int> > current( pm );

  pm->addOption( 0, "electric", pm0, [&](){ ss << "beep" << '\n'; } );
  pm->addOption( 1, "boogaloo", pm0, [&](){ ss << "boop" << '\n'; } );
  pm0->addOption( 0, "foo", pm, [&](){ ss << "buup" << '\n'; } );
  pm0->addOption( 1, "baz", pm, [&](){ ss << "biip" << '\n'; } );
  pm0->addOption( 1, "bar", pm, [&](){ ss << "byyp" << '\n'; } );

  //ctor compile check
  menu<int> one;
  menu<int> two( one );
  menu<int> three( menu<int>() );
  one.print( ss );
  one.print( ss );
  one.print( ss );

  SECTION( "Prints menus when requested." ){
    for( unsigned int i = 0; i < 2; ++i ){
      current->print( ss );
      current = current->select( i );
    }
    int i;
    std::string str;

    ss >> i;
    ss >> str;

    REQUIRE( i == 0 );
    REQUIRE( str == "electric" );

    ss >> i;
    ss >> str;

    REQUIRE( i == 1 );
    REQUIRE( str == "boogaloo" );

    ss >> str;

    REQUIRE( str == "beep" );

    ss >> i;
    ss >> str;

    REQUIRE( i == 0 );
    REQUIRE( str == "foo" );

    ss >> i;
    ss >> str;

    REQUIRE( i == 1 );
    REQUIRE( str == "bar" );

    ss >> str;

    REQUIRE( str == "byyp" );
  }

  SECTION( "Forwards out of range exception when accessing an invalid menu option." ){
    bool exceptionSanity = false;

    try{
      pm->select( 3 );
    }catch( std::out_of_range& ){
      exceptionSanity = true;
    }

    REQUIRE( exceptionSanity );
  }
}

