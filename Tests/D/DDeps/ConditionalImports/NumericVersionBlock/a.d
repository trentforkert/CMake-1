module a;

version(2)
{
    import c;
}
else
{
    import b;
}
