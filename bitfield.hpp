/**
  * Simplified Bit-field implementation for embedded development.
  * EXPERIMENTAL BUILD
  */

#ifndef BITFIELD_HPP_
#define BITFIELD_HPP_

#include<cstdint> // Defines fixed-width integers
#include<iostream> //

enum byte_e : uint8_t {
	b0 = 0x01,
	b1 = 0x02,
	b2 = 0x04,
	b3 = 0x08,
	b4 = 0x10,
	b5 = 0x20,
	b6 = 0x40,
	b7 = 0x80
};

enum word_e : uint16_t {
	w0 = 0x0001,
	w1 = 0x0002,
	w2 = 0x0004,
	w3 = 0x0008,
	w4 = 0x0010,
	w5 = 0x0020,
	w6 = 0x0040,
	w7 = 0x0080,
	w8 = 0x0100,
	w9 = 0x0200,
	w10 = 0x0400,
	w11 = 0x0800,
	w12 = 0x1000,
	w13 = 0x2000,
	w14 = 0x4000,
	w15 = 0x8000
};


// Template Meta-programming http://en.cppreference.com/w/cpp/types/is_integral
// Operators https://stackoverflow.com/questions/4421706/what-are-the-basic-rules-and-idioms-for-operator-overloading
typedef struct byte_t{

	// Actual Data
	union {
		uint8_t data;
	};

	/** Constructor
	  * TODO: constexpr constructor
	  * constexpr byte_t(auto i){data = i;} allows for byte_t Byte = 0x40,
	  * but breaks byte_t Byte;
	  */

	// Behavior Extensions
	constexpr void clear(byte_e b){data &= ~b;}
	constexpr uint8_t get(const byte_e b){return data &= b;}
	constexpr void set(byte_e b){data |= b;}

	// Stream Operators
	friend std::ostream& operator<<(std::ostream& os, const byte_t& byte){return os << byte.data;};
	friend std::istream& operator>>(std::istream& is, byte_t& byte){return is >> byte.data;};

	// Increment and Decrement
	constexpr byte_t& operator++(){data++; return *this;}; // ++prefix
	constexpr byte_t operator++(int){byte_t Byte; Byte.data = this->data; operator++(); return Byte;};
	// TODO: --a
	// TODO: a--

	// Assignment[1]
	constexpr byte_t& operator=(auto i){data = i; return *this;}
	constexpr byte_t& operator=(const byte_t& rhs){data = rhs.data; return *this;}

	// Assignment[2]
	constexpr byte_t& operator+=(const byte_t& rhs){data += rhs.data; return *this;}
	constexpr byte_t& operator-=(const byte_t& rhs){data -= rhs.data; return *this;}
	constexpr byte_t& operator*=(const byte_t& rhs){data *= rhs.data; return *this;}
	constexpr byte_t& operator/=(const byte_t& rhs){data /= rhs.data; return *this;}
	constexpr byte_t& operator%=(const byte_t& rhs){data %= rhs.data; return *this;}
	constexpr byte_t& operator&=(const byte_t& rhs){data &= rhs.data; return *this;}
	constexpr byte_t& operator|=(const byte_t& rhs){data |= rhs.data; return *this;}
	constexpr byte_t& operator^=(const byte_t& rhs){data ^= rhs.data; return *this;}
	constexpr byte_t& operator<<=(const byte_t& rhs){data <<= rhs.data; return *this;}
	constexpr byte_t& operator>>=(const byte_t& rhs){data >>= rhs.data; return *this;}

	// Negation
	constexpr byte_t& operator~(){data = ~data; return *this;}

	// Cast
	operator auto() const {return data;}
};

// Arithmetic
constexpr byte_t operator+(byte_t lhs, const byte_t& rhs){lhs += rhs; return lhs;}
constexpr byte_t operator-(byte_t lhs, const byte_t& rhs){lhs -= rhs; return lhs;}
constexpr byte_t operator*(byte_t lhs, const byte_t& rhs){lhs *= rhs; return lhs;}
constexpr byte_t operator/(byte_t lhs, const byte_t& rhs){lhs /= rhs; return lhs;}
constexpr byte_t operator%(byte_t lhs, const byte_t& rhs){lhs %= rhs; return lhs;}
constexpr byte_t operator&(byte_t lhs, const byte_t& rhs){lhs &= rhs; return lhs;}
constexpr byte_t operator|(byte_t lhs, const byte_t& rhs){lhs |= rhs; return lhs;}
constexpr byte_t operator^(byte_t lhs, const byte_t& rhs){lhs ^= rhs; return lhs;}
constexpr byte_t operator<<(byte_t lhs, const byte_t& rhs){lhs <<= rhs; return lhs;}
constexpr byte_t operator>>(byte_t lhs, const byte_t& rhs){lhs >>= rhs; return lhs;}

// Logic
// TODO: operator!a
// TODO: operator a&&b
// TODO: operator a||b

// Comparison
constexpr bool operator==(const byte_t& lhs, const byte_t& rhs){return (lhs.data==rhs.data);}
constexpr bool operator!=(const byte_t& lhs, const byte_t& rhs){return !operator==(lhs,rhs);}
constexpr bool operator< (const byte_t& lhs, const byte_t& rhs){return (lhs.data < rhs.data);}
constexpr bool operator> (const byte_t& lhs, const byte_t& rhs){return operator< (rhs,lhs);}
constexpr bool operator<=(const byte_t& lhs, const byte_t& rhs){return !operator> (lhs,rhs);}
constexpr bool operator>=(const byte_t& lhs, const byte_t& rhs){return !operator< (lhs,rhs);}

// Other
// TODO: operator Ternary

#endif /* BITFIELD_HPP_ */
