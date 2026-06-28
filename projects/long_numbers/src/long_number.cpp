#include "long_number.hpp"
#include <cstring>

using biv::LongNumber;
		
LongNumber::LongNumber() : length(1), sign(1) {
	numbers = new int[length];
	numbers[0] = 0;
}


LongNumber::LongNumber(int length, int sign) {
	this->sign = sign;
	this->length = length;
	numbers = new int[length];
	for (int i = 0; i < length; i++) {
		numbers[i] = 0;
	}
}


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
	return !(*this == x);
}

bool LongNumber::operator > (const LongNumber& x) const {
	if (sign > x.sign) {
		return true;
	} else if (sign < x.sign) {
		return false;
	} else {
		bool is_max_abs = true;
		if (length != x.length) {
			if (length < x.length) {
				is_max_abs = false;
			}
		} else {
			int i = length - 1;
			while (i >= 0) {
				if (numbers[i] != x.numbers[i]) {
					if (numbers[i] < x.numbers[i]) {
						is_max_abs = false;
					}
					break;
				}
				i--;
			}
			if (i < 0) {
				is_max_abs = false;
			}
		}
		if (sign == -1) {
			return !is_max_abs;
		} else {
			return is_max_abs;
		}
	}
}

bool LongNumber::operator < (const LongNumber& x) const {
	return !(*this > x || *this == x);
}

LongNumber LongNumber::operator + (const LongNumber& x) const { 
	if (sign == x.sign) {
		LongNumber result = add_abs(*this, x);
		result.sign = sign;
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

LongNumber LongNumber::operator - (const LongNumber& x) const {
	if (sign != x.sign) {
		LongNumber result = add_abs(*this, x);
		result.sign = sign;
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
			result.sign = -sign;
			return result;
		}
	}
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
	LongNumber result = mul_abs(*this, x);
	result.sign = sign * x.sign;
	
	return result;
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
	if (x.length == 1 && x.numbers[0] == 0) {
        return LongNumber();
    }
	
	LongNumber quotient, remainder;
	div_abs(*this, x, quotient, remainder);
	
	quotient.sign = sign * x.sign;
	if (quotient.length == 1 && quotient.numbers[0] == 0) {
        quotient.sign = 1;
    }
    
    return quotient;
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
	if (x.length == 1 && x.numbers[0] == 0) {
        return LongNumber();
    }
	
	LongNumber quotient, remainder;
    div_abs(*this, x, quotient, remainder);
	
	remainder.sign = sign;
    if (remainder.length == 1 && remainder.numbers[0] == 0) {
        remainder.sign = 1;
    }
    
    return remainder;
}

/*
bool LongNumber::is_negative() const noexcept {
	// TODO
}
*/

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
/*
int LongNumber::get_length(const char* const str) const noexcept {
	// TODO
}
*/

LongNumber LongNumber::add_abs (const LongNumber& a, const LongNumber& b) {
	int max_len;
	if (a.length > b.length) {
		max_len = a.length;
	} else {
		max_len = b.length;
	}
	
	LongNumber result(max_len + 1, 1);
	
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
	LongNumber result (a.length, 1);
	
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

LongNumber LongNumber::mul_abs (const LongNumber& a, const LongNumber& b) {
	LongNumber result(a.length + b.length, 1);
	for (int i = 0; i < a.length; i++) {
		int carry = 0;
		for (int j = 0; j < b.length; j++) {
			int prod = a.numbers[i] * b.numbers[j] + result.numbers[i + j] + carry;
			result.numbers[i + j] = prod % 10;
			carry = prod / 10;
		}
		if (carry > 0) {
			result.numbers[i + b.length] += carry;
		}
	}
	while (result.length > 1 && result.numbers[result.length - 1] == 0) {
		result.length--;
	}
	
	return result;
}

void LongNumber::div_abs (const LongNumber& a, const LongNumber& b, LongNumber& quotient, LongNumber& remainder)  {
	if (comp_abs(a, b) < 0) {
		delete[] remainder.numbers;
        remainder.numbers = new int[a.length];
        remainder.length = a.length;
        remainder.sign = 1;
		for (int i = 0; i < a.length; i++) {
            remainder.numbers[i] = a.numbers[i];
        }
        return;
	}
	
	delete[] quotient.numbers;
	quotient.numbers = new int[a.length];
	quotient.length = a.length;
	quotient.sign = 1;
	for (int i = 0; i < a.length; i++) {
        quotient.numbers[i] = 0;
    }
	
	for (int i = a.length - 1; i >= 0; i--) {
		int new_length = remainder.length + 1;
		int* new_numbers = new int[new_length];
		for (int j = 0; j < remainder.length; j++) {
            new_numbers[j + 1] = remainder.numbers[j];
        }
		new_numbers[0] = a.numbers[i];
		delete[] remainder.numbers;
		remainder.numbers = new_numbers;
		remainder.length = new_length;
		
		while (remainder.length > 1 && remainder.numbers[remainder.length - 1] == 0) {
            remainder.length--;
        }
		
		int digit = 0;
		for (int d = 9; d >= 1; d--) {
			char digit_str[2] = {(char)('0' + d), '\0'};
			LongNumber d_num(digit_str);
			
			LongNumber prod = b * d_num;
			
			if (comp_abs(prod, remainder) <= 0) {
				digit = d;
				remainder = sub_abs(remainder, prod);
				break;
			}
		}
		quotient.numbers[i] = digit;
	}
	
	while (quotient.length > 1 && quotient.numbers[quotient.length - 1] == 0) {
        quotient.length--;
    }
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
