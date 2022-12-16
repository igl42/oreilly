/**************************************************************************************************
*
* \file RefactorSingleton_2.cpp
* \brief C++ Training - Programming Task for the Singleton Design Pattern
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Assumptions: The 'Logger', the 'CreditCardProcessor' and the 'Database' all require the
*              guarantee that there is only a single instance. Hence they are implemented by
*              means of the 'Singleton' design pattern.
*
* Task: Refactor the code example such that the following functions become testable (i.e. do
*       not depend on a specific class instance anymore):
*
*         - Database::getAccount()
*         - Database::commitAccount()
*         - CreditCardProcessor::charge()
*         - CreditCard::charge()
*
**************************************************************************************************/

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include "Singleton.h"


//---- <Logger.h> ---------------------------------------------------------------------------------

class Logger
   : private Singleton<Logger>
{
 public:
   using Singleton<Logger>::instance;

   template< typename T >
   void log( T&& t ) const;

 private:
   Logger() = default;

   BEFRIEND_SINGLETON;
};

template< typename T >
Logger& operator<<( Logger& logger, const T& t )
{
   logger.log( t );
   return logger;
}


//---- <Logger.cpp> -------------------------------------------------------------------------------

template< typename T >
void Logger::log( T&& t ) const
{
   std::cout << std::forward<T>( t );
}


//---- <NullLogger.h> -----------------------------------------------------------------------------

class NullLogger
{};

template< typename T >
const NullLogger& operator<<( const NullLogger& logger, const T& t )
{
   return logger;
}


//---- <LoggerProxy.h> ----------------------------------------------------------------------------

struct LoggerProxy
{
#ifdef ENABLE_LOGGING
   Logger& logger_{ Logger::instance() };
#else
   NullLogger logger_{};
#endif
};

template< typename T >
const LoggerProxy& operator<<( const LoggerProxy& logger, const T& t )
{
   logger.logger_ << t;
   return logger;
}


//---- <Logging.h> --------------------------------------------------------------------------------

decltype(auto) logger()
{
   return LoggerProxy{};
}


//---- <Person.h> ---------------------------------------------------------------------------------

struct Person
{
 public:
   Person( std::string first, std::string last )
      : firstname_( std::move(first) )
      , lastname_ ( std::move(last) )
   {}

   const std::string& firstname() const { return firstname_; }
   const std::string& lastname()  const { return lastname_; }

 private:
   std::string firstname_{};
   std::string lastname_{};
};


//---- <Account.h> --------------------------------------------------------------------------------

struct Account
{
 public:
   Account( Person owner, size_t number, size_t balance = 0UL )
      : owner_  ( owner )
      , number_ ( number )
      , balance_( balance )
   {}

   const Person& owner  () const noexcept { return owner_; }
   size_t        number () const noexcept { return number_; }
   size_t        balance() const noexcept { return balance_; }

   bool authorize() const { /* Authorizing the access; */ return true; }
   void increaseBalance( size_t amount ) noexcept { balance_ += amount; }
   void decreaseBalance( size_t amount ) noexcept { balance_ -= amount; };

 private:
   Person owner_;
   size_t number_{};
   size_t balance_{};
};


//---- <CreditCard.h> -----------------------------------------------------------------------------

class CreditCard
{
 public:
   CreditCard( size_t number )
      : number_( number )
   {}

   size_t number() const noexcept { return number_; }

 private:
   size_t number_{};
};


//---- <AbstractDatabase.h> -----------------------------------------------------------------------

class AbstractDatabase
{
 public:
   virtual ~AbstractDatabase() = default;

   virtual const Account& getAccount( size_t accountNumber ) = 0;
   virtual bool           commitAccount( const Account& account ) = 0;
   virtual size_t         cardToAccount( size_t cardNumber ) = 0;
};


//---- <DataBase.h> -------------------------------------------------------------------------------

class Database
   : private Singleton<Database, Logger>
{
 public:
   using Singleton<Database,Logger>::instance;

   const Account& getAccount( size_t accountNumber );
   bool           commitAccount( const Account& account );
   size_t         cardToAccount( size_t cardNumber );

 private:
   Database();

   std::vector<Account> accounts_{};
   std::map<size_t,size_t> cards_{};

   BEFRIEND_SINGLETON;
};


//---- <DatabaseAdaptor.h> ------------------------------------------------------------------------

class DatabaseAdaptor
   : public AbstractDatabase
{
 public:
   virtual ~DatabaseAdaptor() = default;

   const Account& getAccount( size_t accountNumber ) override
   {
      return Database::instance().getAccount( accountNumber );
   }

   bool commitAccount( const Account& account ) override
   {
      return Database::instance().commitAccount( account );
   }

   size_t cardToAccount( size_t cardNumber ) override
   {
      return Database::instance().cardToAccount( cardNumber );
   }
};


//---- <AbstractCreditCardProcessor.h> ------------------------------------------------------------

class AbstractCreditCardProcessor
{
 public:
   virtual ~AbstractCreditCardProcessor() = default;

   virtual bool charge( CreditCard& card, size_t amount, AbstractDatabase& database ) = 0;
};


