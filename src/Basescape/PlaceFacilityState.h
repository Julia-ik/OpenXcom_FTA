#pragma once
/*
 * Copyright 2010-2016 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "../Engine/State.h"

namespace OpenXcom
{

class Base;
class BaseFacility;
class RuleBaseFacility;
class Production;
class BaseView;
class TextButton;
class Window;
class Text;

/**
 * Window shown when the player tries to
 * build a facility.
 */
class PlaceFacilityState : public State
{
protected:
	Base *_base;
	const RuleBaseFacility *_rule;
	BaseFacility *_origFac;

	BaseView *_view;
	TextButton *_btnCancel;
	Window *_window;
	Text *_txtFacility, *_txtCost, *_numCost, *_numResources, *_txtTime, *_numTime, *_txtMaintenance, *_numMaintenance;
	bool _ftaUi;
public:
	/// Creates the Place Facility state.
	PlaceFacilityState(Base *base, const RuleBaseFacility *rule, BaseFacility *origFac = 0);
	/// Cleans up the Place Facility state.
	~PlaceFacilityState();
	/// Handler for clicking the Cancel button.
	void btnCancelClick(Action *action);
	/// Handler for clicking the base view.
	void viewClick(Action *action);
};

}
