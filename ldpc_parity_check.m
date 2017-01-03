function H = ldpc_parity_check(n)
  w_c = 3; % Column weight
  w_r = 6; % Row weight
  k = n*w_c/w_r; % Number of rows
  
  H_sub = zeros(n/w_r,n); % First sub-matrix; there are w_c such sub-matrices.
  %% Generation of Basic Sub-matrix
  for i = 1:n/w_r
    for j = (i-1)*w_r+1:i*w_r
      H_sub(i,j) = H_sub(i,j) + 1;
    end
  end
  %% Permutation of Basic Sub-matrix
  H_pre = H_sub;
  for t = 2:w_c
    x = randperm(n);
    H_sub_perm = H_sub(:,x);
    H_pre = [H_pre H_sub_perm];
  end
  
  H = zeros(k,n);
  for p = 1:w_c
    H((p-1)*(n/w_r)+1:(p)*(n/w_r),1:n) = H((p-1)*(n/w_r)+1:(p)*(n/w_r),1:n) + H_pre(:,(p-1)*n+1:p*n);
  end