#!/usr/bin/env qore

%requires magic

my string $filename = shift $ARGV;


my Magic $m();

$m.setFlags(MAGIC_MIME);

printf("\n::file test\n");
printf("path mime: %N\n", $m.file($filename));


# file read
my File $f();
my File $b();
$f.open2($filename);
$b.open2($filename);

printf("\n::buffer test\n");
my string $str = $f.read(-1);
my binary $bin = $b.readBinary(-1);
printf("string buffer: %N\n", $m.buffer($str));
printf("binary buffer: %N\n", $m.buffer($bin));


