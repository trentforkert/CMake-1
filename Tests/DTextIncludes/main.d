module main;

import std.stdio;
import std.exception;

// from foo.c
extern(C) int method();

void main()
{
  // Simplest quine
  writeln(import("main.d"));

  enforce(method() == 42);
}
