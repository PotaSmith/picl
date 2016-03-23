#! /bin/sh

test -z "$VERBOSE" && {
   exec > /dev/null 2>&1
   set -x
}

cat >input <<EOF
a := 1
b := 2
c := 3
d := a + b * c
d
EOF

./picl input
./picl -p input

cat >input <<EOF
a := 1
d := a + b * c
EOF
./picl input

cat >input <<EOF
toto := 1
toto
EOF
./picl -s input

