#!/usr/bin/env bash

# Main driver to submit jobs 
# Author SHI Xin <shixin@ihep.ac.cn>
# Created [2016-03-28 Mon 07:58]


usage() {
    printf "NAME\n\tsubmit.sh - Main driver to submit jobs\n"
    printf "\nSYNOPSIS\n"
    printf "\n\t%-5s\n" "./submit.sh [OPTION]" 
    printf "\nOPTIONS\n" 
    printf "\n\t%-9s  %-40s"  "0.1"      "[run data sample for jpsi2invi]" 
    printf "\n\t%-9s  %-40s"  "0.1.1"    "Split data sample with each group 20G"
    printf "\n\t%-9s  %-40s"  "0.1.2"    "Generate Condor jobs on data ---- 1"
    printf "\n\t%-9s  %-40s"  "0.1.3"    "Test for data"
    printf "\n\t%-9s  %-40s"  "0.1.4"    "Submit Condor jobs on data ---- 2"
    printf "\n\t%-9s  %-40s"  "0.1.5"    "Check Condor jobs on data"
    printf "\n\t%-9s  %-40s"  "0.1.6"    "Generate Selection Condor jobs on data ---- 1."
    printf "\n\t%-9s  %-40s"  "0.1.7"    "Test for data event"
    printf "\n\t%-9s  %-40s"  "0.1.8"    "Submit selection Condor jobs on data ---- 2"
    printf "\n\t%-9s  %-40s"  "0.1.9"    "Check Condor jobs on events data"
	printf "\n\t%-9s  %-40s"  "0.1.10"    "Merge event root file on data" 
    printf "\n\t%-9s  %-40s"  "0.1.11"    "Plot summary with data"

    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "0.2"      "[run con3650 data for jpsi2invi]" 
    printf "\n\t%-9s  %-40s"  "0.2.1"   "Split con3650 data sample with each group 20G"
    printf "\n\t%-9s  %-40s"  "0.2.2"    "Generate Condor jobs on con3650 data ---- 1"
    printf "\n\t%-9s  %-40s"  "0.2.3"    "Test for con3650 data"
    printf "\n\t%-9s  %-40s"  "0.2.4"    "Submit Condor jobs on con3650 data ---- 2"
    printf "\n\t%-9s  %-40s"  "0.2.5"    "Check Condor jobs on con3650 data"
    printf "\n\t%-9s  %-40s"  "0.2.6"    "Generate Selection Condor jobs on con3650 data ---- 1."
    printf "\n\t%-9s  %-40s"  "0.2.7"    "Test for con3650 data event"
    printf "\n\t%-9s  %-40s"  "0.2.8"    "Submit selection Condor jobs on con3650 data ---- 2"
    printf "\n\t%-9s  %-40s"  "0.2.9"    "Check Condor jobs on events con3650 data"
	printf "\n\t%-9s  %-40s"  "0.2.10"    "Merge event root file on con3650 data" 
    printf "\n\t%-9s  %-40s"  "0.2.11"    "Plot summary with con3650 data"

    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "0.3"      "[run data sample]" 
    printf "\n\t%-9s  %-40s"  "0.3.2"    "Generate Condor jobs on data for incl ---- 1"
    printf "\n\t%-9s  %-40s"  "0.3.3"    "Test for data for incl"
    printf "\n\t%-9s  %-40s"  "0.3.4"    "Submit Condor jobs on data for incl ---- 2"
    printf "\n\t%-9s  %-40s"  "0.3.5"    "Check Condor jobs on data for incl"
    printf "\n\t%-9s  %-40s"  "0.3.6"    "Generate Selection Condor jobs on data for incl ---- 1."
    printf "\n\t%-9s  %-40s"  "0.3.7"    "Test for data event for incl"
    printf "\n\t%-9s  %-40s"  "0.3.8"    "Submit selection Condor jobs on data for incl ---- 2"
    printf "\n\t%-9s  %-40s"  "0.3.9"    "Check Condor jobs on events data for incl"
	printf "\n\t%-9s  %-40s"  "0.3.10"    "Merge event root file on data for incl" 
    printf "\n\t%-9s  %-40s"  "0.3.11"    "Plot summary with data for incl"

    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "0.4"      "[run data sample for jpsi2lplm]" 
    printf "\n\t%-9s  %-40s"  "0.4.2"    "Generate Condor jobs on data for lplm ---- 1"
    printf "\n\t%-9s  %-40s"  "0.4.3"    "Test for data for lplm"
    printf "\n\t%-9s  %-40s"  "0.4.4"    "Submit Condor jobs on data for lplm ---- 2"
    printf "\n\t%-9s  %-40s"  "0.4.5"    "Check Condor jobs on data for lplm"
    printf "\n\t%-9s  %-40s"  "0.4.6"    "Generate Selection Condor jobs on data for lplm ---- 1."
    printf "\n\t%-9s  %-40s"  "0.4.7"    "Test for data event for lplm"
    printf "\n\t%-9s  %-40s"  "0.4.8"    "Submit selection Condor jobs on data for lplm ---- 2"
    printf "\n\t%-9s  %-40s"  "0.4.9"    "Check Condor jobs on events data for lplm"
	printf "\n\t%-9s  %-40s"  "0.4.10"    "Merge event root file on data for lplm" 
    printf "\n\t%-9s  %-40s"  "0.4.11"    "Plot summary with data for lplm"

    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "0.7"      "[run con3650 data for jpsi2incl]" 
    printf "\n\t%-9s  %-40s"  "0.7.2"    "Generate Condor jobs on con3650 data for incl ---- 1"
    printf "\n\t%-9s  %-40s"  "0.7.3"    "Test for con3650 data for incl"
    printf "\n\t%-9s  %-40s"  "0.7.4"    "Submit Condor jobs on con3650 data for incl ---- 2"
    printf "\n\t%-9s  %-40s"  "0.7.5"    "Check Condor jobs on con3650 data for incl"
    printf "\n\t%-9s  %-40s"  "0.7.6"    "Generate Selection Condor jobs on con3650 data for incl ---- 1."
    printf "\n\t%-9s  %-40s"  "0.7.7"    "Test for con3650 data event for incl"
    printf "\n\t%-9s  %-40s"  "0.7.8"    "Submit selection Condor jobs on con3650 data for incl ---- 2"
    printf "\n\t%-9s  %-40s"  "0.7.9"    "Check Condor jobs on events con3650 data for incl"
	printf "\n\t%-9s  %-40s"  "0.7.10"    "Merge event root file on con3650 data for incl" 

    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "1.1"      "[run on MC sample]"
    printf "\n\t%-9s  %-40s"  "1.1.1"    "Split psi(2S) MC sample with each group 20G"
    printf "\n\t%-9s  %-40s"  "1.1.2"    "Generate Condor jobs on psi(2S) MC sample ---- 1"     
    printf "\n\t%-9s  %-40s"  "1.1.3"    "Test for psi(2S) MC sample"     
    printf "\n\t%-9s  %-40s"  "1.1.4"    "Submit Condor jobs on psi(2S) MC sample ---- 2"     
    printf "\n\t%-9s  %-40s"  "1.1.5"    "Check Condor jobs on psi(2S) MC sample"     
    printf "\n\t%-9s  %-40s"  "1.1.6"    "Generate Selection jobs on psi(2S) MC sample"     
    printf "\n\t%-9s  %-40s"  "1.1.7"    "Test for psi(2S) MC sample event"     
    printf "\n\t%-9s  %-40s"  "1.1.8"    "Submit Selection jobs on psi(2S) MC sample"        
    printf "\n\t%-9s  %-40s"  "1.1.9"    "Check events selection jobs on psi(2S) MC"
    printf "\n\t%-9s  %-40s"  "1.1.10"    "Merge events files on psi(2S) MC"
    printf "\n\t%-9s  %-40s"  "1.1.11"    "Plot summary with data and psi(2S) MC"
	
    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "1.3"      "[run on MC sample for jpsi2incl]"
    printf "\n\t%-9s  %-40s"  "1.3.2"    "Generate Condor jobs on psi(2S) MC sample for incl ---- 1"     
    printf "\n\t%-9s  %-40s"  "1.3.3"    "Test for psi(2S) MC sample for incl"     
    printf "\n\t%-9s  %-40s"  "1.3.4"    "Submit Condor jobs on psi(2S) MC sample for incl ---- 2"     
    printf "\n\t%-9s  %-40s"  "1.3.5"    "Check Condor jobs on psi(2S) MC sample for incl"     
    printf "\n\t%-9s  %-40s"  "1.3.6"    "Generate Selection jobs on psi(2S) MC sample for incl"     
    printf "\n\t%-9s  %-40s"  "1.3.7"    "Test for psi(2S) MC sample event for incl"     
    printf "\n\t%-9s  %-40s"  "1.3.8"    "Submit Selection jobs on psi(2S) MC sample for incl"        
    printf "\n\t%-9s  %-40s"  "1.3.9"    "Check events selection jobs on psi(2S) MC for incl"
    printf "\n\t%-9s  %-40s"  "1.3.10"    "Merge events files on psi(2S) MC for incl"
    printf "\n\t%-9s  %-40s"  "1.3.11"    "Plot summary with data and psi(2S) MC for incl"
        
    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "1.5"      "[run on generated MC sample]"
    printf "\n\t%-9s  %-40s"  "1.5.3"    "Test for generated MC sample"     
    printf "\n\t%-9s  %-40s"  "1.5.4"    "Submit Condor jobs on generated MC sample ---- 2"         
    printf "\n\t%-9s  %-40s"  "1.5.5"    "Check Condor jobs on generated MC sample"     
    printf "\n\t%-9s  %-40s"  "1.5.7"    "Test for generated MC sample event"     
    printf "\n\t%-9s  %-40s"  "1.5.8"    "Submit Selection jobs on generated MC sample"        
    printf "\n\t%-9s  %-40s"  "1.5.9"    "Check events selection jobs on generated MC"
    printf "\n\t%-9s  %-40s"  "1.5.10"    "Merge events files on generated MC"

    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "1.6"      "[run on generated MC sample for incl]"
    printf "\n\t%-9s  %-40s"  "1.6.3"    "Test for generated MC sample for incl"     
    printf "\n\t%-9s  %-40s"  "1.6.4"    "Submit Condor jobs on generated MC sample for incl ---- 2"         
    printf "\n\t%-9s  %-40s"  "1.6.5"    "Check Condor jobs on generated MC sample for incl"     
    printf "\n\t%-9s  %-40s"  "1.6.7"    "Test for generated MC sample event for incl"     
    printf "\n\t%-9s  %-40s"  "1.6.8"    "Submit Selection jobs on generated MC sample for incl"        
    printf "\n\t%-9s  %-40s"  "1.6.9"    "Check events selection jobs on generated MC for incl"
    printf "\n\t%-9s  %-40s"  "1.6.10"    "Merge events files on generated MC for incl"


    printf "\n\n" 
}


