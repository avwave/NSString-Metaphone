#pragma once

#include "DoubleMetaphone.h"

//IDs for Metaphone characters, as represented in an unsigned short
#define	METAPHONE_A			0x01
#define METAPHONE_F			0x02
#define METAPHONE_FX		((METAPHONE_F << 4) | METAPHONE_X)
#define METAPHONE_H			0x03
#define METAPHONE_J			0x04
#define METAPHONE_K			0x05
#define METAPHONE_KL		((METAPHONE_K << 4) | METAPHONE_L)
#define METAPHONE_KN		((METAPHONE_K << 4) | METAPHONE_N)
#define METAPHONE_KS		((METAPHONE_K << 4) | METAPHONE_S)
#define METAPHONE_L			0x06
#define METAPHONE_M			0x07
#define METAPHONE_N			0x08
#define METAPHONE_P			0x09
#define METAPHONE_S			0x0A
#define METAPHONE_SK		((METAPHONE_S << 4) | METAPHONE_K)
#define METAPHONE_T			0x0B
#define METAPHONE_TK		((METAPHONE_T << 4) | METAPHONE_K)
#define METAPHONE_TS		((METAPHONE_T << 4) | METAPHONE_S)
#define METAPHONE_R			0x0C
#define METAPHONE_X			0x0D
#define METAPHONE_0			0x0E
#define METAPHONE_SPACE		0x0F
#define METAPHONE_NULL		0x00

#define	METAPHONE_INVALID_KEY	0xffff

class ShortDoubleMetaphone : public DoubleMetaphone4 {
public:
	ShortDoubleMetaphone(tchar* word) : DoubleMetaphone4(word) {
		//Compute ushort version of the keys
		m_primaryShortKey = ShortDoubleMetaphone::metaphoneKeyToUshort(getPrimaryKey());
		
		if (getAlternateKey()) {
			m_alternateShortKey =  ShortDoubleMetaphone::metaphoneKeyToUshort(getAlternateKey());
		} else {
			m_alternateShortKey =  METAPHONE_INVALID_KEY;
		}
	}
	
	/** Default ctor, initializes to a zero-length string */
	ShortDoubleMetaphone() : DoubleMetaphone4() {
		m_primaryShortKey = m_alternateShortKey = 0;
	}
	
	/** Copy ctor, called when you do things like this:
	 * ShortDoubleMetaphone mphone1("foo");
	 * ShortDoubleMetaphone mphone2 = mphone1;
	 * 
	 * as well as under less explicit circumstances.
	 * This impl copies the results of the metaphone key computation
	 * 
	 * Implemented not so you can do that, but so this class will be more
	 * useful with container classes, esp the STL container templates */
	ShortDoubleMetaphone(const ShortDoubleMetaphone& rhs) : DoubleMetaphone4(rhs)  {
		//Re-use the assignment operator, which does effectively the same thing
		//we want to do here in the copy ctor
		*this = rhs;
	}
	
	/** Assignment operator, called when you do this:
	 * ShortDoubleMetaphone mphone1("foo");
	 * ShortDoubleMetaphone mphone2("bar");
	 * 
	 * mphone2 = mphone1;
	 * 
	 * Implemented not so you can do that, but so this class will be more
	 * useful with container classes, esp the STL container templates */
	ShortDoubleMetaphone& operator=(const ShortDoubleMetaphone& rhs) {
		//Call assignemnt operator of base class
		*static_cast<DoubleMetaphone4*>(this) = rhs;
		
		//And copy the keys
		m_primaryShortKey = rhs.m_primaryShortKey;
		m_alternateShortKey = rhs.m_alternateShortKey;
		
		return *this;
	}
	
