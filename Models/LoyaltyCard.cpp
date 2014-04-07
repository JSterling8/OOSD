/**
 * LoyaltyCard.cpp
 *
 *  Created on: 7 Apr 2014
 *      @author: Jonathan Sterling
 */

#include "LoyaltyCard.h"

namespace std {

int id;

LoyaltyCard::LoyaltyCard(int loyaltyId) {
	id = loyaltyId;
}

int LoyaltyCard::getId(){
	return id;
}

} /* namespace std */
