#!/bin/bash

JobText_SaveDir=job_text/jobs

for num in {1..10}
do
    jobOptions=jobOptions_jpsi2invi_gen_mc_ee_09_event-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd \$HOME/bes/jpsi2invi/v0.1                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events.py run/gen_mc/jpsi2ee_09/job_text/rootfile_ee_09/gen_mc_ee_09_jpsi2invi-${num}.root run/gen_mc/jpsi2ee_09/job_text/event_ee_09/invi/jpsi2invi_gen_mc_ee_09_event-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

