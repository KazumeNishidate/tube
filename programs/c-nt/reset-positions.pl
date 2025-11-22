#!/usr/bin/perl
#
my $fname1 = $ARGV[0];
my $fname2 = $ARGV[1];
open(POSCAR, "$fname1") || die "I can't open $fname1. \n";
open(POSNEW, "> $fname2") || die "I can't open $fname2. \n";

$LX = 50.0;   
$LY = 50.0;

@POS = <POSCAR>;
@atom = split(/\^|\s+/, ' '.$POS[6]);

# total number of atoms
$atomn=$atom[1]+$atom[2]+$atom[3]+$atom[4]+$atom[5]+$atom[6]+$atom[7];
print ">>> total number of atoms = $atomn \n";

$offset = 8;
print POSNEW "$POS[0]"; print POSNEW "$POS[1]";
print POSNEW " $LX.0   0.0    0.0   \n";
print POSNEW "  0.0  $LY.0    0.0   \n";
print POSNEW "$POS[4]";
print POSNEW "$POS[5]";
print POSNEW "$POS[6]"; print POSNEW "$POS[7]"; 

$gx=0.0; $gy=0.0;
my @rx, @ry, @rz;
for($i=0;$i<$atomn;$i++){
    @tmp=split(/\^|\s+/,$POS[$i+$offset]);
    $rx[$i] = $tmp[1]; $ry[$i] = $tmp[2]; $rz[$i] = $tmp[3];
    $gx += $rx[$i];  # evaluate the center of gravity
    $gy += $ry[$i];
}
$gx /= $atomn;
$gy /= $atomn;
$gxs = $LX/2.0-$gx;  # reset the center of gravity
$gys = $LY/2.0-$gy;

for($i=0;$i<$atomn;$i++){
    $rx[$i] += $gxs;
    $ry[$i] += $gys;    
    write POSNEW;
}


format POSNEW =
 @#.##########   @#.##########   @#.##########      @<< @<< @<<
$rx[$i],   $ry[$i],   $rz[$i],   $tmp[4], $tmp[4], $tmp[4]
.
