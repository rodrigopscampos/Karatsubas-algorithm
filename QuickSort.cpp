int partition(int* arr, int begin, int end) {

	//not random pivot
	int pivot = arr[begin];
	int left = begin + 1;

	for (int right = begin + 1; right <= end; right++) {
		if (arr[right] < pivot) {
			swap(arr[left], arr[right]);
			left++;
		}
	}

	swap(arr[left - 1], arr[begin]);
	return left - 1;
}

void quicksort(int* arr, int begin, int end) {

	if (begin < end) {
		int p = partition(arr, begin, end);
		quicksort(arr, begin, p - 1);
		quicksort(arr, p + 1, end);
	}
}


int main()
{
  const int n = 5;
  int input[n] = {5,4,3,2,1};
  quicksort(input, 0, n - 1);
}
