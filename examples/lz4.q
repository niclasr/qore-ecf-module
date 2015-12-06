#!/usr/bin/env qore
# copyright: public domain

%requires lz4

sub main() {
if (system("lz4 --content-size --no-frame-crc data")) {
   printf("lz4 not found\n");
   return 0;
}
our File $writeuncomp();
our File $writecomp();

$writeuncomp.open2("qore.data", O_CREAT | O_WRONLY);
$writecomp.open2("qore.data.lz4", O_CREAT | O_WRONLY);

our binary $uncomporg = ReadOnlyFile::readBinaryFile("data");
our binary $compqore = lz4frame_compress($uncomporg, 0);
$writecomp.write($compqore);

our binary $comporg = ReadOnlyFile::readBinaryFile("data.lz4");
our binary $uncompqore = lz4frame_decompress($comporg);
$writeuncomp.write($uncompqore);

$writecomp.close();
$writeuncomp.close();

system("diff -s data qore.data");
system("diff -s data.lz4 qore.data.lz4");
}

main();
