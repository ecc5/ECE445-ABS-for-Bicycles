%Simulation File for the ABS Controller

open_system('BrakeSimulator_v2');
open_system('BrakeSimulator_v2/Motor Controller');

%%

Control = 1;

evalc('sim(''BrakeSimulator_v2'')');

%%

Time_ABS = out.Sd.Time; % Save the ABS results
Stop_ABS = out.Sd.Data;

%%

Control = 0;

evalc('sim(''BrakeSimulator_v2'')');

%%

Time_no_ABS = out.Sd.Time; %save the non-ABS results
Stop_no_ABS = out.Sd.Data;

%%

plot(Time_ABS, Stop_ABS, Time_no_ABS, Stop_no_ABS); %code not shown in example
xlabel('Slip Time (sec)'); 
ylabel('Stopping Distance (ft)');
legend('With ABS','Without ABS','Location','SouthEast');
title('Stopping distance for hard braking with and without ABS');

%%

close_system('BrakeSimulator_v2', 0);
close_system('BrakeSimulator_v2/Motor Controller', 0);
clear sldemo_absbrake_output Stop_ABS Stop_no_ABS Time_ABS Time_no_ABS;
clear mex;