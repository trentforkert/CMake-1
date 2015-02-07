module a;

class Foo
{
}

class Bar(T)
    if( is( T : Foo ) )
    : T
{
    import b;
}

class Bar(T)
    : T
    if( !is( T : Foo ) )
{
    import c;
}
