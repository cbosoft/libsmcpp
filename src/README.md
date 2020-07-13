# libsmcpp

Apple SMC interop library in C++.

Strongly borrows from:
  - https://github.com/beltex/libsmc

# Relevance

I noticed libsmc wasn't working on my MBP2020, so I dove it to find out what
was wrong. (It turned out, Apple changed one of the underlying datatypes from
fixed point to floating point.) I decided to rewrite in C++ for no good reason
other than I like C++ and fancied a wee project.