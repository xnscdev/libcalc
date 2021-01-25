#!/bin/sh

[ -z "$AUTORECONF" ] && AUTORECONF=autoreconf
[ -z "$GTKDOCIZE" ] && GTKDOCIZE=gtkdocize

$AUTORECONF --version >/dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "$AUTORECONF not working or not found. Please install" 2>&1
    echo "GNU autoconf or set the AUTORECONF environment variable" 2>&1
    echo "to a working autoreconf script." 2>&1
    exit 1
fi

$GTKDOCIZE --version >/dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "$GTKDOCIZE not working or not found. Please install" 2>&1
    echo "Gtk-doc or set the GTKDOCIZE environment variable" 2>&1
    echo "to a working gtkdocize script." 2>&1
    exit 1
fi

mkdir -p -v build-aux m4
$GTKDOCIZE --copy
$AUTORECONF --force --install --verbose
[ -z "$NO_CONFIGURE" ] && ./configure $CONFIGURE_ARGS
