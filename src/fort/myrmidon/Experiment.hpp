#pragma once

#include <memory>

#include "Types.hpp"
#include "Ant.hpp"
#include "Space.hpp"

namespace fort {
namespace myrmidon {

namespace priv {
// private <fort::myrmidon::priv> Implementation
class Experiment;
} // namespace priv



// Entry point of myrmidon API
//
// Experiment is the main entry point of the myrmidon API. An
// Experiment olds a collection of <Ant>, <Identification>, <Space>
// and <Zone> measurement and give access to the identified tracking
// data and basic interaction detection.
//
// ## File conventiom
//
// Experiment are save to the disk in `.myrmidon` files. One can use
// <Open>, <OpenReadOnly>, <Save> and <NewFile> to interact with those
// files.
//
// Experiment saves relative links to the tracking data directory that
// are acquired with the FORT system. These path are relative, so one
// can rename a `.myrmidon` file on the filesystem, but it must keep
// the same relative path to these tracking data directories.
//
// Multiple program can open an Experiment in read-only mode. However
// a single program can at a Time open an Experiment with full access
// ( read-only program must have released the Experiment too !!!).
class Experiment {
public:
	// A pointer to an Experiment
	typedef std::shared_ptr<Experiment> Ptr;
	// A const pointer to an Experiment
	typedef std::shared_ptr<const Experiment> ConstPtr;

	// Opens an Experiment with full access
	// @filepath the path to the wanted file
	//
	// Opens an Experiment with full access to a `.myrmidon`
	// file. Only a single program can open the same myrmidon file
	// with full access (read only access must be closed).
	//
	// @return a <Ptr> to the Experiment
	static Ptr Open(const std::string & filepath);

	// Opens a read only Experiment
	// @filepath the path to the wanted file.
	//
	// Opens an Experiment with read only access to a `.myrmidon`
	// file. Only a single program can open the same myrmidon file
	// with full access (read only access must be closed).
	//
	// @return a <Ptr> to the Experiment
	static ConstPtr OpenReadOnly(const std::string & filepath);

	// Creates a new Experiment file
	// @filepath the wanted filepath
	//
	// Creates a new Experiment at the wanted filesystem
	// location. Will throw an error if a file already exists at this
	// location.
	//
	// @return a <Ptr> to the new empty Experiment
	static Ptr NewFile(const std::string & filepath);

	// Creates a new Experiment without file association
	// @filepath the wanted filepath
	//
	// Creates a new Experiment virtually associated with the desired
	// filesystem location. Will not create a file.
	//
	// @return a <Ptr> to the new empty Experiment
	static Ptr Create(const std::string & filepath);

	// Saves the Experiment
	// @filepath the desired filesystem location to save the Experiment to
	//
	// Saves the Experiment to its location. It is forbidden to change
	// its parent directory (but file renaming is permitted).
	void Save(const std::string & filepath);


	// Path to the underlying `.myrmidon` file
	//
	// @return the path to the `.myrmidon` file
	const std::string & AbsoluteFilePath() const;

	// Creates a new <Space>
	// @name wanted name for the new <Space>
	//
	// @return a <Space::Ptr> to the new <Space>
	Space::Ptr CreateSpace(const std::string & name);

	// Deletes a <Space>
	// @spaceID the <Space::ID> of the <Space> we want to delete.
	void DeleteSpace(Space::ID spaceID);

	// Gets the <Space> in the Experiment
	//
	// @return a map of the Experiment <Space> by their <Space::ID>
	std::map<Space::ID,Space::Ptr> Spaces();

	/// Gets the <Space> in the Experiment with const access
	//
	// @return a const map of the Experiment <Space>
	std::map<Space::ID,Space::ConstPtr> CSpaces() const;

	// Creates a new <Ant>
	//
	// @return a <Ant::Ptr> to the new <Ant>
	Ant::Ptr CreateAnt();

	// Gets the <Ant> in the Experiment
	//
	// @return the <Ant> indexed by their <Ant::ID> in the Experiment.
	std::map<Ant::ID,Ant::Ptr> Ants();

	// Gets the <Ant> in the Experiment
	//
	// @return the const <Ant> indexed by their <Ant::ID> in the
	// Experiment.
	std::map<Ant::ID,Ant::ConstPtr> CAnts() const;

	// Adds an <Identification> to the Experiment
	// @antID the targetted <Ant> designated by its <Ant::ID>
	// @tagID the tag to associate with the Ant
	// @start the first valid <Time>, nullptr means -∞
	// @end  the first invalid <Time>, nullptr means +∞
	//
	// Adds an <Identification> to the Experiment. <Identification>
	// are valid for [<start>,<end>[. One may obtain a valid time
	// range using <FreeIdentificationRangeAt>.
	//
	// @return a <identification::Ptr> to the new <Identification>
	Identification::Ptr AddIdentification(Ant::ID antID,
	                                      TagID tagID,
	                                      const Time::ConstPtr & start,
	                                      const Time::ConstPtr & end);

	// Deletes an <Identification>
	// @identification the <Identification> to delete
	void DeleteIdentification(const Identification::Ptr & identification);

	// Queries for a valid time range
	// @start return value by reference for the start of the range
	// @end return value by reference for the end of the range
	// @tagID the <TagID> we want a range for
	// @time the <Time> that must be included in the result time range
	//
	// Queries for a valid time range for a given <TagID> and
	// <Time>. The result will be a range [<Start>,<End>[ containing
	// <time> where <tagID> is not used. If it returns false <start>
	// and <end> will be resetted if such a range does not exists.
	//
	// @return `true` if such a range exist, false otherwise.
	bool FreeIdentificationRangeAt(Time::ConstPtr & start,
	                               Time::ConstPtr & end,
	                               TagID tagID, const Time & time) const;


	AntShapeTypeID CreateAntShapeType(const std::string & name);

	std::map<AntShapeTypeID,std::string> AntShapeTypeNames() const;

	void SetAntShapeTypeName(AntShapeTypeID antShapeTypeName,
	                         const std::string & name);

	void DeleteAntShapeType(AntShapeTypeID antShapeTypeID);


	void AddMetadataColumn(const std::string & name,
	                       AntMetadataType type);

	void DeleteMetadataColumn(const std::string & name);

	std::map<std::string,AntMetadataType> AntMetadataColumns() const;

	void RenameAntMetadataColumn(const std::string & oldName,
	                             const std::string & newName);

	void SetAntMetadataColumType(const std::string & name,
	                             AntMetadataType type);

	// Opaque pointer to implementation
	typedef const std::shared_ptr<priv::Experiment> PPtr;

	// Private implementation constructor
	// @pExperiment opaque pointer to implementation
	//
	// User cannot create an Experiment directly. They must use
	// <Open>, <OpenReadOnly>, <Create> and <NewFile>.
	Experiment(const PPtr & pExperiment);
private:



	PPtr d_p;
};

} //namespace mrymidon
} // namespace fort
