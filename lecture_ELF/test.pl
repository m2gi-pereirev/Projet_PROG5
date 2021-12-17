#!/usr/bin/env perl

my @test_list = glob("test/*");

foreach my $test (@test_list)
{
  print $test . ":\n";
  my @result = `./read_header $test`;
  foreach my $output (@result)
  {
    print $output . "\n";
  }
}