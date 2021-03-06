#!/bin/bash

CACHED=no
if [ x"$CACHED" = x"no" ]; then
rm -f LAPACK_EIG_LIST LAPACK_EIG_LIST_  LAPACK_EIG_LIST__
echo "sed \\" > LAPACK_EIG_LIST
echo "-e 's///g'" >> LAPACK_EIG_LIST__

FILES_SUBSET=`ls ~/mplapack/external/lapack/work/internal/lapack-3.9.1/TESTING/EIG/{a,d,z,i,x}*.{f,F}`

for _file in $FILES_SUBSET; do
oldfilename=`basename $_file | sed -e 's/\.f$//' -e 's/\.F$//'` 
oldfilenameUP=`basename $_file | sed -e 's/\.f$//' -e 's/\.F$//' | tr a-z A-Z`
newfilename=`basename $_file | sed -e 's/^dzsum1/RCsum1/g' -e 's/^zdscal/CRscal/g' -e 's/^zdrot/CRrot/g' -e 's/^dcabs/RCabs/g' -e 's/^dzasum/RCasum/g' -e 's/^dznrm2/RCnrm2/g' | sed -e 's/^d/R/' -e 's/^z/C/' -e 's/^a/A/'  -e 's/^id/iR/' -e 's/^iz/iC/' -e 's/^ila/iMla/' -e 's/^ip/iMp/' -e 's/\.f$//' -e 's/\.F$//'`
echo "-e 's/$oldfilename/$newfilename/g' \\" >> LAPACK_EIG_LIST_
echo "-e 's/$oldfilenameUP/$newfilename/g' \\" >> LAPACK_EIG_LIST_
done
cat LAPACK_EIG_LIST_ | sort -r > LAPACK_EIG_LIST___
mv LAPACK_EIG_LIST___  LAPACK_EIG_LIST_
cat LAPACK_EIG_LIST LAPACK_EIG_LIST_  LAPACK_EIG_LIST__ > ll
mv ll LAPACK_EIG_LIST
rm LAPACK_EIG_LIST_*
else
cp ~/mplapack/misc/LAPACK_EIG_LIST .
fi

cp ~/mplapack/misc/BLAS_LIST .
cp ~/mplapack/misc/LAPACK_LIST .

