for i in 2x3zu1x6 Signalsimulator Weichensimulator-45links Weichensimulator-45rechts Weichensimulator-links Weichensimulator-rechts
do
    echo "==== $i ======"
    (cd $i/plot && \
    rm -f ../$i.zip && \
    zip ../$i.zip * )
done