//---- <CreditCardProcessor.h> --------------------------------------------------------------------

class CreditCardProcessor
   : private Singleton<CreditCardProcessor, Logger>
{
 public:
   using Singleton<CreditCardProcessor,Logger>::instance;

   bool charge( CreditCard& card, size_t amount );
   bool charge( CreditCard& card, size_t amount, AbstractDatabase& database );

 private:
   CreditCardProcessor() = default;

   BEFRIEND_SINGLETON;
};


//---- <CreditCardProcessorAdaptor.h> -------------------------------------------------------------

class CreditCardProcessorAdaptor
   : public AbstractCreditCardProcessor
{
 public:
   virtual ~CreditCardProcessorAdaptor() = default;

   bool charge( CreditCard& card, size_t amount, AbstractDatabase& database ) override
   {
      return CreditCardProcessor::instance().charge( card, amount, database );
   }
};


//---- <DataBase.cpp> -----------------------------------------------------------------------------

Database::Database()
{
   accounts_.push_back( Account{ Person{ "Homer"     , "Simpson"   }, 110,     1100 } );
   accounts_.push_back( Account{ Person{ "Marge"     , "Simpson"   }, 112,    10300 } );
   accounts_.push_back( Account{ Person{ "Montgomery", "Burns"     }, 841, 12408730 } );
   accounts_.push_back( Account{ Person{ "Jeff"      , "Albertson" }, 371,     5710 } );
   accounts_.push_back( Account{ Person{ "Ned"       , "Flanders"  }, 666,    57910 } );

   cards_.insert( std::make_pair( 1234'5678'9012'3456, 110 ) );
   cards_.insert( std::make_pair( 5970'4560'3421'0001, 112 ) );
   cards_.insert( std::make_pair( 5490'3420'1120'7799, 841 ) );
   cards_.insert( std::make_pair( 9494'1234'8765'0040, 371 ) );
   cards_.insert( std::make_pair( 1357'4937'6429'4005, 666 ) );
}

const Account& Database::getAccount( size_t accountNumber )
{
   logger() << "Database: Searching for account for credit card " << accountNumber << '\n';

   const auto pos =
      std::find_if( begin(accounts_), end(accounts_), [accountNumber]( const Account& account ) {
         return account.number() == accountNumber;
      } );

   if( pos != end(accounts_) ) {
      logger() << "Database: Search successful\n";
      return *pos;
   }
   else {
      logger() << "Database: Search failed\n";
      throw std::invalid_argument( "Invalid account number" );
   }
}

bool Database::commitAccount( const Account& account )
{
   logger() << "Database: Committing the account number " << account.number() << '\n';

   const auto pos =
      std::find_if( begin(accounts_), end(accounts_), [accountNumber=account.number()]( const Account& account ) {
         return account.number() == accountNumber;
      } );

   if( pos != end(accounts_) ) {
      logger() << "Database: Changing account details for account " << account.number() << '\n';
      *pos = account;
   }
   else {
      logger() << "Database: Adding new account " << account.number() << '\n';
      accounts_.push_back( account );
   }

   return true;
}

size_t Database::cardToAccount( size_t cardNumber )
{
   const auto pos = cards_.find( cardNumber );

   if( pos == cards_.end() ) {
      throw std::invalid_argument( "Invalid credit card number" );
   }

   return pos->second;
}


//---- <CreditCardProcessor.cpp> ------------------------------------------------------------------

bool CreditCardProcessor::charge( CreditCard& card, size_t amount )
{
   DatabaseAdaptor database{};

   return charge( card, amount, database );
}

bool CreditCardProcessor::charge( CreditCard& card, size_t amount, AbstractDatabase& database )
{
   logger() << "CreditCardProcessor: Charging " << amount << " on credit card number " << card.number() << '\n';

   const size_t accountNumber = database.cardToAccount( card.number() );

   try
   {
      Account account( database.getAccount( accountNumber ) );

      logger() << "CreditCardProcessor: Old balance: " << account.balance() << '\n';

      logger() << "CreditCardProcessor: Authorizing account access...\n";

      if( account.authorize() ) {
         logger() << "CreditCardProcessor: Authorization successful\n";
      }
      else {
         logger() << "CreditCardProcessor: Authorization failed\n";
         return false;
      }

      account.decreaseBalance( amount );

      if( database.commitAccount( account ) ) {
         logger() << "CreditCardProcessor: Transaction committed\n";
      }
      else {
         logger() << "CreditCardProcessor: Transaction failed\n";
         return false;
      }

      logger() << "CreditCardProcessor: New balance: " << account.balance() << '\n';
   }
   catch( std::invalid_argument& ex )
   {
      logger() << "CreditCardProcessor: No matching account found in database (" << ex.what() << ")\n";
      return false;
   }

   return true;
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   CreditCard c( 1234'5678'9012'3456 );

   try {
      CreditCardProcessor& ccp( CreditCardProcessor::instance() );
      ccp.charge( c, 100 );
   }
   catch( std::invalid_argument& ex )
   {
      std::cout << "Invalid credit card number\n";
   }

   return EXIT_SUCCESS;
}