for _file in $FILES_SUBSET ; do
perl -i.bk -pe 's/[^[:ascii:]]//g;' $_file
bash ~/mplapack/misc/fable_convert_lapack.sh $_file
oldfilename=`basename $_file | sed -e 's/\.f$//' -e 's/\.F$//'`
newfilename=`basename $_file | sed -e 's/^dzsum1/RCsum1/g' -e 's/^zdscal/CRscal/g' -e 's/^zdrot/CRrot/g' -e 's/^dcabs/RCabs/g' -e 's/^dzasum/RCasum/g' -e 's/^dznrm2/RCnrm2/g' | sed -e 's/^d/R/' -e 's/^z/C/' -e 's/^id/iR/' -e 's/^a/A/g' -e 's/^iz/iC/' -e 's/^ila/iMla/' -e 's/^ip/iMp/' -e 's/\.f$//' -e 's/\.F$//'`
if [ ! -e $newfilename ]; then
cat ${oldfilename}.cpp | bash BLAS_LIST | bash LAPACK_EIG_LIST | bash LAPACK_LIST | sed 's/dlamch/Rlamch/g' > ${newfilename}.cpp_
mv ${newfilename}.cpp_  ${newfilename}.cpp
sed -i -e 's/common &cmn, //g' ${newfilename}.cpp
sed -i -e 's/vect = "N";/vect = \'\'N\'';/g' ${newfilename}.cpp
sed -i -e 's/vect = "U";/vect = \'\'U\'';/g' ${newfilename}.cpp
sed -i -e 's/trans = "N";/trans = \'\'N\'';/g' ${newfilename}.cpp
sed -i -e 's/trans = "C";/trans = \'\'C\'';/g' ${newfilename}.cpp
sed -i -e 's/trans = "T";/trans = \'\'T\'';/g' ${newfilename}.cpp
sed -i -e 's/norm = "1";/norm = \'\'1\'';/g' ${newfilename}.cpp
sed -i -e 's/norm = "I";/norm = \'\'I\'';/g' ${newfilename}.cpp
sed -i -e 's/const &/const /g' ${newfilename}.cpp
sed -i -e 's/, a\[/, \&a\[/g' ${newfilename}.cpp
sed -i -e 's/, b\[/, \&b\[/g' ${newfilename}.cpp
sed -i -e 's/, c\[/, \&c\[/g' ${newfilename}.cpp
sed -i -e 's/, d\[/, \&d\[/g' ${newfilename}.cpp
sed -i -e 's/, e\[/, \&e\[/g' ${newfilename}.cpp
sed -i -e 's/, f\[/, \&f\[/g' ${newfilename}.cpp
sed -i -e 's/, h\[/, \&h\[/g' ${newfilename}.cpp
sed -i -e 's/, v\[/, \&v\[/g' ${newfilename}.cpp
sed -i -e 's/, u\[/, \&u\[/g' ${newfilename}.cpp
sed -i -e 's/, q\[/, \&q\[/g' ${newfilename}.cpp
sed -i -e 's/, t\[/, \&t\[/g' ${newfilename}.cpp
sed -i -e 's/, w\[/, \&w\[/g' ${newfilename}.cpp
sed -i -e 's/, x\[/, \&x\[/g' ${newfilename}.cpp
sed -i -e 's/, z\[/, \&z\[/g' ${newfilename}.cpp
sed -i -e 's/, ab\[/, \&ab\[/g' ${newfilename}.cpp
sed -i -e 's/, ap\[/, \&ap\[/g' ${newfilename}.cpp
sed -i -e 's/, vt\[/, \&vt\[/g' ${newfilename}.cpp
sed -i -e 's/, vr\[/, \&vr\[/g' ${newfilename}.cpp
sed -i -e 's/, vl\[/, \&vl\[/g' ${newfilename}.cpp
sed -i -e 's/, tau\[/, \&tau\[/g' ${newfilename}.cpp
sed -i -e 's/, dum\[/, \&dum\[/g' ${newfilename}.cpp
sed -i -e 's/, cdum\[/, \&cdum\[/g' ${newfilename}.cpp
sed -i -e 's/, ipiv\[/, \&ipiv\[/g' ${newfilename}.cpp
sed -i -e 's/, work\[/, \&work\[/g' ${newfilename}.cpp
sed -i -e 's/, rwork\[/, \&rwork\[/g' ${newfilename}.cpp
sed -i -e 's/, lwork\[/, \&lwork\[/g' ${newfilename}.cpp
sed -i -e 's/, iwork\[/, \&iwork\[/g' ${newfilename}.cpp
sed -i -e 's/, x11\[/, \&x11\[/g' ${newfilename}.cpp
sed -i -e 's/, x12\[/, \&x12\[/g' ${newfilename}.cpp
sed -i -e 's/, x21\[/, \&x21\[/g' ${newfilename}.cpp
sed -i -e 's/, x22\[/, \&x22\[/g' ${newfilename}.cpp
sed -i -e 's/ == "1"/Mlsame( , "1")/g' ${newfilename}.cpp
sed -i -e 's/ == "0"/Mlsame( , "0")/g' ${newfilename}.cpp

fi

cat << EOF > insert_eig.txt

#include <fem.hpp> // Fortran EMulation library of fable module
using namespace fem::major_types;
using fem::common;

#include <mplapack_matgen.h>
#include <mplapack_eig.h>

#include <mplapack_debug.h>
EOF

sed -i "/#include <mplapack.h>/r insert_eig.txt" ${newfilename}.cpp  #GNU sed only
rm -f ${oldfilename}.cpp
done
rm insert_eig.txt