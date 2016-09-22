/*
Greedy algorithm:
Given n jobs with their weight, length and completion times, find the order in which they should be executed
to minimize the time.
*/
#include <iostream>
using namespace std;

class job {
public:
	int w; //weight
	int l; //length
	int c; //completion time
	int d; //w - l

public: 
	job() {}

	job(int weight, int length) {
		w = weight;
		l = length;
		d = w - l;
		c = 0;
	}
};
void merge(job *a, int start, int mid, int end) {
	int i = start, j = mid + 1;
	job *c = new job[end - start];
	int k = 0;
	while (i <= mid && j <= end) {
		if (a[i].d < a[j].d)
			c[k++] = a[i++];
		else if (a[i].d > a[j].d){
			c[k++] = a[j++];
		}
		else {
			if (a[i].w < a[j].w)
				c[k++] = a[i++];
			else
				c[k++] = a[j++];
		}
	}
	while (i <= mid) {
		c[k++] = a[i++];
	}
	while (j <= end) {
		c[k++] = a[j++];
	}
	k = 0;
	for (i = start; i <= end; i++)
		a[i] = c[k++];
}

void merge_sort(job *a, int start, int end) {
	if (start < end) {
		int mid = (start + end) / 2;
		merge_sort(a, start, mid);
		merge_sort(a, mid + 1, end);
		merge(a, start, mid, end);
	}
}

void compute_completion(job* jobs, int n) {
	for (int i = 0; i < n; i++) {
		jobs[i].c = i == 0 ? jobs[i].l : jobs[i - 1].c + jobs[i].l;
	}
}

int compute_w_sum(job* jobs, int n) {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += jobs[i].w*jobs[i].c;
	}
	return sum;
}

int main() {

	int n;
	cin >> n;

	job *jobs = new job[n];
	int w, l;
	for (int i = 0; i < n; i++) {
		cin >> w >> l;
		jobs[i] = job(w, l);
	}

	merge_sort(jobs, 0, n - 1);
	compute_completion(jobs, n);
	int weighted_sum = compute_w_sum(jobs, n);

	cout << weighted_sum;
	return 0;
}