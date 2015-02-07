module a;

class Foo
{
}

class Bar : Foo
{
    import b;
}

// protection specifier on inheritance is deprecated, but still needs to parse
class Wiz : public Foo
{
    import c;
}
