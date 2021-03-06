%% Parameter calculator for TI LMR 16020 switching regulator
% Last modified: B. Weinberg 8/JUL/2018
% Reference: https://www.ti.com/product/LMR16020


% CBEs:
    % 3.3 V: 0.25 A
    % 5 V  : 1.75 A
    % 12 V : 0.75 A
V_in = 28; % Volts
V_out = 5; % Volts 
Vin_Max = 34; % Volts
I_out = 1.75; % Amps
L = 10e-6; % H

max_overshoot_fraction = 0.05;
max_undershoot_fraction = 0.05;

D = V_out / V_in;

R_fbb = 13.3e3; % Ohms
R_fbt = (V_out - .75)*(R_fbb / 0.75); % Ohms; datasheet eqn. 6

f_sw = 1e6; % Hz
Rt = 42904 * (f_sw/1e3)^-1.088; % Ohms; datasheet eqn. 7

K_L = 0.4;

L_min = ((Vin_Max - V_out) / (I_out * K_L)) * (V_out / (Vin_Max * f_sw)); % H; datasheet eqn. 9

if L < L_min
    warning('Inductance too low.');
end % if

delta_I_L = V_out*(Vin_Max - V_out)./(Vin_Max*L*f_sw); % A; datasheet eqn. 8

V_us = max_undershoot_fraction*V_out;
V_os = max_overshoot_fraction*V_out;

C_out_min_1 = 3*I_out/(f_sw*V_us); % Datasheet eqn. 12
C_out_min_2 = L*I_out^2/((V_out + V_os)^2 - V_out^2); % Datasheet eqn. 13
C_out_min = min(C_out_min_1, C_out_min_2);

% Print output:
R_fbt
L_min
C_out_min
    

