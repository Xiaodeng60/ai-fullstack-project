//归并排序算法实现
//C++
#include <iostream>
#include <vector>
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
    vector<int> nums = {12, 11, 13, 5, 6, 7};
    cout << "Original array: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    mergeSort(nums, 0, nums.size() - 1);

    cout << "Sorted array: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
