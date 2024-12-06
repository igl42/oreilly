#==================================================================================================
#
#  Makefile for chapter "C++ Software Design"
#
#  Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================


# Build rules
default:
	@$(MAKE) --no-print-directory -C ./Bridge
	@$(MAKE) --no-print-directory -C ./External_Polymorphism
	@$(MAKE) --no-print-directory -C ./Motivation
	@$(MAKE) --no-print-directory -C ./Prototype
	@$(MAKE) --no-print-directory -C ./Strategy
	@$(MAKE) --no-print-directory -C ./Type_Erasure
	@$(MAKE) --no-print-directory -C ./Visitor


# Cleanup
clean:
	@$(MAKE) --no-print-directory -C ./Bridge clean
	@$(MAKE) --no-print-directory -C ./External_Polymorphism clean
	@$(MAKE) --no-print-directory -C ./Motivation clean
	@$(MAKE) --no-print-directory -C ./Prototype clean
	@$(MAKE) --no-print-directory -C ./Strategy clean
	@$(MAKE) --no-print-directory -C ./Type_Erasure clean
	@$(MAKE) --no-print-directory -C ./Visitor clean


# Setting the independent commands
.PHONY: default clean
