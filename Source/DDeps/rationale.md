DDeps Rationale
===============

The purpose of this document is to explain some of the big-picture design
decisions in DDeps, and the reasoning behind them. It is by no means
comprehensive, and there are cases where source comments will be
needed to properly understand what is going on. However, this document
should complement the source comments and cover things that don't
fit as comments anywhere in the source.

Why DDeps?
----------

First things first, DDeps exists as it does in order to scan dependencies
of D source files for CMake. The way this is done for other languages
is via cmDepends, which puts a parser (or stripped down equivalent)
directly into the CMake binary. However, cmDepends only works for
Makefile-based generators. Ninja-based generators don't (necessarily)
use cmDepends.

Prior to DDeps, D dependency scanning was accomplished by asking the
D compiler directly, as every D compiler currently in existence can
output dependency information. So, cmDependsD would defer to the D
compiler, parse its dependency information and write the Make-style
dependencies that CMake wants. Meanwhile, the way that Ninja (and
the Ninja generator) work meant that this approach would not work
correctly for Ninja. A patch to have Ninja natively support
DMD-style dependencies was written, and rejected from upstream.

The need to do *something* for Ninja and a desire to have faster
parsing then the D compiler is capable of resulted in DDeps,
which is designed as a partial parser, so that it can be faster
than the D compiler, and have this one codebase work for both
Ninja and Makefile generators.

Why Flex/Bison?
---------------

Flex and Bison are used to make maintenance of a fast parser/lexer
easier. They do come with some downsides. For one, they cannot
parse UTF-16 or UTF-32 in a reasonable way, so DDeps only supports
ASCII and UTF-8. D itself doesn't support other non-Unicode encodings.
However, they make it a lot easier to produce fast, portable code.

Why only partially parse?
-------------------------

DDeps is only concerned with the imports. It doesn't care what
your code is/does semantically, only the links between the files.
As such, it only parses enough to be able to (mostly) reliably
determine what the imports are. It actually parses quite a
bit in order to get this information and interpret it correctly.
Memory efficiency is also improved by not keeping track of
identifiers and strings that aren't needed for determining
the dependency information.

Why Caching?
------------

One of the decisions made early in the development of DDeps is
that it would cache its results in order to speed up parsing
of subsequent calls. A lot of my timing tests were on D's standard
library, Phobos, which contains a lot of recursive dependencies.
If these all had to be parsed again for every object, parsing
would take a lot longer. So, a caching system was added so
that DDeps could keep track of what had already been parsed,
and re-parse only when needed.

Why ASCII Delimited Text?
-------------------------

The cache information is stored using ASCII Delimited Text
because there is enough information that needs to be cached that
a one-entry-per line approach would not have worked. Additionally,
things like JSON or CSV would require a significantly more complicated
codebase. ASCII Delimited Text is simple to implement, needs no escaping
if you assume only valid ASCII and UTF-8 strings, and can be parsed
and emitted about as quickly as just reading the file.

Why File-Based Locks?
---------------------

Since the cache data is shared by multiple targets (and objects),
it needs to be locked to prevent concurrent threads in parallel
builds from clobbering one another. A File-Based lock is very
simple to implement, and will only cause problems if DDeps outright
crashes, which, admittedly, is a possibility. On my 2010 MacBookPro,
DDeps usually runs from cache in about 5 milliseconds, even on
moderately sized codebases. That is fast enough that I don't think
it matters in practice, as the actual code compilation will
typically take much longer than that.

Why a shared cache?
-------------------

The cache is shared so that dependencies can be tracked across multiple
targets. While it could be made per-target, this would not remove
the need for the lock, as Ninja calls DDeps per-object. Those
parallel DDeps instances could still clobber each other if locks
were not in place. Sharing the cache simply reduces the overall
amount of parsing that needs to be done.

