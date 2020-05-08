#pragma once

#include <memory>

#include "Types.hpp"
#include "Color.hpp"
#include "Identification.hpp"



namespace fort {
namespace myrmidon {

namespace priv {
class Ant;
} // namespace priv


// The main object of interest of any Experiment
//
//
// Ant are the object of interest of an <Experiment>.
//
// ## Naming
//
// Ant are uniquely identified by <AntID>. By convention we use
// hexadecimal to display an <ID>, as returned by <FormattedID>.
//
// ## Identification
//
// Instead of working directly with <TagID> myrmidon uses
// <identification> to relates <TagID> to an Ant. An Ant could have
// different <Identification>, allowing us to use different <TagID> to
// refer to the same individual. Myrmidon ensures the following
// invariant:
//
// * At any <Time> there is only a single <TagID> used to designate an
//   Ant
// * For any Ant, there only a single <Identification> that designate
//   this Ant at any given <Time>. I.e. <Identification::Start> and *
//   <Identification::End> must not overlap for a given Ant.
//
// ## Visualization property
//
// Visualization of <Experiment> data is done through
// fort-studio. When visualizaing tracking data, each Ant
// <DisplayState> can be changed. Different colors could be assigned
// to each Ant using <SetDisplayColor> and different <DisplayState>
// can be set using <SetDisplayStatus>.
//
// ## Non-tracking data
//
// TODO
class Ant {
public:
	typedef const std::shared_ptr<priv::Ant> PPtr;

	// A pointer to a an Ant
	typedef std::shared_ptr<Ant>       Ptr;
	// A const pointer to an Ant
	typedef std::shared_ptr<const Ant> ConstPtr;
	// The ID of an Ant.
	//
	// ID are unique within an Experiment.
	typedef uint32_t                   ID;

	// The DisplayState of an Ant in an Experiment
	enum class DisplayState {
		// Ant is visible
		VISIBLE = 0,
		// Ant is hidden
		HIDDEN  = 1,
		// Ant is visible and all non-soloed ant will be hidden.
		SOLO    = 2
	};

	// Gets the const Identifications for this Ant
	//
	// Gets the <Identification::ConstPtr> targetting this Ant. These
	// <Identification> will always be sorted in <Time> and not
	// overlapping.
	//
	// @return an <Identification::ConstList> copy of all
	//         <Identification::ConstPtr>
	Identification::ConstList CIdentifications() const;

	// Gets the Identifications for this Ant
	//
	// Gets the <Identification> targetting this Ant. These
	// <Identification> will always be sorted in <Time> and not
	// overlapping.
	//
	// @return an <Identification::List> copy of all
	//         <Identification::Ptr>
	Identification::List Identifications();

	// Gets the ID of an Ant
	//
	// Ants gets an unique ID in an experiment.
	// @return the <ID> of the Ant
	ID AntID() const;

	// Gets the ID of the Ant formatted as a string.
	//
	// By Convention <ID> are formatted using hexadecimal notation (as
	// opposed to tag that are formatted decimal).
	// @return a string with the formatted ID
	std::string FormattedID() const;

	// Gets the Display Color of an Ant
	//
	// Each Ant has a defined color for display.
	// @return a const reference to the <Color> used to display the Ant
	const Color & DisplayColor() const;


	// Sets the Ant display color
	// @color the new <Color> for the Ant
	void SetDisplayColor(const Color & color);

	// Gets the Ant display state
	//
	// When interacting with the FORT Studio, any Ant has
	// different <DisplayState> :
	//
	//   * <DisplayState::VISIBLE>: the Ant is visible if
	//     they are no Ant which are <DisplayState::SOLO>
	//   * <DisplayState::HIDDEN>: the Ant is not displayed
	//   * <DisplayState::SOLO>: the Ant is visible and
	//     all non <DisplayState::SOLO> Ant are shown.
	// @return the <DisplayState> for this Ant.
	DisplayState DisplayStatus() const;

	// Sets the Ant display state.
	// @s the wanted <DisplayState>
	void SetDisplayStatus(DisplayState s);

	// Gets non-tracking data value
	// @name the name of the non-tracking data value
	// @time the <Time> we want the value for
	//
	// @return the wanted <AntStaticValue>
	const AntStaticValue & GetValue(const std::string & name,
	                                const Time & time) const;

	// Sets a non-tracking
	void SetValue(const std::string & name,
	              const AntStaticValue & value,
	              const Time::ConstPtr & time);

	void DeleteValue(const std::string & name,
	                 const Time::ConstPtr & time);

	Ant(const PPtr & pAnt);

private:


	PPtr d_p;






};


} // namespace myrmidon
} //namespace fort
