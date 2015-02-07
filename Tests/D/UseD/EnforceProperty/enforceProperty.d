module enforceProperty;

import std.exception;

struct Foo
{
  @property int x() { return 42; }
  int y() { return 13; }
}

// This will all pass iff property semantics are enforced
void checkProperties()
{
  // Property semantics are broken on 2.056 and older
  static if(__VERSION__ > 2056)
  {
    Foo f;
    enforce(f.x == 42);
    enforce(f.y() == 13);

    // With property semantics, f.y needs parens
    static assert(!__traits(compiles, f.y == 13));
  }
}
