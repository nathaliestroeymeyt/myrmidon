#include "Ant.hpp"

#include "priv/Ant.hpp"


namespace fort {
namespace myrmidon {

Ant::Ant(const PPtr & pAnt)
	: d_p(pAnt) {
}

TagID Ant::IdentifiedAt(const Time & time) const {
	return d_p->IdentifiedAt(time);
}



Identification::List Ant::Identifications() {
	Identification::List res;
	const auto & idents = d_p->Identifications();
	res.reserve(idents.size());
	for ( const auto & pIdent : idents ) {
		res.push_back(Identification::Ptr(new Identification(pIdent)));
	}
	return res;
}

AntID Ant::ID() const {
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
                   const Time & time) {
	d_p->SetValue(name,value,time);
}

void Ant::DeleteValue(const std::string & name,
                      const Time & time) {
	d_p->DeleteValue(name,time);
}

void Ant::AddCapsule(AntShapeTypeID shapeTypeID,
                     const std::shared_ptr<Capsule> & capsule) {
	d_p->AddCapsule(shapeTypeID,capsule);
}

const TypedCapsuleList & Ant::Capsules() const {
	return d_p->Capsules();
}

void Ant::DeleteCapsule(const size_t index) {
	d_p->DeleteCapsule(index);
}

void Ant::ClearCapsules() {
	d_p->ClearCapsules();
}


} // namespace myrmidon
} // namespace fort
