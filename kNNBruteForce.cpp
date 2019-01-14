#include <bits/stdc++.h>
using namespace std;

// 2D point object
struct point {
	double x, y;
	point(double x = 0, double y = 0): x(x), y(y) {}
};

double dist(double x, double y, double a, double b){
    return (x-a)*(x-a) + (y-b)*(y-b);
}

int main(){
    clock_t start = clock();
    int n,k;
    cout<<"Enter the number of points to be added in the 2D Plane : ";
    cin>>n;
    cout<<"Enter those points : \n";
    point p[n+5];
  /*  for(int i=0;i<n;i++){
        cin>>p[i].x>>p[i].y;
    } */
    fstream file("out.txt",ios_base::in);
    int a,b,i=0;
    while(file>>a){
        file>>b;
        p[i].x = a;
        p[i].y = b;
        i++;
    }
    cout<<"Points stored successfully from the file. \n";
    cout<<"\n\nNow, Enter the Query point and value of k(<=n) : \n";
    point t;
    cin>>t.x>>t.y>>k;
    priority_queue<pair<double,point*> > pq;
    for( i=0;i<n;i++){
        double d = dist(p[i].x,p[i].y,t.x,t.y);
        if(pq.size()<k || pq.top().first > d){
            pq.push(make_pair(d,&p[i]));
            if(pq.size()>k) pq.pop();
        }
    }
    vector<point> points;
    while(!pq.empty()){
        points.push_back(*pq.top().second);
        pq.pop();
    }
    reverse(points.begin(),points.end());
    cout<<"k Nearest points to "<<t.x<<" "<<t.y<<" are : \n";
    for( i=0;i<points.size();i++){
        cout<<points[i].x<<" "<<points[i].y<<"\n";
    }
    double duration = (clock() - start)/ (double) CLOCKS_PER_SEC;
    cout<<"Time Taken = "<<duration;
    return 0;
}
