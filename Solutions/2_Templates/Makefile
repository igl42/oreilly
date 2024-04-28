#==================================================================================================
#
#  Makefile for chapter "Templates"
#
#  Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================


# Build rules
default:
	@$(MAKE) --no-print-directory -C ./Class_Templates
	@$(MAKE) --no-print-directory -C ./Concepts
	@$(MAKE) --no-print-directory -C ./Function_Templates
	@$(MAKE) --no-print-directory -C ./Variadic_Templates


# Cleanup
clean:
	@$(MAKE) --no-print-directory -C ./Class_Templates clean
	@$(MAKE) --no-print-directory -C ./Concepts clean
	@$(MAKE) --no-print-directory -C ./Function_Templates clean
	@$(MAKE) --no-print-directory -C ./Variadic_Templates clean


# Setting the independent commands
.PHONY: default clean
