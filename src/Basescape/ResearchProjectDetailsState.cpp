/*
 * Copyright 2010-2022 OpenXcom Developers.
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
#include "ResearchProjectDetailsState.h"
#include <sstream>
#include "../Interface/Window.h"
#include "../Interface/TextButton.h"
#include "../Interface/Text.h"
#include "../Engine/Game.h"
#include "../Engine/LocalizedText.h"
#include "../Engine/Options.h"
#include "../Mod/Mod.h"
#include "../Mod/RuleManufacture.h"
#include "../Savegame/Base.h"
#include "../Savegame/SavedGame.h"
#include "../Mod/RuleInterface.h"

namespace OpenXcom
{

/**
 * Initializes all the elements in the productions start screen.
 * @param game Pointer to the core game.
 * @param base Pointer to the base to get info from.
 * @param item The RuleManufacture to produce.
 */
ResearchProjectDetailsState::ResearchProjectDetailsState(Base *base, const RuleResearch* rule) :  _base(base), _rule(rule)
{
	_screen = false;

	_window = new Window(this, 168, 200, 152, 0);
	_btnOk = new TextButton(146, 16, 163, 175);
	_txtTitle = new Text(154, 17, 159, 7);
	_txtDifficulty = new Text(154, 9, 159, 27);
	_txtFunds = new Text(154, 9, 159, 37);
	_txtDestroyitem = new Text(154, 9, 159, 47);
	_txtReqStatsHeader = new Text(154, 9, 159, 59);
	_txtReqStats = new Text(154, 19, 159, 69);

	// Set palette
	setInterface("researchDetailsMenu");

	add(_window, "window", "researchDetailsMenu");
	add(_txtTitle, "text", "researchDetailsMenu");
	add(_txtDifficulty, "text", "researchDetailsMenu");
	add(_txtFunds, "text", "researchDetailsMenu");
	add(_txtDestroyitem, "text", "researchDetailsMenu");
	add(_txtReqStatsHeader, "text", "researchDetailsMenu");
	add(_txtReqStats, "text", "researchDetailsMenu");
	add(_btnOk, "button", "researchDetailsMenu");

	centerAllSurfaces();

	setWindowBackground(_window, "researchDetailsMenu");

	_txtTitle->setText(tr("STR_RESEARCH_STATE_INFO"));
	_txtTitle->setBig();
	_txtTitle->setAlign(ALIGN_CENTER);

	
	_txtDifficulty->setText(tr("STR_PROJECT_DIFFICULTY").arg(tr(getCostDescription())));

	int dY = 0;
	if (_game->getSavedGame()->getDebugMode())
	{
		_txtDifficulty->setVisible(false);
		dY = 10;
	}

	_txtFunds->setText(tr("STR_PROJECT_FUNDS").arg(_rule->getFunds()));
	_txtFunds->setY(_txtFunds->getY() - dY);
	if (_rule->getFunds() == 0)
	{
		_txtFunds->setVisible(false);
	}
	else
	{
		dY += 10;
	}

	_txtDestroyitem->setText(tr("STR_DESTROY_RESEARCHING_ITEM"));
	_txtDestroyitem->setY(_txtDestroyitem->getY() - dY);
	if (!_rule->destroyItem())
	{
		_txtDestroyitem->setVisible(false);
	}
	else
	{
		dY += 10;
	}
	
	_txtReqStatsHeader->setText(tr("STR_REQUIRED_STATS"));
	_txtReqStatsHeader->setY(_txtReqStatsHeader->getY() - dY + 2);

	_txtReqStats->setText(generateStatsList());
	_txtReqStats->setWordWrap(true);
	_txtReqStats->setY(_txtReqStats->getY() - dY + 2);
	_txtReqStats->setColor(_game->getMod()->getInterface("researchDetailsMenu")->getElement("text")->color2);

	_btnOk->setText(tr("STR_OK"));
	_btnOk->onMouseClick((ActionHandler)&ResearchProjectDetailsState::btnOKClick);
	_btnOk->onKeyboardPress((ActionHandler)&ResearchProjectDetailsState::btnOKClick, Options::keyOk);
	_btnOk->onKeyboardPress((ActionHandler)&ResearchProjectDetailsState::btnOKClick, Options::keyCancel);
}

