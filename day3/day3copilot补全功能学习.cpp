//归并排序算法实现
//C++
#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

void merge(vector<int>& nums, int left, int mid, int right) {
    vector<int> temp(right - left + 1);//临时数组存储合并结果
    int i = left, j = mid + 1, k = 0;
            
    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j]) {
            temp[k++] = nums[i++];
        } else {
            temp[k++] = nums[j++];//将较小的元素放入临时数组
        }
    }

    while (i <= mid) {
        temp[k++] = nums[i++];//将剩余的元素放入临时数组
    }

    while (j <= right) {
        temp[k++] = nums[j++];
    }

    for (int p = 0; p < k; p++) {
        nums[left + p] = temp[p];//将合并后的结果复制回原数组
    }
}

void mergeSort(vector<int>& nums, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(nums, left, mid);//递归排序左半部分
        mergeSort(nums, mid + 1, right);
        merge(nums, left, mid, right);
    }
}

int main() {
    //record time
    clock_t start, end;
    start = clock();
    //generate 500000numbers
    srand((unsigned int)time(NULL));
    vector<int> nums(500000);
    for (int i = 0; i < 500000; i++) {
        nums[i] = rand() % 1000000;//生成随机数
    }
    
    

    mergeSort(nums, 0, nums.size() - 1);

    //cout the first 100 numbers
    cout << "Sorted array: ";
    for (int i = 0; i < 100 && i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
end = clock();
    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time taken: " << duration << " seconds" << endl;
    return 0;
}
