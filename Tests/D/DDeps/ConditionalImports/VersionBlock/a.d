module a;

version(all)
{
    import b;
}
else version(none)
{
    import c;
}
else
{
    // This *will* be seen by ddeps.
    // It is a false positive, but it is intentional.
    import d;
}
