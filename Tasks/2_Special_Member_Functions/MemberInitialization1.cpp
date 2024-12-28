/**************************************************************************************************
*
* \file MemberInitialization1.cpp
* \brief C++ Training - Example for the initialization of data members
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: What is the initial value of the three data members 'i', 's', and 'pi'?
*
**************************************************************************************************/

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>


struct Widget
{
   int i;
   std::string s;
   int* pi;
};


int main()
{
   Widget w;

   std::cout << "\n w.i = " << w.i << ", w.s = " << std::quoted(w.s) << ", w.pi = " << w.pi << "\n\n";

   return EXIT_SUCCESS;
}

