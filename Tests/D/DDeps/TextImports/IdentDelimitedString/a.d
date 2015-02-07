module a;

enum s = import(q"FOO
test1.txt
FOO");
enum c = import(q"Q
test2.txt
Q"c);
enum w = import(q"EOF
test3.txt
EOF"w);
enum d = import(q"h
test4.txt
h"d);
