#!/usr/bin/env perl

`make` if(-e read_header);
my @test_list = glob("test/*");

foreach my $test (@test_list)
{
  print "\n\n".$test . ":\n";
  my @result = `./read_header $test`;
  foreach my $output (@result)
  {
    print $output;
  }
}