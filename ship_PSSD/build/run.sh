outputNo=${1:-0} # set output 0 to CLI argument, or if not present deafult to 0


output=outputs/output$outputNo.root

if [ -f "outputs/output${outputNo}_t0.root" ] # check if .root files from multithread mode are present
    then 
        if [ -f "$output" ] # check if merged file from same output No is present
            then 
                rm $output
        fi

        hadd $output outputs/output${outputNo}_t*.root # merge multithread .root files into one
        echo Merged into $output

        rm outputs/output${outputNo}_t*.root # remove multithread .root files

        #root "plot.cpp($outputNo)" # plot spectra from merged file
    # elif [ -f "$output" ] # if multithread .root files are not present, but the merged file is, plot
    #     then 
    #         root -l "plot.cpp($outputNo)" 
fi
