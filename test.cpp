#include <map>
#include <vector>

int majorityElement(const std::vector<int>& nums) 
{
    const size_t vect_size = nums.size();
    const size_t majority_num = vect_size / 2;

    // First: element
    // Second: frequency
    std::map<int, int> frequencies {};
    bool has_highest_elem_key_set = false;
    int highest_elem_key {};

    for (const int n : nums) 
    {
        if (frequencies.find(n) == frequencies.end())
        {
            frequencies.emplace(n, 1);
        }
        else
        {
            frequencies.at(n)++;
        }

        if (!has_highest_elem_key_set)
        {
            has_highest_elem_key_set = true;
            highest_elem_key = n;
        }

        else if (frequencies.at(n) >= frequencies.at(highest_elem_key))
            highest_elem_key = n;
    }

    return frequencies.at(highest_elem_key);

}


int main()
{
    std::vector<int> nums {3, 2, 3};
    majorityElement(nums);
}
