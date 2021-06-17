#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<map>
#include<vector>
#include<stack>
using namespace std;

map<int, int> times;

int bookedTime(vector<int> appointments, int start) {
    if(start >= appointments.size()) {
        return 0;
    }
    map<int, int>::iterator it = times.find(start);
    if(it != times.end()) {
        return it->second;
    }
    int time = 0;
    int with, without;
    with = appointments[start] + bookedTime(appointments, start+2);
    without = bookedTime(appointments, start+1);
    time += (with>without)?with:without;
    printf("%d: with=%d, without=%d, time=%d\n",start,with,without,time);
    times.insert(make_pair(start, time));
    return time;
}

int main() {
    vector<int> appts{30, 15, 60, 75, 45, 15, 15, 45};
    printf("%d\n", bookedTime(appts, 0));
    return 0;
}