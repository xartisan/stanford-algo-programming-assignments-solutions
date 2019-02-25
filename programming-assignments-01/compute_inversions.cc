/**
 * 斯坦福大学算法公开课 
 * 计算inversion数量
 * by xartisan
 * */
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

long long merge(std::vector<int> &splitArray, std::vector<int> &auxArray, int start, int mid, int end)
{
    int left = start, right = mid + 1;
    int numInversions = 0;

    for (int i = start; i <= end; i++)
    {
        int nextNum = 0;
        if (right > end || (left <= mid && auxArray[left] < auxArray[right]))
        {
            nextNum = auxArray[left];
            left += 1;
            numInversions += (right - mid - 1);
        }
        else
        {
            nextNum = auxArray[right];
            right += 1;
        }
        splitArray[i] = nextNum;
    }

    return numInversions;
}

long long computeInversions(std::vector<int> &inputs, std::vector<int> &tmp, int start, int end)
{
    // base case
    if (end <= start)
        return 0;
    // recursive case
    int mid = start + (end - start) / 2;
    // avoid copy by swap tmp and inputs position
    long long leftInversions = computeInversions(tmp, inputs, start, mid);
    long long rightInversions = computeInversions(tmp, inputs, mid + 1, end);
    long long splitInversions = merge(inputs, tmp, start, mid, end);
    return leftInversions + rightInversions + splitInversions;
}

int main()
{
    std::ifstream fin("IntegerArray.txt");
    std::string strNum;
    std::vector<int> inputs;
    while (std::getline(fin, strNum))
    {
        inputs.push_back(std::stoi(strNum));
    }

    std::vector<int> auxVector(inputs);
    std::cout << "inputs size is: " << inputs.size() << std::endl;
    long long ret = computeInversions(inputs, auxVector, 0, inputs.size() - 1);
    std::cout << "The answer is: " << ret << std::endl;
}