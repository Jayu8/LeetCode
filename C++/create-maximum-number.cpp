// Time:  O(k * n^2)
// Space: O(k * n)

// DP + Greedy solution. (48ms)
class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> res(k);
        const int size1 = nums1.size(), size2 = nums2.size();
        vector<vector<int>> maxDigits1(k + 1), maxDigits2(k + 1);
        getmaxDigits(nums1, max(0, k - size2), min(k, size1), &maxDigits1);  // O(k * n) time
        getmaxDigits(nums2, max(0, k - size1), min(k, size2), &maxDigits2);  // O(k * n) time
        for (int i = max(0, k - size2); i <= min(k, size1); ++i) {  // O(k * n^2) time
            int j = k - i;
            vector<int> tmp(k);
            merge(maxDigits1[i], maxDigits2[j], &tmp);
            if (compareVector(tmp, res)) {
                res = tmp;
            }
        }
        return res;
    }

    void getmaxDigits(vector<int> nums, int start, int end, vector<vector<int>> *maxDigits) {
        (*maxDigits)[end] = maxDigit(nums, end);
        for (int i = end - 1; i >= start; --i) {
            (*maxDigits)[i] = deleteDigit((*maxDigits)[i + 1]);
        }
    }

    // Time:  O(n)
    // Space: O(n)
    vector<int> maxDigit(const vector<int>& nums, int k) {
        vector<int> res;
        int delete_cnt = nums.size() - k;
        for (const auto& num : nums) {
            while (delete_cnt > 0 && !res.empty() && res.back() < num) {
                res.pop_back();
                --delete_cnt;
            }
            res.emplace_back(num);
        }
        while (delete_cnt > 0) {
            res.pop_back();
            --delete_cnt;
        }
        return res;
    }

    // Time:  O(n)
    // Space: O(n)
    vector<int> deleteDigit(const vector<int>& nums) {
        vector<int> res(nums);
        for (int j = 0; j < res.size(); ++j) {
            if (j == res.size() - 1 || res[j] < res[j + 1]) {
                res.erase(res.begin() + j);
                break;
            }
        }
        return res;
    }

    // Time:  O(n)
    // Space: O(1)
    bool compareVector(const vector<int>& vec1, const vector<int>& vec2) {
        auto first1 = vec1.begin(), last1 = vec1.end(), first2 = vec2.begin(), last2 = vec2.end();
        for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
            if (*first1 > *first2) {
                return true;
            } else if (*first1 < *first2) {
                return false;
            }
        }
        if (first1 == last1) {
            return false;
        } else {
            return true;
        }
    }

    // Time:  O(n^2)
    // Space: O(1)
    void merge(const vector<int>& vec1, const vector<int>& vec2, vector<int> *res) {
        auto first1 = vec1.begin(), last1 = vec1.end(),
             first2 = vec2.begin(), last2 = vec2.end();
        auto result = res->begin();
        while (true) {
            if (first1 == last1) {
                std::copy(first2, last2, result);
                return;
            }
            if (first2 == last2) {
                std::copy(first1, last1, result);
                return;
            }
            if (*first2 > *first1) {
                *result++ = *first2++;
            } else if (*first2 < *first1) {
                *result++ = *first1++;
            } else {
                auto pos1 = first1, pos2 = first2;
                while (true) {  // Worst case O(n^2) time.
                    int val1 = (++pos1 != last1) ? *(pos1) : numeric_limits<int>::min();
                    int val2 = (++pos2 != last2) ? *(pos2) : numeric_limits<int>::min();
                    if (val1 > val2) {
                        *result++ = *first1++;
                        break;
                    } else if (val1 < val2) {
                        *result++ = *first2++;
                        break;
                    }
                }
            }
        }
    }
};