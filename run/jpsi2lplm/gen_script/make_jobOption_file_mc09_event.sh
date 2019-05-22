#!/bin/bash

JobText_SaveDir=../job_text/mc09_event

for num in {1..106}
do
    jobOptions=jobOptions_jpsi2lplm_psip_mc09_event-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd ../../../../                                               " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events_lplm.py run/jpsi2lplm/rootfile_mc09/jpsi2lplm_psip_mc09-${num}.root run/jpsi2lplm/event_mc09/jpsi2lplm_psip_mc09_event-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

