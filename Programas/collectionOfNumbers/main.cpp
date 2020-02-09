#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

int main(){
	int n;
	int x;
	char oq;
	priority_queue<int> pq;
	while(cin >> oq){
		switch(oq){
			case 'S':
			cin >> n;
			pq.push(n);
			break;

			case 'A':
			if(pq.empty()) cout << "error!\n";
			else cout << pq.top();
			//pq.push();
			break;

			case 'R':
            if(pq.empty()) cout << "error!\n";
            else pq.pop();
			break;

			case 'I':
            if(pq.empty()) cout << "error!\n";
            else {cin >> n;
            x = pq.top() + n;
            pq.pop();
            pq.push(x);
			//cout << x;
			}
			break;

			case 'D':
            if(pq.empty()) cout << "error!\n";
            else {cin >> n;
            x = pq.top() - n;
            pq.pop();
            pq.push(x);
			//cout << x;
			}
			//pq.push(n);
			break;

			default:
                break;
		}
	}
	return 0;
}
