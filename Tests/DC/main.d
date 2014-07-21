module main;

import std.exception;

// From clib.c
extern(C) int method();

void main()
{
  enforce(method() == 1);
}
