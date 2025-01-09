// Bomber fighter 

#include<bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

double distance(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    srand(time(0));

    Point bomber = {0.0, 0.0};
    Point destination = {100.0, 100.0};

    Point fighter = {50.0, 50.0};

    const double bomberSpeed = 1.0;   // Units per step
    const double fighterSpeed = 1.5;  // Units per step
    const double captureDistance = 1.0; // Distance at which fighter captures bomber
    int steps = 0;

    cout << "Starting simulation...\n";
    while (distance(bomber, destination) > 0.1) {
        steps++;
        // Calculate direction vector for bomber (towards destination)
        double bomberDirX = (destination.x - bomber.x) / distance(bomber, destination);
        double bomberDirY = (destination.y - bomber.y) / distance(bomber, destination);

        // Move bomber
        bomber.x += bomberDirX * bomberSpeed;
        bomber.y += bomberDirY * bomberSpeed;

        // Calculate direction vector for fighter (towards bomber)
        double fighterDirX = (bomber.x - fighter.x) / distance(bomber, fighter);
        double fighterDirY = (bomber.y - fighter.y) / distance(bomber, fighter);

        // Move fighter
        fighter.x += fighterDirX * fighterSpeed;
        fighter.y += fighterDirY * fighterSpeed;

        // Check if fighter captures bomber
        if (distance(bomber, fighter) <= captureDistance) {
            cout << "Fighter captured the bomber in " << steps << " steps!\n";
            return 0;
        }
    }

    cout << "Bomber reached the destination in " << steps << " steps!\n";

    return 0;
}


// Chemical reaction 


#include <bits/stdc++.h>
#include <cmath>
using namespace std;
void simulateReaction(double initialConcentrationA, double rateConstant, double timeStep, double totalTime) {
    double concentrationA = initialConcentrationA;
    double concentrationB = 0.0;
    double concentrationC = 0.0;
    double time = 0.0;

    cout << "Time " << setw(30) << "Concentration_A " << setw(30) << "Concentration_B " << setw(30) << "Concentration_C\n";

    while (time <= totalTime) {
        std::cout << time << setw(30) << concentrationA << setw(30) << concentrationB << setw(30) << concentrationC << "\n";

        double dA = -rateConstant * concentrationA * timeStep;
        double dB = -dA;
        double dC = -dA;

        concentrationA += dA;
        concentrationB += dB;
        concentrationC += dC;

        time += timeStep;
    }
}

int main() {
    double initialConcentrationA = 1.0;  // Initial concentration of A (mol/L)
    double rateConstant = 0.1;           // Rate constant (1/s)
    double timeStep = 0.1;               // Time step (s)
    double totalTime = 1.0;             // Total simulation time (s)

    simulateReaction(initialConcentrationA, rateConstant, timeStep, totalTime);

    return 0;
}


/// Document 
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int i, N, WT[50] , ST = 0, FT = 0, CT = 0;
    char F = 'N';
    cout << "Enter Number of Documents: " << endl;
    cin >> N;
    cout << "Enter Work Time for each documents: " << endl;
    for(i=0; i<N; i++)
        cin >> WT[i];
    cout<<"JOB_NO \t START_TIME \t WORK_TIME \t FINISH_TIME \t CUMULATIVE_TIME \t FLAG \t PENDING_JOBS " << endl;
    for(i=0; i<N; i++) {
        FT += WT[i];
        CT += WT[i];
        if (CT > 60) {
            F = 'Y';
        }
        else {
            F = 'N';
        }
        cout<<i+1<<" \t "<<ST<<" \t\t "<<WT[i]<<" \t\t "<<FT<<" \t\t "<<CT<<" \t\t\t "<<F<<" \t "<<N-i-1<<endl;
        ST = FT;
        if(CT > 60)
        {
            CT=0;
            ST+=5;
            FT+=5;
        }
    }
}


/// Monte carlo

