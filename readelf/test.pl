#!/usr/bin/env perl

`make` if(-e read_header);
my @test_list = glob("test/*");

foreach my $test (@test_list)
{
  print "\n\n".$test . ":\n";
  my @result = `./read-elf -a $test 2> /dev/null`;
  foreach my $output (@result)
  {
    print $output;
  }
}