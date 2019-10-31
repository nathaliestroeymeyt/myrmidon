#<cldoc:fort::myrmidon>

the myrmidon API provides tracking analysis utilities

This is the namespace regrouping all the public myrmidon API. It
provides an efficient interface to perform queries on large Ant colony
tracking datasets. Given a collection of tracking data acquired from
the [FORT](https://github.com/formicidae-tracker) system, and metadata
associated with the colony, it provides an efficient C/C++ interface
to perform queries on these dataset.

Tracking Metadata are all information related to an actual individual
in a colony such as:

 * The list of associated fiducial markers (tag) ID associated with
   a single individual over the whole course of the experiment.

 * Collection of measurements on this individual, performed manually
   using high resolution images.

 * Shape definition for collision (interaction) detection.

 * User specified and time-defined metadata to allow complex filtering
   / analysis of the tracking data.


The library aims to provide ABI stability using the private
implementation design pattern: Any public C++ class is only allowed to
have a pointer to a private implementation class.

The public API is a mere read-only interface for the tracking data and
metadata. The private API allows modification of the tracking metadata
and is primarly used by the fort-studio application. User wanting to
analyze their tracking data need to edit the required metadata
directly from the fort-studio Graphical User Interface.