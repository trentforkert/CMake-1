module a;

int method1(int x)
body
{
    import b;
    return x;
}

int method2(int x)
in
{
    import c;
    assert(x != 0);
}
body
{
    import d;
    return x + 1;
}


int method3(int x)
out(result)
{
    import e;
    assert(result != 0);
}
body
{
    import f;
    return x + 1;
}

int method4(int x)
in
{
    import g;
    assert(x != 0);
}
out(result)
{
    import h;
    assert(result != 0);
}
body
{
    import i;
    return x + 1;
}