	/** Equality operator, compares two instances of a class, like:
	 * ShortDoubleMetaphone mphone1("Nelson");
	 * ShortDoubleMetaphone mphone2("Neilsen");
	 * 
	 * if (mphone1 == mphone2) {
	 *	...
	 * 
	 * Equality for the ShortDoubleMetaphone class is defined as either of the two
	 * ushort metaphone keys of rhs matching either of the two ushort metaphone keys of the instance.
	 * That is:
	 * 		primary = primary
	 * 		primary = alt
	 * 		alt = primary
	 * 		alt = alt
	 * This four-way comparison is necessary because in some cases, given two words m and n,
	 * primary(m) != primary(n), but primary(m) = alternate(n) or alternate(m) = primary(n)
	 **/
	bool operator==(const ShortDoubleMetaphone& rhs) const {
		return ( 
				(m_primaryShortKey == rhs.m_primaryShortKey) ||
				(rhs.m_alternateShortKey != METAPHONE_INVALID_KEY && m_primaryShortKey == rhs.m_alternateShortKey) ||
				(m_alternateShortKey != METAPHONE_INVALID_KEY && m_alternateShortKey == rhs.m_primaryShortKey) ||
				(m_alternateShortKey != METAPHONE_INVALID_KEY && rhs.m_alternateShortKey != METAPHONE_INVALID_KEY && m_alternateShortKey == rhs.m_alternateShortKey)
			);				 
	} 

	/** Inequality operator, compares two instances of a class, like:
	 * ShortDoubleMetaphone mphone1("Nelson");
	 * ShortDoubleMetaphone mphone2("Neilsen");
	 * 
	 * if (mphone1 != mphone2) {
	 *	...
	 * 
	 * Equality for the doublempetahone class is defined as either of the two
	 * metaphone keys of rhs matching either of the two metaphone keys of the instance.
	 * That is:
	 * 		primary = primary
	 * 		primary = alt
	 * 		alt = primary
	 * 		alt = alt
	 * This four-way comparison is necessary because in some cases, given two words m and n,
	 * primary(m) != primary(n), but primary(m) = alternate(n) or alternate(m) = primary(n)
	 **/
	bool operator!=(const ShortDoubleMetaphone& rhs) const {
		//Simply negate the operator==
		return !(*this == rhs);             
	} 
	
	/** Discards previous results and computes the metaphone keys for a new word.*/
	void computeKeys(const tchar* word) {
		DoubleMetaphone4::computeKeys(word);
		
		//Compute ushort version of the keys
		m_primaryShortKey = ShortDoubleMetaphone::metaphoneKeyToUshort(getPrimaryKey());
		
		if (getAlternateKey()) {
			m_alternateShortKey =  ShortDoubleMetaphone::metaphoneKeyToUshort(getAlternateKey());
		} else {
			m_alternateShortKey =  METAPHONE_INVALID_KEY;
		}
	}
	
	/** Gets the ushort representation of the primary metaphone key computed for the word passed to the ctor */
	unsigned short getPrimaryShortKey() {
		return m_primaryShortKey;
	}
	
	/** Gets the ushort representation of the alternate metaphone key computed for the word passed to the ctor, 
	 * or METAPHONE_INVALID_KEY if the word has no alternate key by metaphone */
	unsigned short getAlternateShortKey() {
		return m_alternateShortKey;
	}
	
private:
	unsigned short m_primaryShortKey, m_alternateShortKey;
	
	/** Converts a metaphone key to the packed ushort representation */
	static unsigned short metaphoneKeyToUshort(const tchar* key) {
		unsigned short result, charResult;
		const tchar* currentCharPtr = key;
		tchar currentChar;
		
		result = 0;
	
		while (currentChar = *currentCharPtr) {
			if (currentChar == 'A')
				charResult = METAPHONE_A;
			else if (currentChar == 'P')
				charResult = METAPHONE_P;
			else if (currentChar == 'S')
				charResult = METAPHONE_S;
			else if (currentChar == 'K')
				charResult = METAPHONE_K;
			else if (currentChar == 'X')
				charResult = METAPHONE_X;
			else if (currentChar == 'J')
				charResult = METAPHONE_J;
			else if (currentChar == 'T')
				charResult = METAPHONE_T;
			else if (currentChar == 'F')
				charResult = METAPHONE_F;
			else if (currentChar == 'N')
				charResult = METAPHONE_N;
			else if (currentChar == 'H')
				charResult = METAPHONE_H;
			else if (currentChar == 'M')
				charResult = METAPHONE_M;
			else if (currentChar == 'L')
				charResult = METAPHONE_L;
			else if (currentChar == 'R')
				charResult = METAPHONE_R;
			else if (currentChar == ' ')
				charResult = METAPHONE_SPACE;
			else if (currentChar == '\0')
				charResult = METAPHONE_0;
			else 
				charResult = 0x00; //This should never happen
	
			currentCharPtr++;
			result <<= 4;
			result |= charResult;
		};
		return result;
	}
};


