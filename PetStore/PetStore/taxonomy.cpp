#include "taxonomy.h"

Species::Species(std::string kingdom,
	std::string phylum,
	std::string class_,
	std::string order,
	std::string family,
	std::string genus,
	kingdom{ kingdom },
	class_{ class_ },
	order{ order },
	family{ family },
	genus{ genus },
	species{ species },
	commonName{ commonName },
	shortName{ shortName },
	sapient{sapient}
{}
std::string Species::getKingdom () const {
	return kingdom;
}
std::string Species::getClass() const {
	return class_;
}
std::string Species::getOrder() const {
	return order;
}
std::string Species::getFamily() const {
	return family;
}
std::string Species::getGenus() const {
	return genus;
}
std::string Species::getSpecies() const {
	return species;
}
std::string Species::getCommonName() const {
	return commonName;
}
std::string Species::getShortName() const {
	return shortName;
}
bool Species::isSapient() const {
	return sapient;
}



SpeciesList::SpeciesList() {
}

void SpeciesList::addSpecies(Species* sp) {
	sp_list[sp->getShortName()] = sp;
}
Species* SpeciesList::getSpecies(std::string shortName) {
	return sp_list[shortName];
}

