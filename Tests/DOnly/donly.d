module donly;
import extra;

import hello;
import world;

import std.stdio;
import std.exception;

int main()
{
  int var = 0;
  enforce(helloFunc() == 2.0);
  enforce(worldFunc() == 1.0);
  writefln("Foo: %s %d", foo, var);
  return 0;
}
