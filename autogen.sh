#!/bin/sh

[ -z "$AUTORECONF" ] && AUTORECONF=autoreconf

$AUTORECONF --version 2>/dev/null
if test "$?" -ne 0; then
    echo "$AUTORECONF not working or not found. Please install" 2>&1
    echo "GNU autoconf or set the AUTORECONF environment variable" 2>&1
    echo "to an working autoreconf script." 2>&1
    exit 1
fi

mkdir -p -v build-aux m4
$AUTORECONF --force --install --verbose
[ -z "$NO_CONFIGURE" ] && ./configure $CONFIGURE_ARGS
