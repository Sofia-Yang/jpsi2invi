#!/bin/bash

JobText_SaveDir=../job_text/mc09

for num in {1..106}
do
    file_list=mc_664p01_psip_mc09_20G-${num}.txt
    rootfile=jpsi2invi_psip_mc09-${num}.root
    jobOptions=jobOptions_jpsi2invi_psip_mc09-${num}.txt
    echo   "#include \"\$ROOTIOROOT/share/jobOptions_ReadRec.txt\"        "  > ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$VERTEXFITROOT/share/jobOptions_VertexDbSvc.txt\" " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$MAGNETICFIELDROOT/share/MagneticField.txt\"      " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$ABSCORROOT/share/jobOptions_AbsCor.txt\"         " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$HOME/bes/jpsi2invi/v0.1/run/samples/mc09/$file_list\" " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "ApplicationMgr.DLLs += {\"Jpsi2invi\"};                       " >> ${JobText_SaveDir}/${jobOptions}
    echo   "ApplicationMgr.TopAlg += { \"Jpsi2invi\" };                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "// Set output level threshold (2=DEBUG, 3=INFO, 4=WARNING, 5=ERROR, 6=FATAL ) " >> ${JobText_SaveDir}/${jobOptions}
    echo   "MessageSvc.OutputLevel = 5;                                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "// Number of events to be processed (default is 10)           " >> ${JobText_SaveDir}/${jobOptions}
    echo   "//ApplicationMgr.EvtMax = 5000;                               " >> ${JobText_SaveDir}/${jobOptions}
    echo   "ApplicationMgr.EvtMax = -1;                                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "Jpsi2invi.IsMonteCarlo=\"true\";                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "Jpsi2invi.OutputFileName=\"/besfs/groups/nphy/users/xiaosy/bes/jpsi2invi/v0.1/run/jpsi2invi/rootfile_mc09/$rootfile\"; " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

