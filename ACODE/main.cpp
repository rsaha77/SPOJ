//
//  main.cpp
//  ACODE
//
//  Created by Saha, Rana on 3/8/20.
//  Copyright © 2020 Saha, Rana. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  string s;
  long long int ans[5010];
  while(true) {
    cin >> s;
    if (s[0] == '0') {
      break;
    }
    int len = (int)s.length();
    if (len == 1) {
      cout << 1 << endl;
      continue;
    }
    ans[0] = 1;
    int num = stoi(s.substr(0,2));
    if (s[1] == '0' and num != 10 and num != 20) {
      cout << 0 << endl;
      continue;
    }
    if(s[1] == '0' or num > 26) ans[1] = 1;
    else ans [1] = 2;
    if (len > 2) {
      for (int i=2; i<len; ++i) {
        string temp_s = s.substr(i-1,2);
        num = stoi(temp_s);
        if (s[i] == '0' and num != 10 and num != 20) {
          ans[len-1] = 0;
          break;
        }
        if (s[i] == '0') {
          ans [i] = ans [i - 2];
        } else if (s[i - 1] == '0' or num > 26) {
          ans [i] = ans [i - 1];
        } else {
          ans [i] = ans [i-1] + ans [i-2];
        }
      }
    }
    cout << ans[len-1] << endl;
  }
}
