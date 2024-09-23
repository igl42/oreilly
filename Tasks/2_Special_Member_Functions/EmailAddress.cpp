/**************************************************************************************************
*
* \file EmailAddress.cpp
* \brief C++ Training - Advanced Example for Copy and Move Operations
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the special member functions for the given 'EmailAddress' class. Note that
*       'EmailAddress' must contain a valid email address at all times!
*
**************************************************************************************************/


//---- <EmailAddress.h> ---------------------------------------------------------------------------

#include <algorithm>
#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>

template< typename RandomAccessIt >
constexpr bool is_valid_email_part( RandomAccessIt first, RandomAccessIt last )
{
   auto const isalnum_or_dots_or_underscore =
      []( char a ){ return isalnum(a) || a == '.' || a == '_'; };

   auto const adjacent_dots =
      []( char a, char b ){ return a == '.' && b == '.'; };

   return first != last &&
          std::all_of( first, last, isalnum_or_dots_or_underscore ) &&
          std::adjacent_find( first, last, adjacent_dots ) == last &&
          *first != '.' &&
          *(last-1) != '.';
}

template< typename RandomAccessIt >
constexpr bool is_email_address( RandomAccessIt first, RandomAccessIt last )
{
   auto const firstAt = std::find( first, last, '@' );
   auto const firstDotAfterAt = std::find( firstAt, last, '.' );

   return firstAt != last &&
          firstDotAfterAt != last &&
          is_valid_email_part( first, firstAt ) &&
          is_valid_email_part( firstAt+1, firstDotAfterAt ) &&
          is_valid_email_part( firstDotAfterAt+1, last );

}

class EmailAddress
{
 public:
   explicit EmailAddress( std::string address )
      : address_{std::move(address)}
   {
      if( !is_valid() ) {
         throw std::invalid_argument( "Invalid email address" );
      }
   }

   // TODO: Implement the special member functions.

   std::string const& value() const { return address_; }
   bool is_valid() const { return is_email_address( begin(address_), end(address_) ); }

 private:
   std::string address_;
};

std::ostream& operator<<( std::ostream& os, EmailAddress const& address )
{
   return os << address.value() << " (" << ( address.is_valid() ? "valid" : "INVALID" ) << ')';
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <EmailAddress.h>
#include <cstdlib>
#include <iostream>


int main()
{
   EmailAddress address1{ "klaus.iglberger@gmx.de" };
   std::cout << "Original email address: " << address1 << "\n\n";

   EmailAddress address2 = address1;
   std::cout << "Original email after copy construction: " << address1 << "\n"
             << "New email after copy construction: " << address2 << "\n\n";

   EmailAddress address3 = std::move(address1);
   std::cout << "Original email after move construction: " << address1 << "\n"
             << "New email after move construction: " << address3 << "\n\n";

   address2 = address1;
   std::cout << "Original email address after copy assignment: " << address1 << "\n"
             << "Resulting email address after copy assignment: " << address2 << "\n\n";

   address2 = std::move(address1);
   std::cout << "Original email address after move assignment: " << address1 << "\n"
             << "Resulting email address after move assignment: " << address2 << "\n\n";



   // Checking invalid email addresses
   try {
      EmailAddress address{ "" };
      std::cerr << "INVALID EMAIL 1 ACCEPTED!\n";
   }
   catch( std::invalid_argument const& ex ) {}

   try {
      EmailAddress address{ "@gmx.de" };
      std::cerr << "INVALID EMAIL 2 ACCEPTED!\n";
   }
   catch( std::invalid_argument const& ex ) {}

   try {
      EmailAddress address{ "klaus.iglberger@" };
      std::cerr << "INVALID EMAIL 3 ACCEPTED!\n";
   }
   catch( std::invalid_argument const& ex ) {}

   try {
      EmailAddress address{ "klaus.@gmx.de" };
      std::cerr << "INVALID EMAIL 4 ACCEPTED!\n";
   }
   catch( std::invalid_argument const& ex ) {}

   try {
      EmailAddress address{ ".iglberger@gmx.de" };
      std::cerr << "INVALID EMAIL 5 ACCEPTED!\n";
   }
   catch( std::invalid_argument const& ex ) {}

   try {
      EmailAddress address{ "klaus..iglberger@gmx.de" };
      std::cerr << "INVALID EMAIL 6 ACCEPTED!\n";
   }
   catch( std::invalid_argument const& ex ) {}

   try {
      EmailAddress address{ "klaus.iglberger@.de" };
      std::cerr << "INVALID EMAIL 7 ACCEPTED!\n";
   }
   catch( std::invalid_argument const& ex ) {}

   try {
      EmailAddress address{ "klaus.iglberger@gmx." };
      std::cerr << "INVALID EMAIL 8 ACCEPTED!\n";
   }
   catch( std::invalid_argument const& ex ) {}

   try {
      EmailAddress address{ "klaus.iglberger@gmx..de" };
      std::cerr << "INVALID EMAIL 9 ACCEPTED!\n";
   }
   catch( std::invalid_argument const& ex ) {}

   try {
      EmailAddress address{ "klaus.iglberger@@gmx.de" };
      std::cerr << "INVALID EMAIL 10 ACCEPTED!\n";
   }
   catch( std::invalid_argument const& ex ) {}

   try {
      EmailAddress address{ "klaus@iglberger@gmx.de" };
      std::cerr << "INVALID EMAIL 11 ACCEPTED!\n";
   }
   catch( std::invalid_argument const& ex ) {}

   return EXIT_SUCCESS;
}
