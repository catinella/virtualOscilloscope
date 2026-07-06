#!/usr/bin/perl

use strict;
use warnings;

my $file = $ARGV[0];
my $scale = $ARGV[1];
my @row = ();

open(FH, "<$file") or die $!;
while (<FH>) {
	@row = split(",");
	for (my $t=0; $t < scalar(@row); $t++) {
		if ($t == (scalar(@row) - 1)) {
			printf("%f", $row[$t] * $scale);
		} else {
			printf("%f,", $row[$t] * $scale);
		}
	}
	printf("\n");
}
close(FH);
