// реализовать алгоритм сжатия, который заменяет последовательности одинаковых символов их количеством и символом Medium
#include <cassert>
#include <iostream>
#include <string>

std::string compression(const std::string text) {

	// Обозначения в комментариях:
	// длина последовательности = дп
	// N - длина строки, K - количество последовательностей из одинаковых символов

	std::string compressed_text; // O(1), 40 байт
	short int count{ 0 }; // O(1), 2 байта
	char left_symbol{ text[0] }; // O(1), 1 байт
	short int text_length = text.length(); // O(1), 2 байта (пространственная сложность O(1) поскольку максимальная длина строки 10000 символов, что меньше 2^15-1)
	compressed_text.reserve(2 * text_length); // O(1)

	for (short int i = 1; i <= text_length; i++) { // O(N); память O(K), max(40, 1+log(дп_1) + ... + 1+log(дп_K)) байт

		count++; // O(1)

		if (text[i] != left_symbol) { // O(1)
			compressed_text.push_back(left_symbol); // O(1)
			if (count != 1) {
				compressed_text += std::to_string(count); // O(1+1) или O(M + log(count)) в худшем случае, M - длина результирующей строки, log(count) - количество разрядов count.
			}
			left_symbol = text[i]; // O(1)
			count = 0; // O(1)

		}
	}

	return compressed_text;

}
// итоговые затраты памяти (самой функцией): max(40, 1+log(дп_1) + ... + 1+log(дп_K)) + 2 + 1 + 2 = max(40, 1+log(дп_1) + ... + 1+log(дп_K)) + 5 байт
// итоговые затраты памяти в целом: max(40, 1+log(дп_1) + ... + 1+log(дп_K)) + 2 + 1 + 2 + max(40, N) = max(40, 1+log(дп_1) + ... + 1+log(дп_K)) + max(40, N) + 5 байт
// итоговая временная сложность O(N), пространственная - O(K)

int main() {
	std::string test_str;
	std::string expected;

	// тест 1 из примера
	test_str = "aaabb";
	expected = "a3b2";
	assert(compression(test_str) == expected);

	// тест 2 
	test_str = "wwwwtttttssssshhhhhhhhhh";
	expected = "w4t5s5h10";
	assert(compression(test_str) == expected);

	// тест 3 с еденичными символами
	test_str = "qwwwwghtttttsssssfhhhhhhq";
	expected = "qw4ght5s5fh6q";
	assert(compression(test_str) == expected);

	// тест 4 только с еденичными символами
	test_str = "qwertyuiopasdf";
	expected = "qwertyuiopasdf";
	assert(compression(test_str) == expected);

	// тест 5 с пустой строкой
	test_str = "";
	expected = "";
	assert(compression(test_str) == expected);

	// тест 6 с последовательностями длиной больше 9
	test_str = "qqqqqqqqqqqyuuuuiiiiiiiiiiiiii";
	expected = "q11yu4i14";
	assert(compression(test_str) == expected);

	std::cout << "All tests completed successfully" << std::endl;
}