#pragma once

#include <filesystem>

#include <google/protobuf/util/time_util.h>

namespace fort {

namespace myrmidon {

namespace pb {
class TrackingDataDirectory;
}

namespace priv {

class TrackingDataDirectory {
public:
	std::filesystem::path  Path;

	uint64_t StartFrame;
	uint64_t EndFrame;

	google::protobuf::Timestamp StartDate,EndDate;

	static TrackingDataDirectory Open(const std::filesystem::path & path, const std::filesystem::path & base);

	TrackingDataDirectory();
};

} //namespace priv

} //namespace myrmidon

} //namespace fort


inline bool operator<(const fort::myrmidon::priv::TrackingDataDirectory & a,
                      const fort::myrmidon::priv::TrackingDataDirectory & b) {
	return a.StartDate < b.StartDate;
}