if [[ $# -eq 0 ]]; then
    usage
    echo "Please enter your option: "
    read option
else
    option=$1    
fi

case $option in
    
    # --------------------------------------------------------------------------
    #  Data  
    # --------------------------------------------------------------------------

    0.1) echo "Running on data sample..."
	 ;;

    0.1.1) echo "Split data sample with each group 20G ..."
	   ./python/get_samples.py  /bes3fs/offline/data/664p03/psip/dst run/samples/data_664p03_psip.txt 20G
	   # made 633 groups 
	   ;;

    0.1.2) echo "Generate Condor jobs on data ---- 1..." 
	   mkdir -p run/jpsi2invi/job_text/Data12
	   mkdir -p run/jpsi2invi/rootfile
	   cd run/jpsi2invi/gen_script
	   ./make_jobOption_file_Data12_jpsi2invi.sh
	   cd ../job_text/Data12
	   mv jobOptions_jpsi2invi_data_psip_data12-633.txt jobOptions_jpsi2invi_data_psip_data12-0.txt
	   ;;

    0.1.3) echo "Test for data" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2invi/job_text/Data12/jobOptions_jpsi2invi_data_psip_data12-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2invi/job_text/Data12
            boss.exe jobOptions_jpsi2invi_data_psip_data12-0.txt
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    0.1.4) echo "Submit Condor jobs on data ---- 2..." 
	    cd run/jpsi2invi/job_text/Data12
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	   
		rm ../../rootfile/jpsi2invi_data_psip_data12-*
		boss.condor -g physics -n 633 jobOptions_jpsi2invi_data_psip_data12-%{ProcId}.txt
	    ;;

    0.1.5) echo "Check Condor jobs on data..."
	   ./python/chk_condorjobs.py run/jpsi2invi/rootfile  633
	   ;;
    
    0.1.6) echo "Generate selection Condor jobs on data ---- 1..."
	   mkdir run/jpsi2invi/event
	   mkdir run/jpsi2invi/job_text/Data12_event
	   cd run/jpsi2invi/gen_script
	   ./make_jobOption_file_Data12_event.sh
	   cd ../job_text/Data12_event
	   mv jobOptions_jpsi2invi_data_psip_data12_event-633.sh jobOptions_jpsi2invi_data_psip_data12_event-0.sh
       chmod 755 jobOptions_jpsi2invi_data_psip_data12_event-*
	   ;;

    0.1.7) echo "Test for data event" 
		cd run/jpsi2invi/job_text/Data12_event
		./jobOptions_jpsi2invi_data_psip_data12_event-0.sh
        ;;

    0.1.8) echo "Submit selection Condor jobs on data ---- 2..." 
	    cd run/jpsi2invi/job_text/Data12_event
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	  
	    rm ../../event/jpsi2invi_data_psip_data12_event-*	
	    hep_sub -g physics -n 633 jobOptions_jpsi2invi_data_psip_data12_event-%{ProcId}.sh
	   ;;

    0.1.9) echo "Check Condor jobs on events data..."
	   ./python/chk_condorjobs.py run/jpsi2invi/event  633
	   ;;

    0.1.10) echo  "Merge event root file on data..."
	#    rm run/jpsi2invi/hist/jpsi2invi_data_psip_data12_event_merged_1.root
	   ./python/mrg_rootfiles.py  run/jpsi2invi/event run/jpsi2invi/hist
	   ;; 

    0.1.11) echo  "Plot summary with data..."
	   ./python/plt_summary.py hist 
	   ;;

    0.2) echo "Running on con3650 data..."
	 ;;

    0.2.1) echo "Split con3650 data sample with each group 20G ..."
	   mkdir run/samples/data3650 
	   ./python/get_samples.py  /bes3fs/offline/data/664-1/3650/dst $HOME/bes/jpsi2invi/v0.1/run/samples/data3650/data_663p01_3650.txt 20G
	    # made 84 groups 
	    ;;

    0.2.2) echo "Generate Condor jobs on con3650 data ---- 1..."
	    mkdir run/jpsi2invi/job_text/data3650
	    mkdir run/jpsi2invi/rootfile_data3650  
	    cd run/jpsi2invi/gen_script
		./make_jobOption_file_data3650.sh
		cd ../job_text/data3650
		mv jobOptions_jpsi2invi_data3650-84.txt jobOptions_jpsi2invi_data3650-0.txt
	   ;;

    0.2.3) echo "test for data3650" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2invi/job_text/data3650/jobOptions_jpsi2invi_data3650-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2invi/job_text/data3650
            boss.exe jobOptions_jpsi2invi_data3650-0.txt
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    0.2.4) echo "Submit Condor jobs on data ---- 2..." 
	    cd run/jpsi2invi/job_text/data3650
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	   
        rm ../../rootfile_data3650/jpsi2invi_data3650-*
		boss.condor -g physics -n 84 jobOptions_jpsi2invi_data3650-%{ProcId}.txt
		;;

    0.2.5) echo "Check Condor jobs on con3650 data..."
	   ./python/chk_condorjobs.py run/jpsi2invi/rootfile_data3650  84 
	   ;;

    0.2.6) echo  "Generate selection Condor jobs on con3650 data ---- 1..."
	   mkdir run/jpsi2invi/event_data3650
	   mkdir run/jpsi2invi/job_text/data3650_event
	   cd run/jpsi2invi/gen_script
	   ./make_jobOption_file_data3650_event.sh
	   cd ../job_text/data3650_event
	   mv jobOptions_jpsi2invi_data3650_event-84.sh jobOptions_jpsi2invi_data3650_event-0.sh
	   chmod 755 jobOptions_jpsi2invi_data3650_event-*
	   ;;

    0.2.7) echo "test for data event" 
		cd run/jpsi2invi/job_text/data3650_event
		./jobOptions_jpsi2invi_data3650_event-0.sh
        ;;

    0.2.8) echo "Submit selection Condor jobs on con3650 data ---- 2..." 
	    cd run/jpsi2invi/job_text/data3650_event
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm
 		rm ../../event_data3650/jpsi2invi_data3650_event-*		
	    hep_sub -g physics -n 84 jobOptions_jpsi2invi_data3650_event-%{ProcId}.sh
	    ;; 
    
	0.2.9)echo "Check event Condor jobs on con3650 data..."
	   ./python/chk_condorjobs.py run/jpsi2invi/event_data3650 11
	   ;;
    
	0.2.10) echo  "Merge event root file on con3650 data..."
	   mkdir run/jpsi2invi/hist_data3650
	   ./python/mrg_rootfiles.py  run/jpsi2invi/event_data3650 run/jpsi2invi/hist_data3650
	   ;; 

    0.2.11) echo  "Plot summary with data and con3650..."
	   mkdir run/jpsi2invi/hist_data3650
	   ./python/plt_summary.py data3650 
	   ;;

    0.3) echo "Running on data for jpsi2incl..."
	 ;;

    0.3.2) echo "Generate Submit Condor jobs on data for incl..." 
	   mkdir -p run/jpsi2incl/job_text/Data12
	   mkdir -p run/jpsi2incl/rootfile
	   cd run/jpsi2incl/gen_script
	   ./make_jobOption_file_Data12_jpsi2incl.sh
	   cd ../job_text/Data12
	   mv jobOptions_jpsi2incl_data_psip_data12-633.txt jobOptions_jpsi2incl_data_psip_data12-0.txt
	   ;;

    0.3.3) echo "test for data for incl" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2incl/job_text/Data12/jobOptions_jpsi2incl_data_psip_data12-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2incl/job_text/Data12
            boss.exe jobOptions_jpsi2incl_data_psip_data12-0.txt
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    0.3.4) echo "Submit Condor jobs on data for incl ---- 2..." 
	    cd run/jpsi2incl/job_text/Data12
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	  
	    rm ../../rootfile/jpsi2incl_data_psip_data12-*	
	    boss.condor -g physics -n 633 jobOptions_jpsi2incl_data_psip_data12-%{ProcId}.txt
	    ;;

    0.3.5) echo "Check Condor jobs on data for incl..."
	   ./python/chk_condorjobs.py run/jpsi2incl/rootfile  633
	   ;;
    
    0.3.6) echo "Generate Submit selection Condor jobs on data for incl ---- 1..."
	   mkdir run/jpsi2incl/event
	   mkdir run/jpsi2incl/job_text/Data12_event
	   cd run/jpsi2incl/gen_script
	   rm ../job_text/Data12_event/jobOptions_jpsi2incl_data_psip_data12_event-*
	   ./make_jobOption_file_Data12_event.sh
	   cd ../job_text/Data12_event
	   mv jobOptions_jpsi2incl_data_psip_data12_event-633.sh jobOptions_jpsi2incl_data_psip_data12_event-0.sh
       chmod 755 jobOptions_jpsi2incl_data_psip_data12_event-*
	   ;;

    0.3.7) echo "Test for data event for incl" 
		cd run/jpsi2incl/job_text/Data12_event
		./jobOptions_jpsi2incl_data_psip_data12_event-0.sh
        ;;

    0.3.8) echo "Submit selection Condor jobs on data for incl ---- 2..." 
	    cd run/jpsi2incl/job_text/Data12_event
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	   
		rm ../../event/jpsi2incl_data_psip_data12_event-*
	    hep_sub -g physics -n 633 jobOptions_jpsi2incl_data_psip_data12_event-%{ProcId}.sh
	    ;;

    0.3.9) echo "Check Condor jobs on events data for incl..."
	   ./python/chk_condorjobs.py run/jpsi2incl/event  633
	   ;;

    0.3.10) echo  "Merge event root file on data for incl..."
	   mkdir run/jpsi2incl/hist
	   rm run/jpsi2incl/hist/jpsi2incl_data_psip_data12_event_merged_1.root
	   ./python/mrg_rootfiles.py  run/jpsi2incl/event run/jpsi2incl/hist
	   ;; 

    0.3.11) echo  "Plot summary with data for incl..."
	   ./python/plt_summary.py hist_incl 
	   ;; 
	
    0.4) echo "Running on data for jpsi2lplm..."
	 ;;
	
     0.4.2) echo "Generate Condor jobs on data for lplm ---- 1 ..." 
	   mkdir -p run/jpsi2lplm/job_text/Data12
	   mkdir -p run/jpsi2lplm/rootfile
	   cd run/jpsi2lplm/gen_script
	   ./make_jobOption_file_Data12_jpsi2lplm.sh
	   cd ../job_text/Data12
	   mv jobOptions_jpsi2lplm_data_psip_data12-633.txt jobOptions_jpsi2lplm_data_psip_data12-0.txt
	   ;;

    0.4.3) echo "test for data for lplm" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2lplm/job_text/Data12/jobOptions_jpsi2lplm_data_psip_data12-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2lplm/job_text/Data12
            boss.exe jobOptions_jpsi2lplm_data_psip_data12-0.txt
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    0.4.4) echo "Submit Condor jobs on data for lplm ---- 2..." 
	    cd run/jpsi2lplm/job_text/Data12
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	   
	    boss.condor -g physics -n 633 jobOptions_jpsi2lplm_data_psip_data12-%{ProcId}.txt
	    ;;

     0.4.5) echo "Check Condor jobs on data for lplm..."
	   ./python/chk_condorjobs.py run/jpsi2lplm/rootfile  633
	   ;;
    
     0.4.6) echo "Submit selection Condor jobs on data for lplm..."
	   mkdir run/jpsi2lplm/event
	   mkdir run/jpsi2lplm/job_text/Data12_event
	   cd run/jpsi2lplm/gen_script
       rm ../job_text/Data12_event/jobOptions_jpsi2lplm_data_psip_data12_event-*
	   ./make_jobOption_file_Data12_event.sh
	   cd ../job_text/Data12_event
	   mv jobOptions_jpsi2lplm_data_psip_data12_event-633.sh jobOptions_jpsi2lplm_data_psip_data12_event-0.sh
       chmod 755 jobOptions_jpsi2lplm_data_psip_data12_event-*
	   ;;

 	0.4.7) echo "Test for data event for lplm" 
		cd run/jpsi2lplm/job_text/Data12_event
		./jobOptions_jpsi2lplm_data_psip_data12_event-0.sh
		;;

	0.4.8) echo "Submit selection Condor jobs on data for lplm ---- 2..." 
		cd run/jpsi2lplm/job_text/Data12_event
		find . -name "*.out.*" | xargs rm
		find . -name "*.err.*" | xargs rm	   
	    rm ../../event/jpsi2lplm_data_psip_data12_event-*
		hep_sub -g physics -n 633 jobOptions_jpsi2lplm_data_psip_data12_event-%{ProcId}.sh
	    cd 
	    ;;

     0.4.9) echo "Check Condor jobs on events data for lplm..."
	   ./python/chk_condorjobs.py run/jpsi2lplm/event  633
	   ;;

     0.4.10) echo  "Merge event root file on data for lplm..."
	   mkdir run/jpsi2lplm/hist
       rm run/jpsi2lplm/hist/jpsi2lplm_data_psip_data12_event_merged_1.root
	   ./python/mrg_rootfiles.py  run/jpsi2lplm/event run/jpsi2lplm/hist
	   ;; 

     0.4.11) echo  "Plot summary with data for lplm..."
	   ./python/plt_summary.py hist_lplm 
	   ;; 


    0.7) echo "Running on con3650 data for jpsi2incl..."
	 ;;

    0.7.2) echo "Generate Condor jobs on con3650 data for incl---- 1..."
	    mkdir run/jpsi2incl/job_text/data3650
	    mkdir run/jpsi2incl/rootfile_data3650  
	    cd run/jpsi2incl/gen_script
		./make_jobOption_file_data3650.sh
		cd ../job_text/data3650
		mv jobOptions_jpsi2incl_data3650-84.txt jobOptions_jpsi2incl_data3650-0.txt
	   ;;

    0.7.3) echo "test for data3650 for incl" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2incl/job_text/data3650/jobOptions_jpsi2incl_data3650-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2incl/job_text/data3650
            boss.exe jobOptions_jpsi2incl_data3650-0.txt
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    0.7.4) echo "Submit Condor jobs on data for incl ---- 2..." 
	    cd run/jpsi2incl/job_text/data3650
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	
        rm ../../rootfile_data3650/jpsi2incl_data3650-
		boss.condor -g physics -n 84 jobOptions_jpsi2incl_data3650-%{ProcId}.txt
		;;

    0.7.5) echo "Check Condor jobs on con3650 data for incl..."
	   ./python/chk_condorjobs.py run/jpsi2incl/rootfile_data3650  84 
	   ;;

    0.7.6) echo  "Generate selection Condor jobs on con3650 data for incl ---- 1..."
	   mkdir run/jpsi2incl/event_data3650
	   mkdir run/jpsi2incl/job_text/data3650_event
	   cd run/jpsi2incl/gen_script
       rm ../job_text/data3650_event/jobOptions_jpsi2incl_data3650_event-*
	   ./make_jobOption_file_data3650_event.sh
	   cd ../job_text/data3650_event
	   mv jobOptions_jpsi2incl_data3650_event-84.sh jobOptions_jpsi2incl_data3650_event-0.sh
	   chmod 755 jobOptions_jpsi2incl_data3650_event-*
	   ;;

    0.7.7) echo "test for data event for incl" 
		cd run/jpsi2incl/job_text/data3650_event
		./jobOptions_jpsi2incl_data3650_event-0.sh
        ;;

    0.7.8) echo "Submit selection Condor jobs on con3650 data for incl ---- 2..." 
	    cd run/jpsi2incl/job_text/data3650_event
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm
 		rm ../../event_data3650/jpsi2incl_data3650_event-*		
	    hep_sub -g physics -n 84 jobOptions_jpsi2incl_data3650_event-%{ProcId}.sh
	    ;; 
    
	0.7.9)echo "Check event Condor jobs on con3650 data for incl..."
	   ./python/chk_condorjobs.py run/jpsi2incl/event_data3650 84
	   ;;
    
	0.7.10) echo  "Merge event root file on con3650 data for incl..."
	   mkdir run/jpsi2incl/hist_data3650
	   ./python/mrg_rootfiles.py  run/jpsi2incl/event_data3650 run/jpsi2incl/hist_data3650
	   ;; 



    # --------------------------------------------------------------------------
    #  MC Sample 
    # --------------------------------------------------------------------------
    
    1.1) echo "Running on MC sample..."
	 ;;

    1.1.1) echo "Split psi(2S) MC sample with each group 20G ..."
	   ./python/get_samples.py  /bes3fs/offline/data/664p03/psip/12mc/dst $HOME/bes/jpsi2invi/v0.1/run/samples/mc_664p03_psip_12mc.txt 20G
	   # made 394 groups 
	   ;;

    1.1.2) echo "Generate Condor jobs on psi(2S) MC sample ---- 1..."
	   mkdir -p run/jpsi2invi/job_text/mc12
	   mkdir -p run/jpsi2invi/rootfile_mc12
	   cd run/jpsi2invi/gen_script
	   ./make_jobOption_file_mc12_jpsi2invi.sh
	   cd ../job_text/mc12
	   mv jobOptions_jpsi2invi_psip_mc12-394.txt jobOptions_jpsi2invi_psip_mc12-0.txt
	   ;;

    1.1.3) echo "Test for psi(2S) MC sample" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2invi/job_text/mc12/jobOptions_jpsi2invi_psip_mc12-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2invi/job_text/mc12
            boss.exe jobOptions_jpsi2invi_psip_mc12-0.txt
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    1.1.4) echo "Submit Condor jobs on psi(2S) MC sample ---- 2..." 
	    cd run/jpsi2invi/job_text/mc12
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	 
        rm ../../rootfile_mc12/jpsi2invi_psip_mc12-* 
	   boss.condor -g physics -n 394 jobOptions_jpsi2invi_psip_mc12-%{ProcId}.txt 
	   ;;

    1.1.5) echo "Check Condor jobs on psi(2S) MC sample..."
	   ./python/chk_condorjobs.py $HOME/bes/jpsi2invi/v0.1/run/jpsi2invi/rootfile_mc12  394 
	   ;;

    1.1.6) echo "Generate selection Condor jobs on psi(2S) MC sample ---- 1..."
	   mkdir run/jpsi2invi/event_mc12
	   mkdir run/jpsi2invi/job_text/mc12_event  
	   cd run/jpsi2invi/gen_script
	   ./make_jobOption_file_mc12_event.sh
	   cd ../job_text/mc12_event
	   mv jobOptions_jpsi2invi_psip_mc12_event-394.sh jobOptions_jpsi2invi_psip_mc12_event-0.sh
	   chmod 755 jobOptions_jpsi2invi_psip_mc12_event-*
	   ;;

    1.1.7) echo "Test for psi(2S) MC sample event" 
		cd run/jpsi2invi/job_text/mc12_event
		./jobOptions_jpsi2invi_psip_mc12_event-0.sh
        ;;

    1.1.8) echo "Submit selection Condor jobs on psi(2S) MC sample ---- 2..." 
	    cd run/jpsi2invi/job_text/mc12_event
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	   
		rm ../../event_mc12/jpsi2invi_psip_mc12_event-*
	    hep_sub -g physics -n 394 jobOptions_jpsi2invi_psip_mc12_event-%{ProcId}.sh
	    ;;

    1.1.9) echo "Check events selection jobs on psi(2S) MC sample..."
	   ./python/chk_condorjobs.py run/jpsi2invi/event_mc12  394 
	   ;;

    1.1.10) echo  "Merge events files..."
	   mkdir run/jpsi2invi/hist_mc12
	   ./python/mrg_rootfiles.py  run/jpsi2invi/event_mc12 run/jpsi2invi/hist_mc12
	   ;; 

    1.1.11) echo  "Plot summary with data and psip(2S) MC sample..."
	   ./python/plt_summary.py mc12
	   ;; 

    1.3) echo "Running on psip(2S) MC sample for jpsi2incl..."
	 ;;

    1.3.2) echo "Generate Condor jobs on psip(2S) MC sample for incl..." 
	   mkdir -p run/jpsi2incl/job_text/mc12
	   mkdir -p run/jpsi2incl/rootfile_mc12
	   cd run/jpsi2incl/gen_script
	   ./make_jobOption_file_mc12_jpsi2incl.sh
	   cd ../job_text/mc12
	   mv jobOptions_jpsi2incl_psip_mc12-394.txt jobOptions_jpsi2incl_psip_mc12-0.txt
	   ;;

    1.3.3) echo "test for psip(2S) MC sample for incl" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2incl/job_text/mc12/jobOptions_jpsi2incl_psip_mc12-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2incl/job_text/mc12
            boss.exe jobOptions_jpsi2incl_psip_mc12-0.txt
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    1.3.4) echo "Submit Condor jobs on psip(2S) MC sample for incl ---- 2..." 
	    cd run/jpsi2incl/job_text/mc12
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	  
	   rm ../../rootfile_mc12/jpsi2incl_psip_mc12-*	
	   boss.condor -g physics -n 394 jobOptions_jpsi2incl_psip_mc12-%{ProcId}.txt
	   ;;

    1.3.5) echo "Check Condor jobs on psip(2S) MC sample for incl..."
	   ./python/chk_condorjobs.py run/jpsi2incl/rootfile_mc12  394
	   ;;
    
    1.3.6) echo "Generate selection Condor jobs on psip(2S) MC sample for incl..."
	   mkdir run/jpsi2incl/event_mc12
	   mkdir run/jpsi2incl/job_text/mc12_event
	   cd run/jpsi2incl/gen_script
       rm ../job_text/mc12_event/jobOptions_jpsi2incl_psip_mc12_event-*
	   ./make_jobOption_file_mc12_event.sh
	   cd ../job_text/mc12_event
	   mv jobOptions_jpsi2incl_psip_mc12_event-394.sh jobOptions_jpsi2incl_psip_mc12_event-0.sh
       chmod 755 jobOptions_jpsi2incl_psip_mc12_event-*
	   ;;

    1.3.7) echo "Test for psip(2S) MC sample event for incl" 
		cd run/jpsi2incl/job_text/mc12_event
		./jobOptions_jpsi2incl_psip_mc12_event-0.sh
        ;;

    1.3.8) echo "Submit selection Condor jobs on psip(2S) MC sample for incl ---- 2..." 
	    cd run/jpsi2incl/job_text/mc12_event
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	   	   
        rm ../../event_mc12/jpsi2incl_psip_mc12_event-*
	   hep_sub -g physics -n 394 jobOptions_jpsi2incl_psip_mc12_event-%{ProcId}.sh
	   ;;

    1.3.9) echo "Check Condor jobs on events psip(2S) MC sample for incl..."
	   ./python/chk_condorjobs.py run/jpsi2incl/event_mc12  394
	   ;;

    1.3.10) echo  "Merge event root file on psip(2S) MC sample for incl..."
	   mkdir run/jpsi2incl/hist_mc12
       rm run/jpsi2incl/hist_mc12/jpsi2incl_psip_mc12_event_merged_1.root
	   ./python/mrg_rootfiles.py  run/jpsi2incl/event_mc12 run/jpsi2incl/hist_mc12
	   ;; 

    1.3.11) echo  "Plot summary with psip(2S) MC sample for incl..."
	   ./python/plt_summary.py mc12_incl 
	   ;; 

    1.4) echo "Running on psip(2S) MC sample for jpsi2lplm..."
	 ;;
	
     1.4.2) echo "Generate Condor jobs on psip(2S) MC sample for lplm ---- 1 ..." 
	   mkdir -p run/jpsi2lplm/job_text/mc12
	   cd run/jpsi2lplm/gen_script
	   ./make_jobOption_file_mc12_jpsi2lplm.sh
	   cd ../job_text/mc12
	   mv jobOptions_jpsi2lplm_psip_mc12-394.txt jobOptions_jpsi2lplm_psip_mc12-0.txt
	   ;;

    1.4.3) echo "test for psip(2S) MC sample for lplm" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2lplm/job_text/mc12/jobOptions_jpsi2lplm_psip_mc12-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2lplm/job_text/mc12
            boss.exe jobOptions_jpsi2lplm_psip_mc12-0.txt
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    1.4.4) echo "Submit Condor jobs on psip(2S) MC sample for lplm ---- 2..." 
	    cd run/jpsi2lplm/job_text/mc12
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	   
	    boss.condor -g physics -n 394 jobOptions_jpsi2lplm_psip_mc12-%{ProcId}.txt
	    ;;

     1.4.5) echo "Check Condor jobs on psip(2S) MC sample for lplm..."
	   ./python/chk_condorjobs.py run/jpsi2lplm/rootfile_mc12  394
	   ;;
    
     1.4.6) echo "Submit selection Condor jobs on psip(2S) MC sample for lplm..."
	   mkdir run/jpsi2lplm/event_mc12
	   mkdir run/jpsi2lplm/job_text/mc12_event
	   cd run/jpsi2lplm/gen_script
       rm ../job_text/mc12_event/jobOptions_jpsi2lplm_psip_mc12_event-*
	   ./make_jobOption_file_mc12_event.sh
	   cd ../job_text/mc12_event
	   mv jobOptions_jpsi2lplm_psip_mc12_event-394.sh jobOptions_jpsi2lplm_psip_mc12_event-0.sh
       chmod 755 jobOptions_jpsi2lplm_psip_mc12_event-*
	   ;;

 	1.4.7) echo "Test for psip(2S) MC sample event for lplm" 
		cd run/jpsi2lplm/job_text/mc12_event
		./jobOptions_jpsi2lplm_psip_mc12_event-0.sh
		;;

	1.4.8) echo "Submit selection Condor jobs on psip(2S) MC sample for lplm ---- 2..." 
		cd run/jpsi2lplm/job_text/mc12_event
		find . -name "*.out.*" | xargs rm
		find . -name "*.err.*" | xargs rm	   
	    rm ../../event/jpsi2lplm_psip_mc12_event-*
		hep_sub -g physics -n 394 jobOptions_jpsi2lplm_psip_mc12_event-%{ProcId}.sh
	    ;;

     1.4.9) echo "Check Condor jobs on events psip(2S) MC sample for lplm..."
	   ./python/chk_condorjobs.py run/jpsi2lplm/event_mc12  394
	   ;;

     1.4.10) echo  "Merge event root file on psip(2S) MC sample for lplm..."
	   mkdir run/jpsi2lplm/hist_mc12
       rm run/jpsi2lplm/hist/jpsi2lplm_psip_mc12_event_merged_1.root
	   ./python/mrg_rootfiles.py  run/jpsi2lplm/event_mc12 run/jpsi2lplm/hist_mc12
	   ;; 


	
    1.5) echo "Running on generated MC sample..."
	 ;;

    1.5.3) echo "test for generated MC sample" 
        echo "have you changed test number?(yes / no)
        ./run/gen_mc/jpsi2ee/job_text/jobs/jobOptions_jpsi2invi_gen_mc_ee-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/gen_mc/jpsi2ee/job_text/jobs
            boss.exe jobOptions_jpsi2invi_gen_mc_ee-0.txt
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    1.5.4) echo "Submit Condor jobs on generated MC sample ---- 2..." 
	    cd run/gen_mc/jpsi2mumu/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_mumu/gen_mc_mumu_jpsi2invi-*
	    boss.condor -g physics -n 3 jobOptions_jpsi2invi_gen_mc_mumu-%{ProcId}.txt
        cd ../../../jpsi2ee/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_ee/gen_mc_ee_jpsi2invi-*
	    boss.condor -g physics -n 3 jobOptions_jpsi2invi_gen_mc_ee-%{ProcId}.txt
        cd ../../../jpsi2nn/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_nn/gen_mc_nn_jpsi2invi-1.root
	    boss.condor -g physics jobOptions_jpsi2invi_gen_mc_nn-1.txt
        cd ../../../jpsi2pp/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_pp/gen_mc_pp_jpsi2invi-*
	    boss.condor -g physics -n 2 jobOptions_jpsi2invi_gen_mc_pp-%{ProcId}.txt
        cd ../../../jpsi2nunu/job_text/jobs/
        find . -name "*.txt.*" | xargs rm	
        rm ../rootfile_nunu/gen_mc_nunu_jpsi2invi-1.root
        boss.condor -g physics jobOptions_jpsi2invi_gen_mc_nunu-1.txt
	   ;;

    1.5.5) echo "Check Condor jobs on generated MC sample..."
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2mumu/job_text/rootfile_mumu  3
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2ee/job_text/rootfile_ee  3
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2nn/job_text/rootfile_nn  1
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2pp/job_text/rootfile_pp  2
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2nunu/job_text/rootfile_nunu  1
	   ;;

    1.5.7) echo "Test for generated MC sample event" 
		./python/sel_events.py run/gen_mc/jpsi2ee/job_text/rootfile_ee/gen_mc_ee_jpsi2invi-1.root run/gen_mc/jpsi2ee/job_text/event_ee/invi/jpsi2invi_gen_mc_ee_event-1.root
        ll run/gen_mc/jpsi2ee/job_text/event_ee/invi/jpsi2invi_gen_mc_ee_event-1.root
        ;;

    1.5.8) echo "Submit selection Condor jobs on generated MC sample ---- 2..." 
	    cd run/gen_mc/jpsi2mumu/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_mumu/invi/jpsi2invi_gen_mc_mumu_event-*
	    hep_sub -g physics -n 3 jobOptions_jpsi2invi_gen_mc_mumu_event-%{ProcId}.sh
        cd ../../../jpsi2ee/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_ee/invi/jpsi2invi_gen_mc_ee_event-*
	    hep_sub -g physics -n 3 jobOptions_jpsi2invi_gen_mc_ee_event-%{ProcId}.sh
        cd ../../../jpsi2nn/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_nn/invi/jpsi2invi_gen_mc_nn_event-1.root
	    hep_sub -g physics jobOptions_jpsi2invi_gen_mc_nn_event-1.sh
        cd ../../../jpsi2pp/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_pp/invi/jpsi2invi_gen_mc_pp_event-*
	    hep_sub -g physics -n 2 jobOptions_jpsi2invi_gen_mc_pp_event-%{ProcId}.sh
        cd ../../../jpsi2nunu/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_nunu/invi/jpsi2invi_gen_mc_nunu_event-*
	    hep_sub -g physics jobOptions_jpsi2invi_gen_mc_nunu_event-1.sh
	   ;;

    1.5.10) echo  "Merge event root file on generated MC sample..."
        rm run/gen_mc/jpsi2mumu/job_text/hist/jpsi2invi_gen_mc_mumu_event_merged_1.root
        rm run/gen_mc/jpsi2ee/job_text/hist/jpsi2invi_gen_mc_ee_event_merged_1.root
        rm run/gen_mc/jpsi2nn/job_text/hist/jpsi2invi_gen_mc_nn_event_merged_1.root
        rm run/gen_mc/jpsi2pp/job_text/hist/jpsi2invi_gen_mc_pp_event_merged_1.root
        rm run/gen_mc/jpsi2nunu/job_text/hist/jpsi2invi_gen_mc_nunu_event_merged_1.root
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2mumu/job_text/event_mumu/invi run/gen_mc/jpsi2mumu/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2ee/job_text/event_ee/invi run/gen_mc/jpsi2ee/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2nn/job_text/event_nn/invi run/gen_mc/jpsi2nn/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2pp/job_text/event_pp/invi run/gen_mc/jpsi2pp/job_text/hist
       cd run/gen_mc/jpsi2mumu/job_text/hist
       mv jpsi2invi_gen_mc_mumu_event_merged_1.root jpsi2invi_gen_mc_mumu_event_merged_phi.root
       cd ../../../jpsi2ee/job_text/hist
       mv jpsi2invi_gen_mc_ee_event_merged_1.root jpsi2invi_gen_mc_ee_event_merged_phi.root
       cd ../../../jpsi2nn/job_text/hist
       mv jpsi2invi_gen_mc_nn_event_merged_1.root jpsi2invi_gen_mc_nn_event_merged_phi.root
       cd ../../../jpsi2pp/job_text/hist
       mv jpsi2invi_gen_mc_pp_event_merged_1.root jpsi2invi_gen_mc_pp_event_merged_phi.root
       cd ../../../jpsi2nunu/job_text/hist
       mv ../event_nunu/jpsi2invi_gen_mc_nunu_event-1.root jpsi2invi_gen_mc_nunu_event_merged_phi.root
       ;;

    1.6) echo "Running on generated MC sample for incl..."
	 ;;

    1.6.3) echo "test for generated MC sample for incl" 
        echo "have you changed test number?(yes / no)
        ./run/gen_mc/jpsi2ee/job_text/jobs/jobOptions_jpsi2incl_gen_mc_ee-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/gen_mc/jpsi2ee/job_text/jobs
            boss.exe jobOptions_jpsi2incl_gen_mc_ee-0.txt
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    1.6.4) echo "Submit Condor jobs on generated MC sample for incl ---- 2..." 
	    cd run/gen_mc/jpsi2mumu/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_mumu/gen_mc_mumu_jpsi2incl-*
	    boss.condor -g physics -n 3 jobOptions_jpsi2incl_gen_mc_mumu-%{ProcId}.txt
        cd ../../../jpsi2ee/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_ee/gen_mc_ee_jpsi2incl-*
	    boss.condor -g physics -n 3 jobOptions_jpsi2incl_gen_mc_ee-%{ProcId}.txt
        cd ../../../jpsi2nn/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_nn/gen_mc_nn_jpsi2incl-1.root
	    boss.condor -g physics jobOptions_jpsi2incl_gen_mc_nn-1.txt
        cd ../../../jpsi2pp/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_pp/gen_mc_pp_jpsi2incl-*
	    boss.condor -g physics -n 2 jobOptions_jpsi2incl_gen_mc_pp-%{ProcId}.txt
        cd ../../../jpsi2nunu/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_nunu/gen_mc_nunu_jpsi2incl-*
	    boss.condor -g physics jobOptions_jpsi2incl_gen_mc_nunu-1.txt
	   ;;

    1.6.5) echo "Check Condor jobs on generated MC sample for incl..."
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2mumu/job_text/rootfile_mumu  3
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2ee/job_text/rootfile_ee  3
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2nn/job_text/rootfile_nn  1
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2pp/job_text/rootfile_pp  2
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2nunu/job_text/rootfile_nunu  1
	   ;;

    1.6.7) echo "Test for generated MC sample event for incl" 
		./python/sel_events_inclusive.py run/gen_mc/jpsi2ee/job_text/rootfile_ee/gen_mc_ee_jpsi2incl-1.root run/gen_mc/jpsi2ee/job_text/event_ee/incl/jpsi2incl_gen_mc_ee_event-1.root
        ;;

    1.6.8) echo "Submit selection Condor jobs on generated MC sample for incl ---- 2..." 
	    cd run/gen_mc/jpsi2mumu/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_mumu/incl/jpsi2incl_gen_mc_mumu_event-*
	    hep_sub -g physics -n 3 jobOptions_jpsi2incl_gen_mc_mumu_event-%{ProcId}.sh
        cd ../../../jpsi2ee/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_ee/incl/jpsi2incl_gen_mc_ee_event-*
	    hep_sub -g physics -n 3 jobOptions_jpsi2incl_gen_mc_ee_event-%{ProcId}.sh
        cd ../../../jpsi2nn/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_nn/incl/jpsi2incl_gen_mc_nn_event-1.root
	    hep_sub -g physics jobOptions_jpsi2incl_gen_mc_nn_event-1.sh
        cd ../../../jpsi2pp/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_pp/incl/jpsi2incl_gen_mc_pp_event-*
	    hep_sub -g physics -n 2 jobOptions_jpsi2incl_gen_mc_pp_event-%{ProcId}.sh
        cd ../../../jpsi2nunu/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_nunu/incl/jpsi2incl_gen_mc_nunu_event-*
	    hep_sub -g physics jobOptions_jpsi2incl_gen_mc_nunu_event-1.sh
	   ;;

    1.6.10) echo  "Merge event root file on generated MC sample for incl..."
       rm run/gen_mc/jpsi2mumu/job_text/hist/jpsi2incl_gen_mc_mumu_event_merged_1.root
       rm run/gen_mc/jpsi2ee/job_text/hist/jpsi2incl_gen_mc_ee_event_merged_1.root
       rm run/gen_mc/jpsi2nn/job_text/hist/jpsi2incl_gen_mc_nn_event_merged_1.root
       rm run/gen_mc/jpsi2pp/job_text/hist/jpsi2incl_gen_mc_pp_event_merged_1.root
       rm run/gen_mc/jpsi2nunu/job_text/hist/jpsi2incl_gen_mc_nunu_event_merged_1.root
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2mumu/job_text/event_mumu/incl run/gen_mc/jpsi2mumu/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2ee/job_text/event_ee/incl run/gen_mc/jpsi2ee/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2nn/job_text/event_nn/incl run/gen_mc/jpsi2nn/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2pp/job_text/event_pp/incl run/gen_mc/jpsi2pp/job_text/hist
       cd run/gen_mc/jpsi2mumu/job_text/hist
       mv jpsi2incl_gen_mc_mumu_event_merged_1.root jpsi2incl_gen_mc_mumu_event_merged_phi.root
       cd ../../../jpsi2ee/job_text/hist
       mv jpsi2incl_gen_mc_ee_event_merged_1.root jpsi2incl_gen_mc_ee_event_merged_phi.root
       cd ../../../jpsi2nn/job_text/hist
       mv jpsi2incl_gen_mc_nn_event_merged_1.root jpsi2incl_gen_mc_nn_event_merged_phi.root
       cd ../../../jpsi2pp/job_text/hist
       mv jpsi2incl_gen_mc_pp_event_merged_1.root jpsi2incl_gen_mc_pp_event_merged_phi.root
       cd ../../../jpsi2nunu/job_text/hist
       mv ../event_nunu/jpsi2incl_gen_mc_nunu_event-1.root jpsi2incl_gen_mc_nunu_event_merged_phi.root
       ;;

    # 1.7) echo "Running on psip(2S) MC sample for jpsi2mumu..."
	#  ;;

    # 1.7.2) echo "Generate Condor jobs on psip(2S) MC sample for mumu..." 
	#    cd run/jpsi2mumu/gen_script
    #    rm ../job_text/mc12/jobOptions_jpsi2mumu_psip_mc12-*
	#    ./make_jobOption_file_mc12_jpsi2mumu.sh
	#    cd ../job_text/mc12
	#    mv jobOptions_jpsi2mumu_psip_mc12-394.txt jobOptions_jpsi2mumu_psip_mc12-0.txt
	#    ;;

    # 1.7.3) echo "test for psip(2S) MC sample for mumu" 
    #     echo "have you changed test number?(yes / no)
    #     ./run/jpsi2mumu/job_text/mc12/jobOptions_jpsi2mumu_psip_mc12-0.txt"
    #     read opt
    #     if [ $opt == "yes" ]
    #         then
    #         echo "now in yes"  
    #         cd run/jpsi2mumu/job_text/mc12
    #         boss.exe jobOptions_jpsi2mumu_psip_mc12-0.txt
    #     else
    #         echo "Default value is 'no', please change test number."
    #     fi
    #     ;;

    # 1.7.4) echo "Submit Condor jobs on psip(2S) MC sample for mumu ---- 2..." 
	#     cd run/jpsi2mumu/job_text/mc12
    #     find . -name "*.out.*" | xargs rm
    #     find . -name "*.err.*" | xargs rm	  
	#    rm ../../rootfile_mc12/jpsi2mumu_psip_mc12-*	
	#    boss.condor -g physics -n 394 jobOptions_jpsi2mumu_psip_mc12-%{ProcId}.txt
	#    ;;

    # 1.7.5) echo "Check Condor jobs on psip(2S) MC sample for mumu..."
	#    ./python/chk_condorjobs.py run/jpsi2mumu/rootfile_mc12  394
	#    ;;
    
    # 1.7.6) echo "Generate selection Condor jobs on psip(2S) MC sample for mumu..."
	#    cd run/jpsi2mumu/gen_script
    #    rm ../job_text/mc12_event/jobOptions_jpsi2mumu_psip_mc12_event-*
	#    ./make_jobOption_file_mc12_event.sh
	#    cd ../job_text/mc12_event
	#    mv jobOptions_jpsi2mumu_psip_mc12_event-394.sh jobOptions_jpsi2mumu_psip_mc12_event-0.sh
    #    chmod 755 jobOptions_jpsi2mumu_psip_mc12_event-*
	#    ;;

    # 1.7.7) echo "Test for psip(2S) MC sample event for mumu" 
	# 	cd run/jpsi2mumu/job_text/mc12_event
	# 	./jobOptions_jpsi2mumu_psip_mc12_event-0.sh
    #     ;;

    # 1.7.8) echo "Submit selection Condor jobs on psip(2S) MC sample for mumu ---- 2..." 
	#     cd run/jpsi2mumu/job_text/mc12_event
    #     find . -name "*.out.*" | xargs rm
    #     find . -name "*.err.*" | xargs rm	   	   
    #     rm ../../event_mc12/jpsi2mumu_psip_mc12_event-*
	#    hep_sub -g physics -n 394 jobOptions_jpsi2mumu_psip_mc12_event-%{ProcId}.sh
	#    ;;

    # 1.7.9) echo "Check Condor jobs on events psip(2S) MC sample for mumu..."
	#    ./python/chk_condorjobs.py run/jpsi2mumu/event_mc12  394
	#    ;;

    # 1.7.10) echo  "Merge event root file on psip(2S) MC sample for mumu..."
	#    mkdir run/jpsi2mumu/hist_mc12
    #    rm run/jpsi2mumu/hist_mc12/jpsi2mumu_psip_mc12_event_merged_1.root
	#    ./python/mrg_rootfiles.py  run/jpsi2mumu/event_mc12 run/jpsi2mumu/hist_mc12
	#    ;; 



    3.1) echo "Running on data09 sample..."
	 ;;

    3.1.1) echo "Split data09 sample with each group 20G ..."
	   ./python/get_samples.py  /bes3fs/offline/data/664-1/psip/dst run/samples/data09/data_664-1_psip.txt 20G
	   # made 633 groups 
	   ;;

    3.1.2) echo "Generate Condor jobs on data09 ---- 1..." 
	   cd run/jpsi2invi/gen_script
	   ./make_jobOption_file_data09_jpsi2invi.sh
	   cd ../job_text/data09
	   mv jobOptions_jpsi2invi_data_psip_data09-314.txt jobOptions_jpsi2invi_data_psip_data09-0.txt
	   ;;

    3.1.3) echo "Test for data09" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2invi/job_text/data09/jobOptions_jpsi2invi_data_psip_data09-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2invi/job_text/data09
            boss.exe jobOptions_jpsi2invi_data_psip_data09-0.txt
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    3.1.4) echo "Submit Condor jobs on data09 ---- 2..." 
	    cd run/jpsi2invi/job_text/data09
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	   
		rm ../../rootfile_data09/jpsi2invi_data_psip_data09-*
		boss.condor -g physics -n 314 jobOptions_jpsi2invi_data_psip_data09-%{ProcId}.txt
	    ;;

    3.1.5) echo "Check Condor jobs on data09..."
	   ./python/chk_condorjobs.py run/jpsi2invi/rootfile_data09  314
	   ;;
    
    3.1.6) echo "Generate selection Condor jobs on data09 ---- 1..."
	   cd run/jpsi2invi/job_text/data09_event
       find . -name "*.sh*" | xargs rm
       cd ../../gen_script
	   ./make_jobOption_file_data09_event.sh
	   cd ../job_text/data09_event
	   mv jobOptions_jpsi2invi_data_psip_data09_event-314.sh jobOptions_jpsi2invi_data_psip_data09_event-0.sh
       chmod 755 jobOptions_jpsi2invi_data_psip_data09_event-*
	   ;;

    3.1.7) echo "Test for data09 event" 
		cd run/jpsi2invi/job_text/data09_event
		./jobOptions_jpsi2invi_data_psip_data09_event-0.sh
        ;;

    3.1.8) echo "Submit selection Condor jobs on data09 ---- 2..." 
	    cd run/jpsi2invi/job_text/data09_event
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	  
	    rm ../../event_data09/jpsi2invi_data_psip_data09_event-*	
	    hep_sub -g physics -n 314 jobOptions_jpsi2invi_data_psip_data09_event-%{ProcId}.sh
	   ;;

    3.1.9) echo "Check Condor jobs on events data09..."
	   ./python/chk_condorjobs.py run/jpsi2invi/event_data09  314
	   ;;

    3.1.10) echo  "Merge event root file on data09..."
	   rm run/jpsi2invi/hist_data09/jpsi2invi_data_psip_data09_event_merged_1.root
	   ./python/mrg_rootfiles.py  run/jpsi2invi/event_data09 run/jpsi2invi/hist_data09
	   ;; 


    3.3) echo "Running on data09 for jpsi2incl..."
	 ;;

    3.3.2) echo "Generate Submit Condor jobs on data09 for incl..." 
	   mkdir -p run/jpsi2incl/job_text/data09
	   cd run/jpsi2incl/gen_script
	   ./make_jobOption_file_data09_jpsi2incl.sh
	   cd ../job_text/data09
	   mv jobOptions_jpsi2incl_data_psip_data09-314.txt jobOptions_jpsi2incl_data_psip_data09-0.txt
	   ;;

    3.3.3) echo "test for data09 for incl" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2incl/job_text/data09/jobOptions_jpsi2incl_data_psip_data09-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2incl/job_text/data09
            boss.exe jobOptions_jpsi2incl_data_psip_data09-0.txt
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    3.3.4) echo "Submit Condor jobs on data09 for incl ---- 2..." 
	    cd run/jpsi2incl/job_text/data09
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	  
	    rm ../../rootfile_data09/jpsi2incl_data_psip_data09-*	
	    boss.condor -g physics -n 314 jobOptions_jpsi2incl_data_psip_data09-%{ProcId}.txt
	    ;;

    3.3.5) echo "Check Condor jobs on data09 for incl..."
	   ./python/chk_condorjobs.py run/jpsi2incl/rootfile_data09  314
	   ;;
    
    3.3.6) echo "Generate Submit selection Condor jobs on data09 for incl ---- 1..."
	   mkdir run/jpsi2incl/job_text/data09_event
	   cd run/jpsi2incl/gen_script
	   rm ../job_text/data09_event/jobOptions_jpsi2incl_data_psip_data09_event-*
	   ./make_jobOption_file_data09_event.sh
	   cd ../job_text/data09_event
	   mv jobOptions_jpsi2incl_data_psip_data09_event-314.sh jobOptions_jpsi2incl_data_psip_data09_event-0.sh
       chmod 755 jobOptions_jpsi2incl_data_psip_data09_event-*
	   ;;

    3.3.7) echo "Test for data09 event for incl" 
		cd run/jpsi2incl/job_text/data09_event
		./jobOptions_jpsi2incl_data_psip_data09_event-0.sh
        ;;

    3.3.8) echo "Submit selection Condor jobs on data09 for incl ---- 2..." 
	    cd run/jpsi2incl/job_text/data09_event
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	   
		rm ../../event_data09/jpsi2incl_data_psip_data09_event-*
	    hep_sub -g physics -n 314 jobOptions_jpsi2incl_data_psip_data09_event-%{ProcId}.sh
	    ;;

    3.3.9) echo "Check Condor jobs on events data09 for incl..."
	   ./python/chk_condorjobs.py run/jpsi2incl/event_data09  314
	   ;;

    3.3.10) echo  "Merge event root file on data09 for incl..."
	   mkdir run/jpsi2incl/hist_data09
	   rm run/jpsi2incl/hist_data09/jpsi2incl_data_psip_data09_event_merged_1.root
	   ./python/mrg_rootfiles.py  run/jpsi2incl/event_data09 run/jpsi2incl/hist_data09
	   ;; 

    3.4) echo "Running on data09 for jpsi2lplm..."
	 ;;
	
     3.4.2) echo "Generate Condor jobs on data09 for lplm ---- 1 ..." 
	   mkdir -p run/jpsi2lplm/job_text/data09
	   cd run/jpsi2lplm/gen_script
	   ./make_jobOption_file_data09_jpsi2lplm.sh
	   cd ../job_text/data09
	   mv jobOptions_jpsi2lplm_data_psip_data09-314.txt jobOptions_jpsi2lplm_data_psip_data09-0.txt
	   ;;

    3.4.3) echo "test for data09 for lplm" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2lplm/job_text/data09/jobOptions_jpsi2lplm_data_psip_data09-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2lplm/job_text/data09
            boss.exe jobOptions_jpsi2lplm_data_psip_data09-0.txt
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    3.4.4) echo "Submit Condor jobs on data09 for lplm ---- 2..." 
	    cd run/jpsi2lplm/job_text/data09
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	   
	    boss.condor -g physics -n 314 jobOptions_jpsi2lplm_data_psip_data09-%{ProcId}.txt
	    ;;

     3.4.5) echo "Check Condor jobs on data09 for lplm..."
	   ./python/chk_condorjobs.py run/jpsi2lplm/rootfile_data09  314
	   ;;
    
     3.4.6) echo "Submit selection Condor jobs on data09 for lplm..."
	   mkdir run/jpsi2lplm/job_text/data09_event
	   cd run/jpsi2lplm/gen_script
       rm ../job_text/data09_event/jobOptions_jpsi2lplm_data_psip_data09_event-*
	   ./make_jobOption_file_data09_event.sh
	   cd ../job_text/data09_event
	   mv jobOptions_jpsi2lplm_data_psip_data09_event-314.sh jobOptions_jpsi2lplm_data_psip_data09_event-0.sh
       chmod 755 jobOptions_jpsi2lplm_data_psip_data09_event-*
	   ;;

 	3.4.7) echo "Test for data09 event for lplm" 
		cd run/jpsi2lplm/job_text/data09_event
		./jobOptions_jpsi2lplm_data_psip_data09_event-0.sh
		;;

	3.4.8) echo "Submit selection Condor jobs on data09 for lplm ---- 2..." 
		cd run/jpsi2lplm/job_text/data09_event
		find . -name "*.out.*" | xargs rm
		find . -name "*.err.*" | xargs rm	   
	    rm ../../event_data09/jpsi2lplm_data_psip_data09_event-*
		hep_sub -g physics -n 314 jobOptions_jpsi2lplm_data_psip_data09_event-%{ProcId}.sh
	    ;;

     3.4.9) echo "Check Condor jobs on events data09 for lplm..."
	   ./python/chk_condorjobs.py run/jpsi2lplm/event_data09  314
	   ;;

     3.4.10) echo  "Merge event root file on data09 for lplm..."
	   mkdir run/jpsi2lplm/hist_data09
       rm run/jpsi2lplm/hist_data09/jpsi2lplm_data_psip_data09_event_merged_1.root
	   ./python/mrg_rootfiles.py  run/jpsi2lplm/event_data09 run/jpsi2lplm/hist_data09
	   ;; 

    3.5) echo "Running on generated MC 09 sample..."
	 ;;

    3.5.3) echo "test for generated MC 09 sample" 
        echo "have you changed test number?(yes / no)
        ./run/gen_mc/jpsi2ee_09/job_text/jobs/jobOptions_jpsi2invi_gen_mc_ee_09-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/gen_mc/jpsi2ee_09/job_text/jobs
            boss.exe jobOptions_jpsi2invi_gen_mc_ee_09-0.txt
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    3.5.4) echo "Submit Condor jobs on generated MC 09 sample ---- 2..." 
	    cd run/gen_mc/jpsi2mumu_09/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_mumu_09/gen_mc_mumu_09_jpsi2invi-*
	    boss.condor -g physics -n 10 jobOptions_jpsi2invi_gen_mc_mumu_09-%{ProcId}.txt
        cd ../../../jpsi2ee_09/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_ee_09/gen_mc_ee_09_jpsi2invi-*
	    boss.condor -g physics -n 10 jobOptions_jpsi2invi_gen_mc_ee_09-%{ProcId}.txt
        cd ../../../jpsi2nn_09/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_nn_09/gen_mc_nn_09_jpsi2invi-*
	    boss.condor -g physics -n 4 jobOptions_jpsi2invi_gen_mc_nn_09-%{ProcId}.txt
        cd ../../../jpsi2pp_09/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_pp_09/gen_mc_pp_09_jpsi2invi-*
	    boss.condor -g physics -n 7 jobOptions_jpsi2invi_gen_mc_pp_09-%{ProcId}.txt
        cd ../../../jpsi2nunu_09/job_text/jobs
        rm ../rootfile_nunu_09/gen_mc_nunu_09_jpsi2invi-*
        boss.condor -g physics -n 4 jobOptions_jpsi2invi_gen_mc_nunu_09-%{ProcId}.txt
	   ;;

    3.5.5) echo "Check Condor jobs on generated MC 09 sample..."
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2mumu_09/job_text/rootfile_mumu_09  10
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2ee_09/job_text/rootfile_ee_09  10
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2nn_09/job_text/rootfile_nn_09  4
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2pp_09/job_text/rootfile_pp_09  7
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2nunu_09/job_text/rootfile_nunu_09  4
	   ;;

    3.5.7) echo "Test for generated MC 09 sample event" 
		./python/sel_events.py run/gen_mc/jpsi2ee_09/job_text/rootfile_ee_09/gen_mc_ee_09_jpsi2invi-1.root run/gen_mc/jpsi2ee_09/job_text/event_ee_09/invi/jpsi2invi_gen_mc_ee_09_event-1.root
        ll run/gen_mc/jpsi2ee_09/job_text/event_ee_09/invi/jpsi2invi_gen_mc_ee_09_event-1.root
        ;;

    3.5.8) echo "Submit selection Condor jobs on generated MC 09 sample ---- 2..." 
	    cd run/gen_mc/jpsi2mumu_09/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_mumu_09/invi/jpsi2invi_gen_mc_mumu_09_event-*
	    hep_sub -g physics -n 10 jobOptions_jpsi2invi_gen_mc_mumu_09_event-%{ProcId}.sh
        cd ../../../jpsi2ee_09/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_ee_09/invi/jpsi2invi_gen_mc_ee_09_event-*
	    hep_sub -g physics -n 10 jobOptions_jpsi2invi_gen_mc_ee_09_event-%{ProcId}.sh
        cd ../../../jpsi2nn_09/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_nn_09/invi/jpsi2invi_gen_mc_nn_09_event-*
	    hep_sub -g physics -n 4 jobOptions_jpsi2invi_gen_mc_nn_09_event-%{ProcId}.sh
        cd ../../../jpsi2pp_09/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_pp_09/invi/jpsi2invi_gen_mc_pp_09_event-*
	    hep_sub -g physics -n 7 jobOptions_jpsi2invi_gen_mc_pp_09_event-%{ProcId}.sh
        cd ../../../jpsi2nunu_09/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_nunu_09/invi/jpsi2invi_gen_mc_nunu_09_event-*
	    hep_sub -g physics -n 4 jobOptions_jpsi2invi_gen_mc_nunu_09_event-%{ProcId}.sh
	   ;;

    3.5.9) echo "Check Condor event jobs on generated MC 09 sample..."
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2mumu_09/job_text/event_mumu_09  10
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2ee_09/job_text/event_ee_09  10
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2nn_09/job_text/event_nn_09  4
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2pp_09/job_text/event_pp_09  7
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2nunu_09/job_text/event_nunu_09  4
	   ;;       

    3.5.10) echo  "Merge event root file on generated MC 09 sample..."
        rm run/gen_mc/jpsi2mumu_09/job_text/hist/jpsi2invi_gen_mc_mumu_09_event_merged_1.root
        rm run/gen_mc/jpsi2ee_09/job_text/hist/jpsi2invi_gen_mc_ee_09_event_merged_1.root
        rm run/gen_mc/jpsi2nn_09/job_text/hist/jpsi2invi_gen_mc_nn_09_event_merged_1.root
        rm run/gen_mc/jpsi2pp_09/job_text/hist/jpsi2invi_gen_mc_pp_09_event_merged_1.root
        rm run/gen_mc/jpsi2nunu_09/job_text/hist/jpsi2invi_gen_mc_nunu_09_event_merged_1.root
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2mumu_09/job_text/event_mumu_09/invi run/gen_mc/jpsi2mumu_09/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2ee_09/job_text/event_ee_09/invi run/gen_mc/jpsi2ee_09/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2nn_09/job_text/event_nn_09/invi run/gen_mc/jpsi2nn_09/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2pp_09/job_text/event_pp_09/invi run/gen_mc/jpsi2pp_09/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2nunu_09/job_text/event_nunu_09/invi run/gen_mc/jpsi2nunu_09/job_text/hist
       cd run/gen_mc/jpsi2mumu_09/job_text/hist
       mv jpsi2invi_gen_mc_mumu_09_event_merged_1.root jpsi2invi_gen_mc_mumu_09_event_merged_phi.root
       cd ../../../jpsi2ee_09/job_text/hist
       mv jpsi2invi_gen_mc_ee_09_event_merged_1.root jpsi2invi_gen_mc_ee_09_event_merged_phi.root
       cd ../../../jpsi2nn_09/job_text/hist
       mv jpsi2invi_gen_mc_nn_09_event_merged_1.root jpsi2invi_gen_mc_nn_09_event_merged_phi.root
       cd ../../../jpsi2pp_09/job_text/hist
       mv jpsi2invi_gen_mc_pp_09_event_merged_1.root jpsi2invi_gen_mc_pp_09_event_merged_phi.root
       cd ../../../jpsi2nunu_09/job_text/hist
       mv jpsi2invi_gen_mc_nunu_09_event_merged_1.root jpsi2invi_gen_mc_nunu_09_event_merged_phi.root
       ;;

    3.6) echo "Running on generated MC 09 sample for incl..."
	 ;;

    3.6.4) echo "Submit Condor jobs on generated MC 09 sample ---- 2..." 
	    cd run/gen_mc/jpsi2mumu_09/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_mumu_09/gen_mc_mumu_09_jpsi2incl-*
	    boss.condor -g physics -n 10 jobOptions_jpsi2incl_gen_mc_mumu_09-%{ProcId}.txt
        cd ../../../jpsi2ee_09/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_ee_09/gen_mc_ee_09_jpsi2incl-*
	    boss.condor -g physics -n 10 jobOptions_jpsi2incl_gen_mc_ee_09-%{ProcId}.txt
        cd ../../../jpsi2nn_09/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_nn_09/gen_mc_nn_09_jpsi2incl-*
	    boss.condor -g physics -n 4 jobOptions_jpsi2incl_gen_mc_nn_09-%{ProcId}.txt
        cd ../../../jpsi2pp_09/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_pp_09/gen_mc_pp_09_jpsi2incl-*
	    boss.condor -g physics -n 7 jobOptions_jpsi2incl_gen_mc_pp_09-%{ProcId}.txt
        cd ../../../jpsi2nunu_09/job_text/jobs
        rm ../rootfile_nunu_09/gen_mc_nunu_09_jpsi2incl-*
        boss.condor -g physics -n 4 jobOptions_jpsi2incl_gen_mc_nunu_09-%{ProcId}.txt
	   ;;


    3.6.8) echo "Submit selection Condor jobs on generated MC 09 sample ---- 2..." 
	    cd run/gen_mc/jpsi2mumu_09/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_mumu_09/incl/jpsi2incl_gen_mc_mumu_09_event-*
	    hep_sub -g physics -n 10 jobOptions_jpsi2incl_gen_mc_mumu_09_event-%{ProcId}.sh
        cd ../../../jpsi2ee_09/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_ee_09/incl/jpsi2incl_gen_mc_ee_09_event-*
	    hep_sub -g physics -n 10 jobOptions_jpsi2incl_gen_mc_ee_09_event-%{ProcId}.sh
        cd ../../../jpsi2nn_09/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_nn_09/incl/jpsi2incl_gen_mc_nn_09_event-1.root
	    hep_sub -g physics -n 4 jobOptions_jpsi2incl_gen_mc_nn_09_event-%{ProcId}.sh
        cd ../../../jpsi2pp_09/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_pp_09/incl/jpsi2incl_gen_mc_pp_09_event-*
	    hep_sub -g physics -n 7 jobOptions_jpsi2incl_gen_mc_pp_09_event-%{ProcId}.sh
        cd ../../../jpsi2nunu_09/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_nunu_09/incl/jpsi2incl_gen_mc_nunu_09_event-*
	    hep_sub -g physics -n 4 jobOptions_jpsi2incl_gen_mc_nunu_09_event-%{ProcId}.sh
	   ;;

    3.6.9) echo "Check Condor event jobs on generated MC 09 sample..."
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2mumu_09/job_text/event_mumu_09/incl  10
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2ee_09/job_text/event_ee_09/incl  10
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2nn_09/job_text/event_nn_09/incl  4
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2pp_09/job_text/event_pp_09/incl  7
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2nunu_09/job_text/event_nunu_09/incl  4
	   ;;     

    3.6.10) echo  "Merge event root file on generated MC 09 sample..."
	    rm run/gen_mc/jpsi2mumu_09/job_text/hist/jpsi2incl_gen_mc_mumu_09_event_merged_1.root
        rm run/gen_mc/jpsi2ee_09/job_text/hist/jpsi2incl_gen_mc_ee_09_event_merged_1.root
        rm run/gen_mc/jpsi2nn_09/job_text/hist/jpsi2incl_gen_mc_nn_09_event_merged_1.root
        rm run/gen_mc/jpsi2pp_09/job_text/hist/jpsi2incl_gen_mc_pp_09_event_merged_1.root
        rm run/gen_mc/jpsi2nunu_09/job_text/hist/jpsi2incl_gen_mc_nunu_09_event_merged_1.root
       ./python/mrg_rootfiles.py  run/gen_mc/jpsi2mumu_09/job_text/event_mumu_09/incl run/gen_mc/jpsi2mumu_09/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2ee_09/job_text/event_ee_09/incl run/gen_mc/jpsi2ee_09/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2nn_09/job_text/event_nn_09/incl run/gen_mc/jpsi2nn_09/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2pp_09/job_text/event_pp_09/incl run/gen_mc/jpsi2pp_09/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2nunu_09/job_text/event_nunu_09/incl run/gen_mc/jpsi2nunu_09/job_text/hist
       cd run/gen_mc/jpsi2mumu_09/job_text/hist
       mv jpsi2incl_gen_mc_mumu_09_event_merged_1.root jpsi2incl_gen_mc_mumu_09_event_merged_phi.root
       cd ../../../jpsi2ee_09/job_text/hist
       mv jpsi2incl_gen_mc_ee_09_event_merged_1.root jpsi2incl_gen_mc_ee_09_event_merged_phi.root
       cd ../../../jpsi2nn_09/job_text/hist
       mv jpsi2incl_gen_mc_nn_09_event_merged_1.root jpsi2incl_gen_mc_nn_09_event_merged_phi.root
       cd ../../../jpsi2pp_09/job_text/hist
       mv jpsi2incl_gen_mc_pp_09_event_merged_1.root jpsi2incl_gen_mc_pp_09_event_merged_phi.root
       cd ../../../jpsi2nunu_09/job_text/hist
       mv jpsi2incl_gen_mc_nunu_09_event_merged_1.root jpsi2incl_gen_mc_nunu_09_event_merged_phi.root

        ;;

    4.1) echo "Running on psip(2S) MC09..."
	 ;;

    4.1.2) echo "Generate Condor jobs on psip(2S) MC09..." 
	   cd run/jpsi2invi/gen_script
	   ./make_jobOption_file_mc09_jpsi2invi.sh
	   cd ../job_text/mc09
	   mv jobOptions_jpsi2invi_psip_mc09-106.txt jobOptions_jpsi2invi_psip_mc09-0.txt
	   ;;

    4.1.3) echo "test for psip(2S) MC09" 
    
        echo "have you changed test number?(yes / no)
        ./run/jpsi2invi/job_text/mc09/jobOptions_jpsi2invi_psip_mc09-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2invi/job_text/mc09
            boss.exe jobOptions_jpsi2invi_psip_mc09-0.txt
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    4.1.4) echo "Submit Condor jobs on psip(2S) MC09 ---- 2..." 
	    cd run/jpsi2invi/job_text/mc09
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	  
	   rm ../../rootfile_mc09/jpsi2invi_psip_mc09-*	
	   boss.condor -g physics -n 106 jobOptions_jpsi2invi_psip_mc09-%{ProcId}.txt
	   ;;

    4.1.5) echo "Check Condor jobs on psip(2S) MC09..."
	   ./python/chk_condorjobs.py run/jpsi2invi/rootfile_mc09  106
	   ;;
    
    4.1.6) echo "Generate selection Condor jobs on psip(2S) MC09..."
	   mkdir run/jpsi2invi/job_text/mc09_event
	   cd run/jpsi2invi/gen_script
	   ./make_jobOption_file_mc09_event.sh
	   cd ../job_text/mc09_event
	   mv jobOptions_jpsi2invi_psip_mc09_event-106.sh jobOptions_jpsi2invi_psip_mc09_event-0.sh
       chmod 755 jobOptions_jpsi2invi_psip_mc09_event-*
	   ;;

    4.1.7) echo "Test for psip(2S) MC09 event for invi" 
		cd run/jpsi2invi/job_text/mc09_event
		./jobOptions_jpsi2invi_psip_mc09_event-0.sh
        ;;

    4.1.8) echo "Submit selection Condor jobs on psip(2S) MC09 ---- 2..." 
	    cd run/jpsi2invi/job_text/mc09_event
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	   	   
        rm ../../event_mc09/jpsi2invi_psip_mc09_event-*
	   hep_sub -g physics -n 106 jobOptions_jpsi2invi_psip_mc09_event-%{ProcId}.sh
	   ;;

    4.1.9) echo "Check Condor jobs on events psip(2S) MC09..."
	   ./python/chk_condorjobs.py run/jpsi2invi/event_mc09  106
	   ;;

    4.1.10) echo  "Merge event root file on psip(2S) MC09..."
	   mkdir run/jpsi2invi/hist_mc09
       rm run/jpsi2invi/hist_mc09/jpsi2invi_psip_mc09_event_merged_1.root
	   ./python/mrg_rootfiles.py  run/jpsi2invi/event_mc09 run/jpsi2invi/hist_mc09
	   ;; 
     





    4.3) echo "Running on psip(2S) MC09 for jpsi2incl..."
	 ;;

    4.3.1) echo "Split psi(2S) MC09 with each group 20G ..."
	   ./python/get_samples.py  /bes3fs/offline/data/664p01/psip/mc/09dst $HOME/bes/jpsi2invi/v0.1/run/samples/mc09/mc_664p01_psip_mc09.txt 20G
	   # made 106 groups 
	   ;;

    4.3.2) echo "Generate Condor jobs on psip(2S) MC09 for incl..." 
	   mkdir -p run/jpsi2incl/job_text/mc09
	   cd run/jpsi2incl/gen_script
	   ./make_jobOption_file_mc09_jpsi2incl.sh
	   cd ../job_text/mc09
	   mv jobOptions_jpsi2incl_psip_mc09-106.txt jobOptions_jpsi2incl_psip_mc09-0.txt
	   ;;

    4.3.3) echo "test for psip(2S) MC09 for incl" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2incl/job_text/mc09/jobOptions_jpsi2incl_psip_mc09-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2incl/job_text/mc09
            boss.exe jobOptions_jpsi2incl_psip_mc09-0.txt
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    4.3.4) echo "Submit Condor jobs on psip(2S) MC09 for incl ---- 2..." 
	    cd run/jpsi2incl/job_text/mc09
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	  
	   rm ../../rootfile_mc09/jpsi2incl_psip_mc09-*	
	   boss.condor -g physics -n 106 jobOptions_jpsi2incl_psip_mc09-%{ProcId}.txt
	   ;;

    4.3.5) echo "Check Condor jobs on psip(2S) MC09 for incl..."
	   ./python/chk_condorjobs.py run/jpsi2incl/rootfile_mc09  106
	   ;;
    
    4.3.6) echo "Generate selection Condor jobs on psip(2S) MC09 for incl..."
	   mkdir run/jpsi2incl/job_text/mc09_event
	   cd run/jpsi2incl/gen_script
	   ./make_jobOption_file_mc09_event.sh
	   cd ../job_text/mc09_event
	   mv jobOptions_jpsi2incl_psip_mc09_event-106.sh jobOptions_jpsi2incl_psip_mc09_event-0.sh
       chmod 755 jobOptions_jpsi2incl_psip_mc09_event-*
	   ;;

    4.3.7) echo "Test for psip(2S) MC09 event for incl" 
		cd run/jpsi2incl/job_text/mc09_event
		./jobOptions_jpsi2incl_psip_mc09_event-0.sh
        ;;

    4.3.8) echo "Submit selection Condor jobs on psip(2S) MC09 for incl ---- 2..." 
	    cd run/jpsi2incl/job_text/mc09_event
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	   	   
        rm ../../event_mc09/jpsi2incl_psip_mc09_event-*
	   hep_sub -g physics -n 106 jobOptions_jpsi2incl_psip_mc09_event-%{ProcId}.sh
	   ;;

    4.3.9) echo "Check Condor jobs on events psip(2S) MC09 for incl..."
	   ./python/chk_condorjobs.py run/jpsi2incl/event_mc09  106
	   ;;

    4.3.10) echo  "Merge event root file on psip(2S) MC09 for incl..."
	   mkdir run/jpsi2incl/hist_mc09
       rm run/jpsi2incl/hist_mc09/jpsi2incl_psip_mc09_event_merged_1.root
	   ./python/mrg_rootfiles.py  run/jpsi2incl/event_mc09 run/jpsi2incl/hist_mc09
	   ;; 

    4.4) echo "Running on psip(2S) MC09 for jpsi2lplm..."
	 ;;
	
     4.4.2) echo "Generate Condor jobs on psip(2S) MC09 for lplm ---- 1 ..." 
	   mkdir -p run/jpsi2lplm/job_text/mc09
	   cd run/jpsi2lplm/gen_script
	   ./make_jobOption_file_mc09_jpsi2lplm.sh
	   cd ../job_text/mc09
	   mv jobOptions_jpsi2lplm_psip_mc09-106.txt jobOptions_jpsi2lplm_psip_mc09-0.txt
	   ;;

    4.4.3) echo "test for psip(2S) MC09 for lplm" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2lplm/job_text/mc09/jobOptions_jpsi2lplm_psip_mc09-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2lplm/job_text/mc09
            boss.exe jobOptions_jpsi2lplm_psip_mc09-0.txt
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    4.4.4) echo "Submit Condor jobs on psip(2S) MC09 for lplm ---- 2..." 
	    cd run/jpsi2lplm/job_text/mc09
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	   
	    boss.condor -g physics -n 106 jobOptions_jpsi2lplm_psip_mc09-%{ProcId}.txt
	    ;;

     4.4.5) echo "Check Condor jobs on psip(2S) MC09 for lplm..."
	   ./python/chk_condorjobs.py run/jpsi2lplm/rootfile_mc09  106
	   ;;
    
     4.4.6) echo "Submit selection Condor jobs on psip(2S) MC09 for lplm..."
	   mkdir run/jpsi2lplm/job_text/mc09_event
	   cd run/jpsi2lplm/gen_script
       rm ../job_text/mc09_event/jobOptions_jpsi2lplm_psip_mc09_event-*
	   ./make_jobOption_file_mc09_event.sh
	   cd ../job_text/mc09_event
	   mv jobOptions_jpsi2lplm_psip_mc09_event-106.sh jobOptions_jpsi2lplm_psip_mc09_event-0.sh
       chmod 755 jobOptions_jpsi2lplm_psip_mc09_event-*
	   ;;

 	4.4.7) echo "Test for psip(2S) MC09 event for lplm" 
		cd run/jpsi2lplm/job_text/mc09_event
		./jobOptions_jpsi2lplm_psip_mc09_event-0.sh
		;;

	4.4.8) echo "Submit selection Condor jobs on psip(2S) MC09 for lplm ---- 2..." 
		cd run/jpsi2lplm/job_text/mc09_event
		find . -name "*.out.*" | xargs rm
		find . -name "*.err.*" | xargs rm	   
	    rm ../../event_mc09/jpsi2lplm_psip_mc09_event-*
		hep_sub -g physics -n 106 jobOptions_jpsi2lplm_psip_mc09_event-%{ProcId}.sh
	    ;;

     4.4.9) echo "Check Condor jobs on events psip(2S) MC09 for lplm..."
	   ./python/chk_condorjobs.py run/jpsi2lplm/event_mc09  106
	   ;;

     4.4.10) echo  "Merge event root file on psip(2S) MC09 for lplm..."
	   mkdir run/jpsi2lplm/hist_mc09
       rm run/jpsi2lplm/hist_mc09/jpsi2lplm_psip_mc09_event_merged_1.root
	   ./python/mrg_rootfiles.py  run/jpsi2lplm/event_mc09 run/jpsi2lplm/hist_mc09
	   ;; 


    4.6.4) echo "Submit Condor jobs on generated MC sample 09&12 for lplm ---- 2..." 
	    cd run/gen_mc/jpsi2mumu/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_mumu/gen_mc_mumu_jpsi2lplm-*
	    boss.condor -g physics -n 3 jobOptions_jpsi2lplm_gen_mc_mumu-%{ProcId}.txt
        cd ../../../jpsi2mumu_09/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_mumu_09/gen_mc_mumu_09_jpsi2lplm-*
	    boss.condor -g physics -n 10 jobOptions_jpsi2lplm_gen_mc_mumu_09-%{ProcId}.txt
	   ;;

    4.6.8) echo "Submit selection Condor jobs on generated MC sample 09&12 for lplm ---- 2..." 
	    cd run/gen_mc/jpsi2mumu/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_mumu/lplm/jpsi2lplm_gen_mc_mumu_event-*
	    hep_sub -g physics -n 3 jobOptions_jpsi2lplm_gen_mc_mumu_event-%{ProcId}.sh
        cd ../../../jpsi2ee_09/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_mumu_09/lplm/jpsi2lplm_gen_mc_mumu_09_event-*
	    hep_sub -g physics -n 10 jobOptions_jpsi2lplm_gen_mc_mumu_09_event-%{ProcId}.sh
	   ;;

    4.6.10) echo  "Merge event root file on generated MC sample 09&12 for lplm..."
       rm run/gen_mc/jpsi2mumu/job_text/hist/jpsi2lplm_gen_mc_mumu_event_merged_1.root
       rm run/gen_mc/jpsi2mumu_09/job_text/hist/jpsi2lplm_gen_mc_mumu_09_event_merged_1.root
       ./python/mrg_rootfiles.py  run/gen_mc/jpsi2mumu/job_text/event_mumu/lplm run/gen_mc/jpsi2mumu/job_text/hist 
       ./python/mrg_rootfiles.py  run/gen_mc/jpsi2mumu_09/job_text/event_mumu_09/lplm run/gen_mc/jpsi2mumu_09/job_text/hist 
	   ;;


    5.0.1) echo "Simulation -- Generate Jpsi->anything MC samples"
        cd run/gen_mc/jpsi2any
        rm job_text/sim/*
        ./make_jobOption_file_jpsi2ee_sim.sh
        cd job_text/sim
        mv jobOptions_sim-300.txt jobOptions_sim-0.txt
        boss.condor -g physics -n 300 jobOptions_sim-%{ProcId}.txt
        ;;

    5.0.2) echo "Reconstruction -- Generate Jpsi->anything MC samples"
        cd run/gen_mc/jpsi2any
        rm job_text/rec/*
        ./make_jobOption_file_jpsi2ee_rec.sh
        cd job_text/rec
        mv jobOptions_rec_any-300.txt jobOptions_rec_any-0.txt
        boss.condor -g physics -n 300 jobOptions_rec_any-%{ProcId}.txt
        ;;

    5.0.3) echo "Split Jpsi->anything MC sample with each group 5G ..."
	    ./python/get_samples.py  /besfs/groups/nphy/users/xiaosy/bes/jpsi2invi/v0.1/run/gen_mc/jpsi2any/job_text/dst run/samples/mc12_any/mc12_any_psip.txt 5G
	    # made 15 groups 
	    ;;





esac

