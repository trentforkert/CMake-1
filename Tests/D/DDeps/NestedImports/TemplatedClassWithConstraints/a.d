module a;

class Foo
{

}

class Bar(T) if( is( T : Foo ) )
{
    import b;
}
