#!/usr/bin/gnuplot
# This is obviously intended for Linux 

reset

set terminal epslatex size 15.00cm, 8.00cm color lw 1 standalone colortext font 10 \
	header '\usepackage{grffile} \usepackage{amssymb}'

set xtics
set ytics
set ylabel '$|r|/|b|$'
# set xlabel 'global iter. count, $[50\times 128=6400]$ lcl. iter./glb. iter.'
set xlabel 'iteration'

set format y '$10^{%+03T}$'
# 
# set logscale y

set xrange [0:8000]
set yrange [1e-10:1e0]

infile = 'force.dat'

outfile = 'force'

set key spacing 2
set key enhanced
set key top right

# set xtics 1
# set grid x lw 3 dashtype 8

set output outfile.'.tex'

# set format y '$10^{%T}$'
set logscale y
# set logscale x

plot \
  'no_ml.dat' using 2:9 with points ps 0.4 pt 7 title 'no ML', \
  'ml_0.940.dat' using 2:9 with points ps 0.4 pt 7 title '$\mu=0.940$', \
  'ml_0.960.dat' using 2:9 with points ps 0.4 pt 7 title '$\mu=0.960$'

set output # Need to close the output file before latex can work with it

system 'pdflatex -shell-escape -interaction=batchmode '.outfile.\
	'.tex > /dev/null; rm '.outfile.'-inc.eps '.outfile.\
		'-inc-eps-converted-to.pdf '.outfile.'.tex $(basename '.\
			outfile.').log $(basename '.outfile.').aux'\

system 'evince '.outfile.'.pdf'

