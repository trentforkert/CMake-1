module a;

// A correct D parser stops after an __EOF__ token
import b;

__EOF__
// This should not even get parsed
import c;
