
function iirsos_coeff_gen(coeff, gain, fname)
%
%  iirsos_coeff_gen(coeff, gain, fname)
%
%  Generates a "C" header file of IIR elliptic filter coefficients
%  for a 6th-order, lowpass, elliptic IIR
%
%Used for 
%
% Inputs:
%    "coeff" is the SOS matrix computed by the Matlab FDA tool
%    "gain" is the G vector calculated by the Matlab FDA tool
%    "fname" is the file the filter coefficients are written to.


% Validate input matrices dimensions
if isempty(coeff) || isempty(gain) || size(coeff, 2) ~= 6 || size(gain, 2) ~= 1
    error('Input matrices are not valid.  Please check');
end

% Get the number of sections
num_sections = length(gain) - 1;

fid = fopen(fname, 'wt');
if fid == -1
    error("Unable to open file for writing.");
end

% Header file contents start here
fprintf(fid, '//     File name: %s\n', fname);
fprintf(fid, "//     Filter coefficient file generated by iirsos_coeff_gen.m\n");

% Define the number of sections
fprintf(fid, '\n#define NUM_SECTIONS %d\n', num_sections);

% i is the interator through sections
fprintf(fid,'\nfloat b[NUM_SECTIONS][3] = { \n');
for i=1:num_sections
  if i==num_sections
    fprintf(fid,'{%2.8E, %2.8E, %2.8E} };\n',...
    coeff(i,1)*gain(i),coeff(i,2)*gain(i),coeff(i,3)*gain(i));
  else
    fprintf(fid,'{%2.8E, %2.8E, %2.8E},\n',...
    coeff(i,1)*gain(i),coeff(i,2)*gain(i),coeff(i,3)*gain(i));
  end
end

% Write the numerator coefficients 'a' in the C header file
% i is the interator through sections
fprintf(fid,'\nfloat a[NUM_SECTIONS][3] = { \n');
for i=1:num_sections
  if i==num_sections
    fprintf(fid,'{%2.8E, %2.8E, %2.8E} };\n',...
    coeff(i,4),coeff(i,5),coeff(i,6));
  else
    fprintf(fid,'{%2.8E, %2.8E, %2.8E},\n',...
    coeff(i,4),coeff(i,5),coeff(i,6));
  end
end

fclose(fid);

