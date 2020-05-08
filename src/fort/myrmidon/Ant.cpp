#include "Ant.hpp"

#include <fort/myrmidon/priv/Ant.hpp>

namespace fort {
namespace myrmidon {

Identification::ConstList Ant::CIdentifications() const {
	Identification::ConstList res;
	const auto & idents = d_p->Identifications();
	res.reserve(idents.size());
	for ( const auto & pIdent : idents ) {
		res.push_back(std::make_shared<const Identification>(pIdent));
	}
	return res;
}

Identification::List Ant::Identifications() {
	Identification::List res;
	const auto & idents = d_p->Identifications();
	res.reserve(idents.size());
	for ( const auto & pIdent : idents ) {
		res.push_back(std::make_shared<Identification>(pIdent));
	}
	return res;
}

Ant::ID Ant::AntID() const {
	return d_p->AntID();
}

std::string Ant::FormattedID() const {
	return d_p->FormattedID();
}


const Color & Ant::DisplayColor() const {
	return d_p->DisplayColor();
}

void Ant::SetDisplayColor(const Color & color) {
	d_p->SetDisplayColor(color);
}

Ant::DisplayState Ant::DisplayStatus() const {
	return d_p->DisplayStatus();
}

void Ant::SetDisplayStatus(DisplayState s) {
	d_p->SetDisplayStatus(s);
}

const AntStaticValue & Ant::GetValue(const std::string & name,
                                     const Time & time) const {
	return d_p->GetValue(name,time);
}

void Ant::SetValue(const std::string & name,
                   const AntStaticValue & value,
                   const Time::ConstPtr & time) {
	d_p->SetValue(name,value,time);
}

void Ant::DeleteValue(const std::string & name,
                      const Time::ConstPtr & time) {
	d_p->DeleteValue(name,time);
}



} // namespace myrmidon
} // namespace fort
