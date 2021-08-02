#pragma once

#include "HandleInContext.hpp"

#include "ZoneHandle.hpp"

namespace fort {
namespace myrmidon {

class SpaceHandle : public priv::HandleInContext<priv::Space,priv::Experiment> {
public :
	SpaceHandle(const priv::Space::Ptr & space,
	            const priv::Experiment::Ptr & experiment)
		: HandleInContext(space,experiment) {
		for (const auto & [zoneID,zone] : space->Zones() ) {
			d_zones.insert_or_assign(zoneID,MakeZonePtr(zone));
		}
	}

	const ZoneByID & Zones() const {
		return d_zones;
	}

	void DeleteZone(ZoneID zoneID) {
		d_object->DeleteZone(zoneID);
		d_zones.erase(zoneID);
	}

	Zone::Ptr CreateZone(const std::string & name) {
		auto zone = MakeZonePtr(d_object->CreateZone(name,0));
		d_zones.insert_or_assign(zone->ID(),zone);
		return d_zones.at(zone->ID());
	}

private:
	Zone::Ptr MakeZonePtr(const priv::Zone::Ptr & zone) {
		return Zone::Ptr(new Zone(std::make_unique<ZoneHandle>(zone)));
	}

	ZoneByID d_zones;
};

} // namespace myrmidon
} // namespace fort
