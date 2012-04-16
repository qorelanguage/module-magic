#!/usr/bin/env qore

%requires magic


my Magic $m();

$m.setFlags(MAGIC_MIME);

printf("mime: %N\n", $m.file(shift $ARGV));

