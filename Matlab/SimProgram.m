%Simulation File for the ABS Controller

clf

open_system('BrakeSimulator_v2');

%%
% open_system('BrakeSimulator_v2/Motor Controller');

%%

Control = 1;
%% 

% evalc('sim(''BrakeSimulator_v2'')');
out = sim('BrakeSimulator_v2');

%%

Time_ABS = out.Sd.Time; % Save the ABS results
Stop_ABS = out.Sd.Data;
W_Time_ABS = out.w.Time;
W_Speed_ABS = out.w.Data;
V_Time_ABS = out.v.Time;
V_Speed_ABS = out.v.Data;

%%

Control = 0;

% evalc('sim(''BrakeSimulator_v2'')');
out = sim('BrakeSimulator_v2');

%%

Time_no_ABS = out.Sd.Time; %save the non-ABS results
Stop_no_ABS = out.Sd.Data;
W_Time_no_ABS = out.w.Time;
W_Speed_no_ABS = out.w.Data;
V_Time_no_ABS = out.v.Time;
V_Speed_no_ABS = out.v.Data;

%%

figure(1)
plot(Time_ABS, Stop_ABS, Time_no_ABS, Stop_no_ABS); %code not shown in example
xlabel('Slip Time (sec)'); 
ylabel('Stopping Distance (ft)');
legend('With ABS','Without ABS','Location','SouthEast');
title('Stopping distance for hard braking with and without ABS');

figure(2)
plot(W_Time_ABS,W_Speed_ABS,V_Time_ABS,V_Speed_ABS);
xlabel('Slip Time (sec)');
ylabel('Theoretical Wheel Speeds (rad/s)');
legend('Vehicle','Brake Wheel','Location','SouthEast');
title('Projected wheel speeds for hard braking with ABS');

figure(3)
plot(W_Time_no_ABS,W_Speed_no_ABS,V_Time_no_ABS,V_Speed_no_ABS);
xlabel('Slip Time (sec)');
ylabel('Theoretical Wheel Speeds (rad/s)');
legend('Vehicle','Brake Wheel','Location','SouthEast');
title('Projected wheel speeds for hard braking without ABS');

% plot(Time_ABS, Stop_ABS);
% xlabel('Slip Time (sec)'); 
% ylabel('Stopping Distance (ft)');
% legend('With ABS','Location','SouthEast');
% title('Stopping distance for hard braking with ABS');

%%

% close_system('BrakeSimulator_v2', 0);
% close_system('BrakeSimulator_v2/Motor Controller', 0);
% clear sldemo_absbrake_output Stop_ABS Stop_no_ABS Time_ABS Time_no_ABS;
% clear mex;