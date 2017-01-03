function success = ldpc_decode(y, H, iter)
  M = y;
  [N1, N2] = size(H);
  for i = 1:iter
    for j = 1:N1
      ci = find(H(j,:) );
      d = find(M(ci) ~= -1);
      d1 = find(M(ci) == -1);
      if ((length(d) >= 2) & (length(d1) == 1) )
        E(j, ci(d1) ) = mod(sum(M(ci(d) ) ), 2);
      else
        E(j, ci(d1) ) = -1;
      end
    end
    for j=1:N2
      ri = find(H(:, j) );
      if (M(j) == -1)
        for ii = 1:length(ri)
          if (E(ri(ii), j) ~= -1)
            M(j) = E(ri(ii), j);
          end
        end
      end
    end
  end
  % disp('After decoding:');
  % M
  success = (sum(M) == 0);
end