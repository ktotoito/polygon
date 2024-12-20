// ����������� �������� ������, ������� �������� ������������������ ���������� �������� �� ����������� � �������� Medium
#include <cassert>
#include <iostream>
#include <string>

std::string compression(const std::string text) {

	// ����������� � ������������:
	// ����� ������������������ = ��
	// N - ����� ������, K - ���������� ������������������� �� ���������� ��������

	std::string compressed_text; // O(1), 40 ����
	short int count{ 0 }; // O(1), 2 �����
	char left_symbol{ text[0] }; // O(1), 1 ����
	short int text_length = text.length(); // O(1), 2 ����� (���������������� ��������� O(1) ��������� ������������ ����� ������ 10000 ��������, ��� ������ 2^15-1)
	compressed_text.reserve(2 * text_length); // O(1)

	for (short int i = 1; i <= text_length; i++) { // O(N); ������ O(K), max(40, 1+log(��_1) + ... + 1+log(��_K)) ����

		count++; // O(1)

		if (text[i] != left_symbol) { // O(1)
			compressed_text.push_back(left_symbol); // O(1)
			if (count != 1) {
				compressed_text += std::to_string(count); // O(1+1) ��� O(M + log(count)) � ������ ������, M - ����� �������������� ������, log(count) - ���������� �������� count.
			}
			left_symbol = text[i]; // O(1)
			count = 0; // O(1)

		}
	}

	return compressed_text;

}
// �������� ������� ������ (����� ��������): max(40, 1+log(��_1) + ... + 1+log(��_K)) + 2 + 1 + 2 = max(40, 1+log(��_1) + ... + 1+log(��_K)) + 5 ����
// �������� ������� ������ � �����: max(40, 1+log(��_1) + ... + 1+log(��_K)) + 2 + 1 + 2 + max(40, N) = max(40, 1+log(��_1) + ... + 1+log(��_K)) + max(40, N) + 5 ����
// �������� ��������� ��������� O(N), ���������������� - O(K)

int main() {
	std::string test_str;
	std::string expected;

	// ���� 1 �� �������
	test_str = "aaabb";
	expected = "a3b2";
	assert(compression(test_str) == expected);

	// ���� 2 
	test_str = "wwwwtttttssssshhhhhhhhhh";
	expected = "w4t5s5h10";
	assert(compression(test_str) == expected);

	// ���� 3 � ���������� ���������
	test_str = "qwwwwghtttttsssssfhhhhhhq";
	expected = "qw4ght5s5fh6q";
	assert(compression(test_str) == expected);

	// ���� 4 ������ � ���������� ���������
	test_str = "qwertyuiopasdf";
	expected = "qwertyuiopasdf";
	assert(compression(test_str) == expected);

	// ���� 5 � ������ �������
	test_str = "";
	expected = "";
	assert(compression(test_str) == expected);

	// ���� 6 � �������������������� ������ ������ 9
	test_str = "qqqqqqqqqqqyuuuuiiiiiiiiiiiiii";
	expected = "q11yu4i14";
	assert(compression(test_str) == expected);

	std::cout << "All tests completed successfully" << std::endl;
}