#include <iostream>
#include <cstdlib>   // For rand() and srand()
#include <cmath>     // For sqrt()
#include <ctime>     // For time()
using namespace std;
int main() {
    const int numPoints = 1000000;
    int pointsInsideCircle = 0;

    srand(time(0));

    for (int i = 0; i < numPoints; ++i) {
        double x = (double)(rand()) / RAND_MAX;
        double y = (double)(rand()) / RAND_MAX;

        if (sqrt(x * x + y * y) <= 1.0) {
            pointsInsideCircle++;
        }
    }

    double piEstimate = 4.0 * pointsInsideCircle / numPoints;

    cout << "Estimated value of pi: " << piEstimate << endl;

    return 0;
}


/// single server queue

#include<bits/stdc++.h>
using namespace std;
const int N = 100;
int AT[N],ST[N],CAT[N],IDT[N],QL[N],CDT[N];
int32_t main() {
    cout << "Enter number of N : "; int n; cin >> n;
    cout << "Enter arrival times : ";
    for(int i=1; i<=n; i++) cin >> AT[i];
    cout << "Enter service times : ";
    for(int i=1; i<=n; i++) cin >> ST[i];
    for(int i=1; i<=n; i++) CAT[i] = CAT[i-1] + AT[i];
    int i = 2, j = 1;
    int NAT = CAT[2], NDT = CDT[1] = ST[1]; int clock = 0,dif;
    vector<int> nat,ndt,CLK,II,JJ;
    nat.push_back(NAT); ndt.push_back(NDT); CLK.push_back(clock);
    II.push_back(i); JJ.push_back(j);
    while(1) {
        if(i > n) {
            clock = NDT; CDT[j+1] = CDT[j]+ST[j+1]; NDT = CDT[j+1]; j++;
            ndt.push_back(NDT); CLK.push_back(clock); JJ.push_back(j);
        }
        else {
            dif = NAT - NDT;
            if(dif == 0) {
                QL[i] = QL[i-1]; clock = NAT; NAT = CAT[i+1];
                CDT[j+1] = CAT[i]+ST[j+1]; NDT = CDT[j+1]; j++, i++;
                nat.push_back(NAT); ndt.push_back(NDT); CLK.push_back(clock);
                II.push_back(i); JJ.push_back(j);
            }
            else if(dif < 0) {
                clock = NAT; NAT = CAT[i+1]; QL[i] = i-j; i++;
                nat.push_back(NAT); CLK.push_back(clock); II.push_back(i);
                continue;
            }
            else {
                if(i-j > 1) {
                    clock = NDT; CDT[j+1] = CDT[j]+ST[j+1];
                    NDT = CDT[j+1]; j++;
                    ndt.push_back(NDT); CLK.push_back(clock); JJ.push_back(j);
                }
                else {
                    IDT[i] = dif; clock = NAT; NAT = CAT[i+1];
                    CDT[j+1] = CAT[i]+ST[j+1]; NDT = CDT[j+1]; j++, i++;
                nat.push_back(NAT); ndt.push_back(NDT); CLK.push_back(clock);
                    II.push_back(i); JJ.push_back(j);
                }
            }
        }
        if(j >= n) {
            cout << "CAT's are : ";
            for(int i=1; i<=n; i++) cout << CAT[i] << " ";
            cout << endl << "QL length are : ";
            for(int i=1; i<=n; i++) cout << QL[i] << " ";
            cout << endl << "IDT's are : ";
            for(int i=1; i<=n; i++) cout << IDT[i] << " ";
            cout << endl << "CDT's are : ";
            for(int i=1; i<=n; i++) cout << CDT[i] << " ";
            cout << endl;
            break;
        }
        else {
            continue;
        }
    }
    cout << endl << "I : ";
    for(auto x:II) cout << x << ", ";
    cout << endl << "J : ";
    for(auto x:JJ) cout << x << ", ";
    cout << endl << "NAT : ";
    for(auto x:nat) cout << x << ", ";
    cout << endl << "NDT : ";
    for(auto x:ndt) cout << x << ", ";
    cout << endl << "CLOCK : ";
    for(auto x:CLK) cout << x << ", ";
    cout << endl;
    return 0;
}
