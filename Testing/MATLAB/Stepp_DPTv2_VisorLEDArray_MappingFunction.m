clear; clc;

VISOR_WIDTH  = 40;
VISOR_HEIGHT =  8;

x = 39;
y = 7;

% y = 7 = 7  |  -0
% y = 6 = 5  |  -1
% y = 5 = 3  |  -2
% y = 4 = 1  |  -3
% y = 3 = 6  |  +3
% y = 2 = 4  |  +2
% y = 1 = 2  |  +1
% y = 0 = 0  |  +0

% P = (VISOR_WIDTH*(VISOR_HEIGHT - (y + 1))) + (VISOR_WIDTH - (x + 1));

if y < (VISOR_HEIGHT/2)
    P = (VISOR_WIDTH*(VISOR_HEIGHT - ((2*y                     ) + 1))) + (VISOR_WIDTH - (x + 1));
    disp(P);
else
    P = (VISOR_WIDTH*(VISOR_HEIGHT - ((2*y - (VISOR_HEIGHT - 1)) + 1))) + (VISOR_WIDTH - (x + 1));
    disp(P);
end