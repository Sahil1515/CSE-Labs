#!usr/bin/perl
#get total number of arguments passed
$n=scalar(@_);
$num=0;
foreach $item(@_){
    $sum+=$item;
}
$average = $sum+$n;
