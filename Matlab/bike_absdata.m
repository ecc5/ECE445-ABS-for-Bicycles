%MotorProto_ABSDATA 
%   Initialization data for the SLDEMO_ABSBRAKE braking model.
%   Places model parameters in the MATLAB workspace when typed at the
%   command line 
%
%   See also SLDEMO_ABSBRAKE, SLDEMO_ABSBRAKEPLOTS

%   Author(s): L. Michaels, S. Quinn, 12/01/97 
%   Modified : G. Chistol,            08/04/07
%
%   Copyright 1990-2006 The MathWorks, Inc.

g = 32.18;
v0 = 88;
r = 0.30;  % Wheel radius
Kf = 1;
m = 50;
PBmax = 1500;
TB = 0.01;
I = 5;
k1 = .7;
k2 = .23;
Control = 1;

k3 = .5; %wheel speed sensor IIR tuning
k4 = .5; %vehicle speed sensor IIR tuning

%
% Mu slip curve
%
slip = (0:.05:1.0); 
mu = [0 .4 .8 .97 1.0 .98 .96 .94 .92 .9 .88 .855 .83 .81 .79 .77 .75 .73 .72 .71 .7];
ctrl = 1;

