set xlabel font "Helvetica,20"
set ylabel font "Helvetica,20"
set key font "Helvetica,20"
set title font "Helvetica,24"
set title "Raxpy performance on AMD Ryzen Threadripper 3970X"
set xlabel "Dimension"
set ylabel "MFLOPS"
set terminal postscript eps color enhanced

plot \
"log.Raxpy._Float128"       using 1:2 title '\_Float128'             with lines linewidth 6, \
"log.Raxpy._Float128_opt"   using 1:2 title '\_Float128 (OpenMP)'    with lines linewidth 6, \
"log.Raxpy._Float64x"       using 1:2 title '\_Float64x'             with lines linewidth 6, \
"log.Raxpy._Float64x_opt"   using 1:2 title '\_Float64x (OpenMP)'    with lines linewidth 6, \
"log.Raxpy.dd"              using 1:2 title 'double double'          with lines linewidth 6, \
"log.Raxpy.dd_opt"          using 1:2 title 'double double (OpenMP)' with lines linewidth 6, \
"log.Raxpy.double"          using 1:2 title 'double'                 with lines linewidth 6, \
"log.Raxpy.double_opt"	    using 1:2 title 'double (OpenMP)'        with lines linewidth 6
