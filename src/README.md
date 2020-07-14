# libsmcpp

Apple SMC interop library in C++.

A re-implementation of https://github.com/beltex/libsmc.

Given the closed source nature of Apple's SMC, there is a lot of guess work
involved in creating something like this. There are a bunch of resources
available online; I'll collect here the most useful ones I find. beltex/libsmc 
has a bunch so start with:

Sources:
  - https://www.insanelymac.com/forum/topic/328814-smc-keys-knowledge-database/
  - https://stackoverflow.com/questions/22160746/fpe2-and-sp78-data-types

# Relevance

I noticed libsmc wasn't working on my MBP2020, so I dove it to find out what
was wrong. (It turned out, Apple changed one of the underlying datatypes from
fixed point to floating point.) I decided to rewrite in C++ for no good reason
other than I like C++ and fancied a wee project.