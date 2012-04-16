#!/usr/bin/env qore

%requires magic


my Magic $m();
printf("%N\n", $m);

$m.setFlags(0x10);

printf("mime: %N\n", $m.file(shift $ARGV));