/**
 * Returns to previous screen.
 * @param action A pointer to an Action.
 */
void ResearchProjectDetailsState::btnOKClick(Action *)
{
	_game->popState();
}


std::string ResearchProjectDetailsState::generateStatsList()
{
	std::ostringstream ss;

	auto stats = _rule->getStats();
	std::map<int, std::string> statMap;

	if (stats.physics > 0)
		statMap.insert(std::make_pair(stats.physics, tr(UnitStats::getStatString(&UnitStats::physics, UnitStats::STATSTR_LC))));
	if (stats.chemistry > 0)
		statMap.insert(std::make_pair(stats.chemistry, tr(UnitStats::getStatString(&UnitStats::chemistry, UnitStats::STATSTR_LC))));
	if (stats.biology > 0)
		statMap.insert(std::make_pair(stats.biology, tr(UnitStats::getStatString(&UnitStats::biology, UnitStats::STATSTR_LC))));
	if (stats.data > 0)
		statMap.insert(std::make_pair(stats.data, tr(UnitStats::getStatString(&UnitStats::data, UnitStats::STATSTR_LC))));
	if (stats.computers > 0)
		statMap.insert(std::make_pair(stats.computers, tr(UnitStats::getStatString(&UnitStats::computers, UnitStats::STATSTR_LC))));
	if (stats.tactics > 0)
		statMap.insert(std::make_pair(stats.tactics, tr(UnitStats::getStatString(&UnitStats::tactics, UnitStats::STATSTR_LC))));
	if (stats.designing > 0)
		statMap.insert(std::make_pair(stats.designing, tr(UnitStats::getStatString(&UnitStats::designing, UnitStats::STATSTR_LC))));
	if (stats.alienTech > 0)
		statMap.insert(std::make_pair(stats.alienTech, tr(UnitStats::getStatString(&UnitStats::alienTech, UnitStats::STATSTR_LC))));
	if (stats.psionics > 0)
		statMap.insert(std::make_pair(stats.psionics, tr(UnitStats::getStatString(&UnitStats::psionics, UnitStats::STATSTR_LC))));
	if (stats.xenolinguistics > 0)
		statMap.insert(std::make_pair(stats.xenolinguistics, tr(UnitStats::getStatString(&UnitStats::xenolinguistics, UnitStats::STATSTR_LC))));

	if (!statMap.empty())
	{
		size_t pos = 0;
		std::pair<int, std::string> result;
		for (auto it = statMap.rbegin(); it != statMap.rend(); ++it)
		{
			if (pos > 0)
			{
				ss << ", ";
			}
			ss << (*it).second;
			pos++;
		}
		ss << ".";
	}

	return ss.str();
}

std::string ResearchProjectDetailsState::getCostDescription()
{
	const int cost = _rule->getCost();
	if (cost < 50 * 100) // for more precise calculation, we use man/hour * 100 in FtA for cost/spends calcualtions
		return "STR_TRIVIAL";
	if (cost < 100 * 100)
		return "STR_VERY_EASY";
	else if (cost < 300 * 100)
		return "STR_EASY";
	else if (cost < 500 * 100)
		return "STR_MODERATE";
	else if (cost < 700 * 100)
		return "STR_AVERAGE";
	else if (cost < 1000 * 100)
		return "STR_SOPHISTICATED";
	else if (cost < 1500 * 100)
		return "STR_HARD";
	else if (cost < 2000 * 100)
		return "STR_VERY_HARD";
	else
		return "STR_IMPOSSIBLE";
}

}
