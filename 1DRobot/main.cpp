#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <numeric>

using namespace std;

vector <float> sense(vector <float> p, string z, vector <string> world, float pHit, float pMiss);
vector <float> move1(vector <float> p, int u, float pExact, float pOvershoot, float pUndershoot);

int main(){
    vector <float> p = {0.2, 0.2, 0.2, 0.2, 0.2};
    vector <string> world = {"green", "red", "red", "green", "green"};
    vector <string> measurements = {"red", "green"};
    vector <int> motions = {1,1};
    float pHit = 0.6;
    float pMiss = 0.2;
    float pExact = 0.8;
    float pOvershoot = 0.1;
    float pUndershoot = 0.1;

    for (int i = 0; i < 2; i++){
        p = sense(p, measurements[i], world, pHit, pMiss);
        p = move1(p, motions[i], pExact, pOvershoot, pUndershoot);
    }
    for (int l = 0; l < p.size(); l++){
        cout << p[l] << "  ";
    }
    cout << endl;
    return 0;
}

vector <float> sense(vector <float> p, string z, vector <string> world, float pHit, float pMiss){
    vector <float> q(5,1);
    float sum;
    int hit;

    for (int i = 0; i < p.size(); i++){
        if (world[i].compare(z) == 0 ){
            hit = 1;
        } else{
            hit = 0;
        }
        q[i] = p[i] * (hit * pHit + (1-hit) * pMiss);
    }

    for (int ik = 0; ik < q.size(); ik++){
        sum = sum + q[ik];
    }

    for (int j = 0; j < q.size(); j++){
        q[j] = q[j]/sum;
    }
    return q;
}


vector <float> move1(vector <float> p, int u, float pExact, float pOvershoot, float pUndershoot){
    vector <float> q(5,0);
    float s;
    for (int i = 0; i < p.size(); i++){
        s = pExact * p[(i-u+5) % p.size()];
        s = s + pOvershoot * p[(i-u-1+5) % p.size()];
        s = s + pUndershoot * p[(i-u+1+5) % p.size()];
        q[i] = s;
    }
    return q;
}
