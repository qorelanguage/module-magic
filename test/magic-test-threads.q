#!/usr/bin/env qore

%requires magic

sub test() {
    while ($run) {
        $m.buffer('lorem ipsum');
    }
}

our Magic $m();

$m.setFlags(MAGIC_MIME);
our $run = True;

for (my int $i = 0; $i < 11; $i++)
    background test();

sleep(10);

$run = False;

