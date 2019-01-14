#include <bits/stdc++.h>
#include <fstream>
using namespace std;

// 2D point object
struct point {
	double x, y;
	point(double x = 0, double y = 0): x(x), y(y) {}
};

// use comparators for all dimensions
bool cmpx(const point& a, const point& b) {return a.x < b.x;}
bool cmpy(const point& a, const point& b) {return a.y < b.y;}

struct qdtree {
	point *tree;
	int n;
	// constructor
	qdtree(point p[], int n): tree(new point[n]), n(n) {
		copy(p, p + n, tree);
		build(0, n, false);
	}
	// destructor
	~qdtree() {delete[] tree;}
	// k-nearest neighbor query, O(k log(k) log(n)) on average
	vector<point> query(double x, double y, int k = 1) {
		perform_query(x, y, k, 0, n, false); // recurse
		vector<point> points;
		while (!pq.empty()) { // collect points
			points.push_back(*pq.top().second);
			pq.pop();
		}
		reverse(points.begin(), points.end());
		return points;
	}
private:
	// build is O(n log n) using divide and conquer
	void build(int L, int R, bool dvx) {
		if (L >= R) return;
		int M = (L + R) / 2;
		// get median in O(n), split x-coordinate if dvx is true
		nth_element(tree+L, tree+M, tree+R, dvx?cmpx:cmpy);
		build(L, M, !dvx); build(M+1, R, !dvx);
	}

	// priority queue for KNN, keep the K nearest
	priority_queue<pair<double, point*> > pq;
	void perform_query(double x, double y, int k, int L, int R, bool dvx) {
		if (L >= R) return;
		int M = (L + R) / 2;
		double dx = x - tree[M].x;
		double dy = y - tree[M].y;
		double delta = dvx ? dx : dy;
		double dist = dx * dx + dy * dy;
		// if point is nearer to the kth farthest, put point in queue
		if (pq.size() < k || dist < pq.top().first) {
			pq.push(make_pair(dist, &tree[M]));
			if (pq.size() > k) pq.pop(); // keep k elements only
		}
		int nearL = L, nearR = M, farL = M + 1, farR = R;
		if (delta > 0) { // right is nearer
			swap(nearL, farL);
			swap(nearR, farR);
		}
                // query the nearer child
		perform_query(x, y, k, nearL, nearR, !dvx);

		if (pq.size() < k || delta * delta < pq.top().first)
                        // query the farther child if there might be candidates
			perform_query(x, y, k, farL, farR, !dvx);
	}
};


int main(){
    clock_t start = clock();
    int n,k;
    cout<<"Enter the number of points to be added in the 2D Plane : ";
    cin>>n;
    cout<<"Enter those points : \n";
    point p[n+5];
   /* for(int i=0;i<n;i++){
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
    qdtree x(p,n);
    cout<<"\n\nNow, Enter the Query point and value of k(<=n) : \n";
    point t;
    cin>>t.x>>t.y>>k;
    vector<point> ans = x.query(t.x,t.y,k);
    cout<<"k Nearest points to "<<t.x<<" "<<t.y<<" are : \n";
    for( i=0;i<ans.size();i++){
        cout<<ans[i].x<<" "<<ans[i].y<<"\n";
    }
    double duration = (clock() - start)/ (double) CLOCKS_PER_SEC;
    cout<<"Time Taken = "<<duration;
    return 0;
}
