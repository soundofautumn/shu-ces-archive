clear all;
close all;

A = [1; 0.5];
B = [0.1; 0.5; 1];
C = [0.2; 1];

% Compound of A and B
AB = zeros(length(A), length(B));
for i = 1:length(A)
    for j = 1:length(B)
        AB(i, j) = min(A(i), B(j));
    end
end

% Transfer to Column
T1 = AB(:);

% Get fuzzy R
R = zeros(length(T1), length(C));
for i = 1:length(T1)
    for j = 1:length(C)
        R(i, j) = min(T1(i), C(j));
    end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
A1 = [0.8; 0.1];
B1 = [0.5; 0.2; 0];

% Compound of A1 and B1
AB1 = zeros(length(A1), length(B1));
for i = 1:length(A1)
    for j = 1:length(B1)
        AB1(i, j) = min(A1(i), B1(j));
    end
end

% Transfer to Row
T2 = AB1(:)';

% Get output C1
D = zeros(length(T2), length(C));
C1 = zeros(1, length(C));
for i = 1:length(T2)
    for j = 1:length(C)
        D(i, j) = min(T2(i), R(i, j));
    end
end

for j = 1:length(C)
    C1(j) = max(D(:, j));
end

C1
