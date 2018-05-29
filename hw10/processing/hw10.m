fid = fopen('hw10.txt','rt');
A = fscanf(fid,'%f',[100 4]);
fclose(fid);
x = 0:99;
x1 = [];
x2 = [];
x3 = [];
x4 = [];
x0 = [];
for ii = 1:4
    for jj = 1:100
        x0 = [x0 A(jj,ii)];
    end
end

for ii = 0:99
    a = 1 +4*ii;
    b = 2 +4*ii;
    c = 3 +4*ii;
    d = 4 +4*ii;
    x1 = [x1 x0(a)]; 
    x2 = [x2 x0(b)];
    x3 = [x3 x0(c)];
    x4 = [x4 x0(d)];
end


plot(x,x1, x,x2,x,x3,x,x4);
legend('zraw','moving average','iir','fir');
title('DSP techniques');
