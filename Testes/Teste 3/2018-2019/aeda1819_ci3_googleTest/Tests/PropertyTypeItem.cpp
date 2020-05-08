#include "PropertyTypeItem.h"

PropertyTypeItem::PropertyTypeItem(string address, string postalCode, string typology, int maxPrice) {
	this->address = address;
	this->postalCode = postalCode;
	this->typology = typology;
	this->maxPrice = maxPrice;
}

string PropertyTypeItem::getAddress() const {
	return this->address;
}

string PropertyTypeItem::getPostalCode() const {
	return this->postalCode;
}

string PropertyTypeItem::getTypology() const {
	return this->typology;
}

int PropertyTypeItem::getMaxPrice() const {
	return this->maxPrice;
}

vector<Property*> PropertyTypeItem::getItems() const {
	return this->items;
}

void PropertyTypeItem::setItems(vector<Property*> properties) {
	items = properties;
}

void PropertyTypeItem::addItems(Property* property) {
	this->items.push_back(property);
}

//
// TODO
//

bool PropertyTypeItem::operator<(const PropertyTypeItem &pti1) const {
    if(pti1.getAddress()== address){
        if(pti1.getPostalCode()==postalCode){
            if (pti1.getTypology() == typology){
                return maxPrice<pti1.getMaxPrice();
            }
            else{
                return typology< pti1.getTypology();
            }
        }
        else{
            return postalCode<pti1.getPostalCode();
        }
    }
    else{
        return address< pti1.getAddress();
    }
}

bool PropertyTypeItem::operator==(const PropertyTypeItem &pti1) const {
	//TODO:
	return (address == pti1.getAddress() && postalCode == pti1.getPostalCode() && typology == pti1.getTypology() && maxPrice==pti1.getMaxPrice()) ;
}
