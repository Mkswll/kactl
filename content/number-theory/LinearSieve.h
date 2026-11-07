/**
 * Author: Maxwell He
 * Date: 
 * License: 
 * Source: 
 * Description: 
 */
#pragma once

struct Sieve {
	int n;
	vector<int> lp, mu, phi;
	vector<int> pr;
	Sieve(): n{0} {}
	Sieve(int n_): n{n_} {
		lp.assign(n_ + 1, 0);
		// mu.assign(n_ + 1, 0);
		// phi.assign(n_ + 1, 0);
		// phi[1] = 1;
	    // mu[1] = 1;
	    for (int i = 2; i <= n; ++i) {
	        if (lp[i] == 0) {
	            lp[i] = i;
	            // mu[i] = -1;
	            // phi[i] = i - 1;
	            pr.push_back(i);
	        }
	        for (int j = 0; i * pr[j] <= n; ++j) {
	            lp[i * pr[j]] = pr[j];
	            if (pr[j] == lp[i]) {
	                // phi[i * pr[j]] = pr[j] * phi[i];
	                break;
	            }
	            // mu[i * pr[j]] = -mu[i];
	            // phi[i * pr[j]] = (pr[j] - 1) * phi[i];
	        }
	    }
	}
	
	bool is_prime(int x) {
		assert(x >= 1 && x <= n);
		return lp[x] == x;
	}
};
