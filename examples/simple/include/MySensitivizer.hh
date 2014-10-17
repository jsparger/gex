//---------------------------------------------------------------------------//
// Copyright (c) 2014 John Sparger <jsparger87@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See https://github.com/jsparger/gex for more information.
//---------------------------------------------------------------------------//

#ifndef MY_SENSITIVIZER_HH
#define MY_SENSITIVIZER_HH

#include "gex/sd/Sensitivizer.hh"

class MySensitivizer : public gex::sd::Sensitivizer
{
public:
	MySensitivizer(std::string fileName, std::string treeName, std::string branchName);
	virtual ~MySensitivizer() {;}
	virtual void makeSensitive(G4LogicalVolume* vol) override;

protected:
	std::string fileName, treeName, branchName;
};

#endif