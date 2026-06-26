#include "long_number.hpp"
#include <cstring>

using biv::LongNumber;
		
LongNumber::LongNumber() : length(1), sign(1) {
	numbers = new int[length];
	numbers[0] = 0;
}

/*
LongNumber::LongNumber(int length, int sign) {
	
}
*/

LongNumber::LongNumber(const char* const str) {
	int str_length = std::strlen(str);
	if(str[0] == '-') {
		sign = -1;
		length = str_length - 1;
	} else {
		sign = 1;
		length = str_length;
	}
	
	numbers = new int[length];
	for (int i = 0; i < length; i++) {
		numbers[i] = str[str_length - i - 1] - '0';
	}
}

LongNumber::LongNumber(const LongNumber& x) {
	length = x.length;
	sign = x.sign;
	numbers = new int[length];
	for (int i = 0; i < length; i++) {
		numbers[i] = x.numbers[i];
	}
}

LongNumber::LongNumber(LongNumber&& x) {
	length = x.length;
	sign = x.sign;
	numbers = x.numbers;
	x.numbers = nullptr;
}

LongNumber::~LongNumber() {
	length = 0;
	delete [] numbers;
	numbers = nullptr;
}

LongNumber& LongNumber::operator = (const char* const str) {
	int str_length = std::strlen(str);
	if (str[0] == '-') {
		sign = -1;
		length = str_length - 1;
	} else {
		sign = 1;
		length = str_length;
	}
	
	delete [] numbers;
	numbers = new int[length];
	for (int i = 0; i < length; i++) {
		numbers[i] = str[str_length - i - 1] - '0';
	}
	
	return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	if (this == &x) return *this;
	
	length = x.length;
	sign = x.sign;
	
	delete [] numbers;
	numbers = new int[length];
	for (int i = 0; i < length; i++) {
		numbers[i] = x.numbers[i];
	}
	
	return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
	length = x.length;
	sign = x.sign;
	
	delete [] numbers;
	numbers = x.numbers;
	x.numbers = nullptr;
	
	return *this;
}

bool LongNumber::operator == (const LongNumber& x) const {
	if (sign != x.sign) {
		return false;
	}
	if (length != x.length) {
		return false;
	}
	if (sign == x.sign && length == x.length) {
		for (int i = 0; i < length; i++) {
			if (numbers[i] != x.numbers[i]) {
				return false;
			}
		}
	}
	return true;
}

bool LongNumber::operator != (const LongNumber& x) const {
	if (sign != x.sign || length != x.length) {
		return true;
	} else {
		for (int i = 0; i < length; i++) {
			if (numbers[i] != x.numbers[i]) {
				return true;
			}
		}
	}
	return false;
}

bool LongNumber::operator > (const LongNumber& x) const {
	if (sign > x.sign) {
		return true;
	} else if (sign < x.sign) {
		return false;
	} else {
		if (sign == 1) {
			if (length > x.length) {
				return true;
			} else if (length < x.length) {
				return false;
			} else {
				for (int i = length - 1; i >= 0; i--) {
					if (numbers[i] > x.numbers[i]) {
						return true;
					} else if (numbers[i] < x.numbers[i]) {
						return false;
					}
				}
			}
		} else {
			if (length < x.length) {
				return true;
			} else if (length > x.length) {
				return false;
			} else {
				for (int i = length - 1; i >= 0; i--) {
					if (numbers[i] < x.numbers[i]) {
						return true;
					} else if (numbers[i] > x.numbers[i]) {
						return false;
					}
				}
			}
		}
	}
}


bool LongNumber::operator < (const LongNumber& x) const {
	if (sign < x.sign) {
		return true;
	}
	if (sign == 1 && x.sign == 1 && length < x.length) {
		return true;
	}
	if (sign == -1 && x.sign == -1 && length > x.length) {
		return true;
	}
	if (sign == 1 && x.sign == 1 && length == x.length) {
		for (int i = length - 1; i >= 0; i--) {
			if (numbers[i] < x.numbers[i]) {
				return true;
			} else if (numbers[i] > x.numbers[i]) {
				return false;
			}
		}
	}
	if (sign == -1 && x.sign == -1 && length == x.length) {
		for (int i = length - 1; i >= 0; i--) {
			if (numbers[i] > x.numbers[i]) {
				return true;
			} else if (numbers[i] < x.numbers[i]) {
				return false;
			}
		}
	}
	return false;
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
	if (sign == x.sign) {
		LongNumber result = add_abs(*this, x);
		result.sign = sign;
		/*
		if (result.length == 1 && result.numbers[0] == 0) {
			result.sign = 1;
		}
		*/
		return result;
	} else {
	
		int is_bigger = comp_abs(*this, x);
		if (is_bigger == 0) {
			return LongNumber();
		}
		if (is_bigger > 0) {
			LongNumber result = sub_abs(*this, x);
			result.sign = sign;
			return result;
		} else {
			LongNumber result = sub_abs(x, *this);
			result.sign = x.sign;
			return result;
		}
	}
}
/*
LongNumber LongNumber::operator - (const LongNumber& x) const {
	// TODO
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
	// TODO
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
	// TODO
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
	// TODO
}
*/
/*
bool LongNumber::is_negative() const noexcept {
	// TODO
}
*/

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
	// TODO
}

LongNumber LongNumber::add_abs (const LongNumber& a, const LongNumber& b) {
	int max_len;
	if (a.length > b.length) {
		max_len = a.length;
	} else {
		max_len = b.length;
	}
	
	LongNumber result;
	delete[] result.numbers;
	result.numbers = new int[max_len + 1];
	result.length = max_len + 1;
	result.sign = 1;
	
	int carry = 0;
	for (int i = 0; i < max_len; i++) {
		int sum = carry;
		if (i < a.length) sum += a.numbers[i];
		if (i < b.length) sum += b.numbers[i];
		result.numbers[i] = sum % 10;
		carry = sum / 10;
	}
	if (carry > 0) {
		result.numbers[max_len] = carry;
    } else {
        result.length = max_len;
    }
	
	while (result.length > 1 && result.numbers[result.length - 1] == 0) {
		result.length--;
	}
	
	return result;
}

LongNumber LongNumber::sub_abs (const LongNumber& a, const LongNumber& b) {	
	LongNumber result;
	delete[] result.numbers;
	result.numbers = new int[a.length];
	result.length = a.length;
	result.sign = 1;
	
	int borrow = 0;
	for (int i = 0; i < a.length; i++) {
		int diff = a.numbers[i] - borrow;
		if (i < b.length) {
			diff -= b.numbers[i];
		}
		if (diff < 0) {
			diff += 10;
			borrow = 1;
		} else {
			borrow = 0;
		}
		result.numbers[i] = diff;
	}
	
	while (result.length > 1 && result.numbers[result.length - 1] == 0) {
		result.length--;
	}
	return result;
}

int LongNumber::comp_abs (const LongNumber& a, const LongNumber& b) {
	if (a.length != b.length) {
		if (a.length > b.length) {
			return 1;
		} else {
			return -1;
		}
	}
	for (int i = a.length - 1; i >= 0; i--) {
		if (a.numbers[i] != b.numbers[i]) {
			if (a.numbers[i] > b.numbers[i]) {
				return 1;
			} else {
				return -1;
			}
		}
	}
	return 0;
}


// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace biv {
	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
		if (x.sign == -1) {
			os << '-';
		}
		for (int i = x.length - 1; i >= 0; i--) {
			os << x.numbers[i];
		}
		return os;
	}
}
