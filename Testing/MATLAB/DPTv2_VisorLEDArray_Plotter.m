clear;clc;
height = 8;
width = 40;
for i = 0:height-1
   for j = 0:width-1
       plot(j,i,'ko');
       hold on;
   end
end
hold off;
axis equal;
xlim([-1 width]);
ylim([-1 height]);
grid on;
grid minor;