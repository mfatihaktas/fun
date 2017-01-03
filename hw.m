close all; clear all; clc;

% addpath('/cac/u01/mfa51/Desktop/fun');
% path(path, genpath('/cac/u01/mfa51/Desktop/fun') );

n = 900 % 240 % 24; % Number of columns

num_iter_v_size = 4
max_num_iter = 100;
num_iter_v = zeros(1, num_iter_v_size);
num_eps = 20;
eps_v = zeros(1, num_eps);
err_rate_v = zeros(1, num_eps);

num_graph = 10
num_trials_per_graph = 10

h = figure;
hold all
for num_iter = 10:max_num_iter/num_iter_v_size:max_num_iter
  num_iter
  k = 0;
  for epsilon = 1/num_eps:1/num_eps:1
    k = k + 1;
    eps_v(k) = epsilon;
    for g = 1:num_graph
      H = ldpc_parity_check(n);
      success_v = zeros(1, num_trials_per_graph);
      for t = 1:num_trials_per_graph;
        y = zeros(1, n);
        for i = 1:n
          if (rand() < epsilon)
            y(i) = -1;
          end
        end
        success_v(t) = ldpc_decode(y, H, num_iter);
      end
      % epsilon
      success_rate = sum(success_v)/num_trials_per_graph;
      err_rate_v(k) = 1 - success_rate;
    end
  end
  % plot(eps_v, err_rate_v, '-o')
  disp('Plotting');
  eps_v
  err_rate_v
  % plot(eps_v, err_rate_v, 'color', rand(1, 3) )
  plot(eps_v, err_rate_v, 'LineWidth', 2, 'color', rand(1, 3) )
  % hold on
  set(gca, 'ColorOrderIndex', 1)
end
% eps_v
% err_rate_v
xlabel('epsilon')
ylabel('Error rate')
% print(figure, '-dpng', 'exp.png')
saveas(h, 'exp.png')

% x = [2 4 7 2 4 5 2 5 1 4];
% bar(x);
% saveas(gcf, 'deneme.png')
% filename = '/cac/u01/mfa51/Desktop/fun/deneme.png'
% saveas(fig, filename)

% print(figure, 'hw.png')

