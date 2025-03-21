#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

std::vector<std::vector<short int>> permut(std::vector<float>& data) {
	std::vector<std::vector<short int>> res;
	res.reserve(1275);
	short int datasize = data.size();
	for (short int i1 = 0; i1 < datasize; i1++){
		for (short int i2 = 0; i2 < datasize; i2++){
			for (short int i3 = 0; i3 < datasize; i3++){
				for (short int i4 = 0; i4 < datasize; i4++){
					for (short int i5 = 0; i5 < datasize; i5++){
						for (short int i6 = i5 + 1; i6 < datasize; i6++){
							for (short int i7 = i6 + 1; i7 < datasize; i7++){
								for (short int i8 = i7+1; i8 < datasize; i8++){
									for (short int i9 = i8+1; i9 < datasize; i9++){

										if ((data[i1] + data[i2] + data[i3] + data[i4] + data[i5] + data[i6] + data[i7] + data[i8] + data[i9] == 0) &&
											(i9 > i8) && (i8 > i7) && (i7 > i6) && (i6 > i5) && (i5 > i4) && (i4 > i3) && (i3 > i2) && (i2 > i1)) {
											std::cout << '[' << i1 << ' ' << i2 << ' ' << i3 << ' ' << i4 << ' ' << i5 << ' ' << i6 << ' ' << i7 << ' ' << i8 << ' ' << i9 << ']' << std::endl;
											res.push_back({ i1 , i2 , i3 , i4 , i5 , i6 , i7 , i8 ,i9 });
										}
									}}}}}}}}}
	return res;
}

void test1() {
	std::vector<float> r = { 234, -221, 34, -43, -543, 123, 345, -12, 53, 634, -77, 11, 4, 6, -77, 9, 0 };
	assert(permut(r).size() > 1);
	std::cout << "Test with more than one combination: Successeful!" << std::endl;
}


void test2() {
	std::vector<float> r = { 1, -1, 1, -1, 1 , -1, 1, -1, 0 };
	assert(permut(r).size() == 1);
	std::cout << "Test with one possible combination: Successeful!" << std::endl;
}

void test3() {
	std::vector<float> r = { 1, 3, 4, 5, 6, 7, 8, 8, 9, 3, 2, 8, 3 };
	assert(permut(r).size() == 0);
	std::cout << "Test with zero possible combination: Successeful!" << std::endl;
}


int main() {
	//test1();
	//test2();
	//test3();

	//std::vector<float> r = { 0 };
	std::vector<float> r = { 234, -221, 34, -43, -543, 123, 345, -12, 53 };
	//std::vector<float> r = { 234, -221, 34, -43, -543, 123, 345, -12, 53, 634, -77, 11 };
	//std::vector<float> r = { 234, -221, 34, -43, -543, 123, 345, -12, 53, 634, -77, 11, 4, 6, -77 };
	//std::vector<float> r = { 234, -221, 34, -43, -543, 123, 345, -12, 53, 634, -77, 11, 4, 6, -77, 9, 0, 55};
	//std::vector<float> r = { 234, -221, 34, -43, -543, 123, 345, -12, 53, 634, -77, 11, 4, 6, -77, 9, 0, 55, -1, -5, -41 };
	//std::vector<float> r = { 234, -221, 34, -43, -543, 123, 345, -12, 53, 634, -77, 11, 4, 6, -77, 9, 0, 55, -1, -5, -41, 65, -4, 90, 236 };
	auto begin = std::chrono::steady_clock::now();
	std::cout << permut(r).size() << std::endl;
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << "The time: " << elapsed_ms.count() << " ms\n";


	return 0;
}