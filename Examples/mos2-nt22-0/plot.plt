# set term pdfcairo enhanced size 4in, 3in
# set output "mos2-nt22-0.pdf"

set tics font "Times New Roman,18"  
set xlabel font "Times New Roman,18"
set ylabel font "Times New Roman,18"
set key font "Times New Roman,18"   

set lmargin 15
set rmargin 1
set tmargin 5
set bmargin 5

set  size   0.6, 1.0
set  origin 0, 0

set title "MoS_2 NT (22,0)"
set title font"Arial,18"

## *** Plot range ***
    x1=   0.0000
    x2=   3.6530
y1=-5
y2= 5
set xrange [0:x2]
set yrange [y1:y2]

ef=-0.7240

set xzeroaxis
set grid x

set ylabel "E-E_F (eV)" offset -1,0
set xtics ("{/Symbol G}" x1, "Z" x2) offset 0,-1

unset key
plot "swnt.band.gnu" u 1:($2-ef) w l lw 2
unset arrow

pause -1
