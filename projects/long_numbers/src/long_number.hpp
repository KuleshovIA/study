#pragma once

#include <iostream>

namespace biv {
	class LongNumber {
		private:
			int* numbers;
			int length;
			int sign;
		
		public:
			LongNumber();
			LongNumber(int length, int sign);
			LongNumber(const char* const str);
			LongNumber(const LongNumber& x);
			LongNumber(LongNumber&& x);
			
			~LongNumber();
			
			LongNumber& operator = (const char* const str);
			LongNumber& operator = (const LongNumber& x);
			LongNumber& operator = (LongNumber&& x);
			
			bool operator == (const LongNumber& x) const;
			bool operator != (const LongNumber& x) const;
			bool operator > (const LongNumber& x) const;
			bool operator < (const LongNumber& x) const;
			
			LongNumber operator + (const LongNumber& x) const;
			LongNumber operator - (const LongNumber& x) const;
			LongNumber operator * (const LongNumber& x) const;
			LongNumber operator / (const LongNumber& x) const;
			LongNumber operator % (const LongNumber& x) const;
			
			bool is_negative() const noexcept;
			
			friend std::ostream& operator << (std::ostream &os, const LongNumber& x);
			
		private:
			int get_length(const char* const str) const noexcept;
			
			static LongNumber add_abs (const LongNumber &a, const LongNumber &b);
			static LongNumber sub_abs (const LongNumber &a, const LongNumber &b);
			static LongNumber mul_abs (const LongNumber &a, const LongNumber &b);
			static void div_abs (const LongNumber &a, const LongNumber &b, LongNumber& quotient, LongNumber& remainder);
			static int comp_abs (const LongNumber &a, const LongNumber &b);
	};
}
