/*
This Source Code Form is subject to the
terms of the Mozilla Public License, v.
2.0. If a copy of the MPL was not
distributed with this file, You can
obtain one at
http://mozilla.org/MPL/2.0/.
*/

#include "stdafx.h"
#include "command.h"

#include "Globals.h"
#include "Logs.h"
#include "Timer.h"
#include "utilities.h"
#include "simulation.h"
#include "Train.h"

namespace simulation {

command_queue Commands;
commanddescription_sequence Commands_descriptions = {

    { "aidriverenable", command_target::vehicle },
    { "aidriverdisable", command_target::vehicle },
    { "jointcontrollerset", command_target::vehicle },
    { "mastercontrollerincrease", command_target::vehicle },
    { "mastercontrollerincreasefast", command_target::vehicle },
    { "mastercontrollerdecrease", command_target::vehicle },
    { "mastercontrollerdecreasefast", command_target::vehicle },
    { "mastercontrollerset", command_target::vehicle },
    { "secondcontrollerincrease", command_target::vehicle },
    { "secondcontrollerincreasefast", command_target::vehicle },
    { "secondcontrollerdecrease", command_target::vehicle },
    { "secondcontrollerdecreasefast", command_target::vehicle },
    { "secondcontrollerset", command_target::vehicle },
    { "mucurrentindicatorothersourceactivate", command_target::vehicle },
    { "independentbrakeincrease", command_target::vehicle },
    { "independentbrakeincreasefast", command_target::vehicle },
    { "independentbrakedecrease", command_target::vehicle },
    { "independentbrakedecreasefast", command_target::vehicle },
    { "independentbrakeset", command_target::vehicle },
    { "independentbrakebailoff", command_target::vehicle },
	{ "universalbrakebutton1", command_target::vehicle },
	{ "universalbrakebutton2", command_target::vehicle },
	{ "universalbrakebutton3", command_target::vehicle },
    { "trainbrakeincrease", command_target::vehicle },
    { "trainbrakedecrease", command_target::vehicle },
    { "trainbrakeset", command_target::vehicle },
    { "trainbrakecharging", command_target::vehicle },
    { "trainbrakerelease", command_target::vehicle },
    { "trainbrakefirstservice", command_target::vehicle },
    { "trainbrakeservice", command_target::vehicle },
    { "trainbrakefullservice", command_target::vehicle },
    { "trainbrakehandleoff", command_target::vehicle },
    { "trainbrakeemergency", command_target::vehicle },
    { "trainbrakebasepressureincrease", command_target::vehicle },
    { "trainbrakebasepressuredecrease", command_target::vehicle },
    { "trainbrakebasepressurereset", command_target::vehicle },
    { "trainbrakeoperationtoggle", command_target::vehicle },
    { "manualbrakeincrease", command_target::vehicle },
    { "manualbrakedecrease", command_target::vehicle },
    { "alarmchaintoggle", command_target::vehicle },
    { "wheelspinbrakeactivate", command_target::vehicle },
    { "sandboxactivate", command_target::vehicle },
	{ "autosandboxtoggle", command_target::vehicle },
	{ "autosandboxactivate", command_target::vehicle },
	{ "autosandboxdeactivate", command_target::vehicle },
    { "reverserincrease", command_target::vehicle },
    { "reverserdecrease", command_target::vehicle },
    { "reverserforwardhigh", command_target::vehicle },
    { "reverserforward", command_target::vehicle },
    { "reverserneutral", command_target::vehicle },
    { "reverserbackward", command_target::vehicle },
    { "waterpumpbreakertoggle", command_target::vehicle },
    { "waterpumpbreakerclose", command_target::vehicle },
    { "waterpumpbreakeropen", command_target::vehicle },
    { "waterpumptoggle", command_target::vehicle },
    { "waterpumpenable", command_target::vehicle },
    { "waterpumpdisable", command_target::vehicle },
    { "waterheaterbreakertoggle", command_target::vehicle },
    { "waterheaterbreakerclose", command_target::vehicle },
    { "waterheaterbreakeropen", command_target::vehicle },
    { "waterheatertoggle", command_target::vehicle },
    { "waterheaterenable", command_target::vehicle },
    { "waterheaterdisable", command_target::vehicle },
    { "watercircuitslinktoggle", command_target::vehicle },
    { "watercircuitslinkenable", command_target::vehicle },
    { "watercircuitslinkdisable", command_target::vehicle },
    { "fuelpumptoggle", command_target::vehicle },
    { "fuelpumpenable", command_target::vehicle },
    { "fuelpumpdisable", command_target::vehicle },
    { "oilpumptoggle", command_target::vehicle },
    { "oilpumpenable", command_target::vehicle },
    { "oilpumpdisable", command_target::vehicle },
    { "linebreakertoggle", command_target::vehicle },
    { "linebreakeropen", command_target::vehicle },
    { "linebreakerclose", command_target::vehicle },
    { "convertertoggle", command_target::vehicle },
    { "converterenable", command_target::vehicle },
    { "converterdisable", command_target::vehicle },
    { "convertertogglelocal", command_target::vehicle },
    { "converteroverloadrelayreset", command_target::vehicle },
    { "compressortoggle", command_target::vehicle },
    { "compressorenable", command_target::vehicle },
    { "compressordisable", command_target::vehicle },
    { "compressortogglelocal", command_target::vehicle },
	{ "compressorpresetactivatenext", command_target::vehicle },
	{ "compressorpresetactivateprevious", command_target::vehicle },
	{ "compressorpresetactivatedefault", command_target::vehicle },
    { "motoroverloadrelaythresholdtoggle", command_target::vehicle },
    { "motoroverloadrelaythresholdsetlow", command_target::vehicle },
    { "motoroverloadrelaythresholdsethigh", command_target::vehicle },
    { "motoroverloadrelayreset", command_target::vehicle },
    { "universalrelayreset1", command_target::vehicle },
    { "universalrelayreset2", command_target::vehicle },
    { "universalrelayreset3", command_target::vehicle },
    { "notchingrelaytoggle", command_target::vehicle },
    { "epbrakecontroltoggle", command_target::vehicle },
	{ "trainbrakeoperationmodeincrease", command_target::vehicle },
	{ "trainbrakeoperationmodedecrease", command_target::vehicle },
    { "brakeactingspeedincrease", command_target::vehicle },
    { "brakeactingspeeddecrease", command_target::vehicle },
    { "brakeactingspeedsetcargo", command_target::vehicle },
    { "brakeactingspeedsetpassenger", command_target::vehicle },
    { "brakeactingspeedsetrapid", command_target::vehicle },
    { "brakeloadcompensationincrease", command_target::vehicle },
    { "brakeloadcompensationdecrease", command_target::vehicle },
    { "mubrakingindicatortoggle", command_target::vehicle },
    { "alerteracknowledge", command_target::vehicle },
    { "hornlowactivate", command_target::vehicle },
    { "hornhighactivate", command_target::vehicle },
    { "whistleactivate", command_target::vehicle },
    { "radiotoggle", command_target::vehicle },
    { "radiochannelincrease", command_target::vehicle },
    { "radiochanneldecrease", command_target::vehicle },
    { "radiostopsend", command_target::vehicle },
    { "radiostoptest", command_target::vehicle },
    { "radiocall3send", command_target::vehicle },
	{ "radiovolumeincrease", command_target::vehicle },
	{ "radiovolumedecrease", command_target::vehicle },
// TBD, TODO: make cab change controls entity-centric
    { "cabchangeforward", command_target::vehicle },
    { "cabchangebackward", command_target::vehicle },

    { "viewturn", command_target::entity },
    { "movehorizontal", command_target::entity },
    { "movehorizontalfast", command_target::entity },
    { "movevertical", command_target::entity },
    { "moveverticalfast", command_target::entity },
    { "moveleft", command_target::entity },
    { "moveright", command_target::entity },
    { "moveforward", command_target::entity },
    { "moveback", command_target::entity },
    { "moveup", command_target::entity },
    { "movedown", command_target::entity },
    // TBD, TODO: make coupling controls entity-centric
    { "nearestcarcouplingincrease", command_target::vehicle },
    { "nearestcarcouplingdisconnect", command_target::vehicle },
    { "nearestcarcoupleradapterattach", command_target::vehicle },
    { "nearestcarcoupleradapterremove", command_target::vehicle },
    { "occupiedcarcouplingdisconnect", command_target::vehicle },
    { "doortoggleleft", command_target::vehicle },
    { "doortoggleright", command_target::vehicle },
    { "doorpermitleft", command_target::vehicle },
    { "doorpermitright", command_target::vehicle },
    { "doorpermitpresetactivatenext", command_target::vehicle },
    { "doorpermitpresetactivateprevious", command_target::vehicle },
    { "dooropenleft", command_target::vehicle },
    { "dooropenright", command_target::vehicle },
    { "dooropenall", command_target::vehicle },
    { "doorcloseleft", command_target::vehicle },
    { "doorcloseright", command_target::vehicle },
    { "doorcloseall", command_target::vehicle },
    { "doorsteptoggle", command_target::vehicle },
    { "doormodetoggle", command_target::vehicle },
    { "departureannounce", command_target::vehicle },
    { "doorlocktoggle", command_target::vehicle },
    { "pantographcompressorvalvetoggle", command_target::vehicle },
    { "pantographcompressorvalveenable", command_target::vehicle },
    { "pantographcompressorvalvedisable", command_target::vehicle },
    { "pantographcompressoractivate", command_target::vehicle },
    { "pantographtogglefront", command_target::vehicle },
    { "pantographtogglerear", command_target::vehicle },
    { "pantographraisefront", command_target::vehicle },
    { "pantographraiserear", command_target::vehicle },
    { "pantographlowerfront", command_target::vehicle },
    { "pantographlowerrear", command_target::vehicle },
    { "pantographlowerall", command_target::vehicle },
    { "pantographselectnext", command_target::vehicle },
    { "pantographselectprevious", command_target::vehicle },
    { "pantographtoggleselected", command_target::vehicle },
    { "pantographraiseselected", command_target::vehicle },
    { "pantographlowerselected", command_target::vehicle },
    { "pantographvalvesupdate", command_target::vehicle },
    { "pantographvalvesoff", command_target::vehicle },
    { "heatingtoggle", command_target::vehicle },
    { "heatingenable", command_target::vehicle },
    { "heatingdisable", command_target::vehicle },
    { "lightspresetactivatenext", command_target::vehicle },
    { "lightspresetactivateprevious", command_target::vehicle },
    { "headlighttoggleleft", command_target::vehicle },
    { "headlightenableleft", command_target::vehicle },
    { "headlightdisableleft", command_target::vehicle },
    { "headlighttoggleright", command_target::vehicle },
    { "headlightenableright", command_target::vehicle },
    { "headlightdisableright", command_target::vehicle },
    { "headlighttoggleupper", command_target::vehicle },
    { "headlightenableupper", command_target::vehicle },
    { "headlightdisableupper", command_target::vehicle },
    { "redmarkertoggleleft", command_target::vehicle },
    { "redmarkerenableleft", command_target::vehicle },
    { "redmarkerdisableleft", command_target::vehicle },
    { "redmarkertoggleright", command_target::vehicle },
    { "redmarkerenableright", command_target::vehicle },
    { "redmarkerdisableright", command_target::vehicle },
    { "headlighttogglerearleft", command_target::vehicle },
    { "headlighttogglerearright", command_target::vehicle },
    { "headlighttogglerearupper", command_target::vehicle },
    { "redmarkertogglerearleft", command_target::vehicle },
    { "redmarkertogglerearright", command_target::vehicle },
    { "redmarkerstoggle", command_target::vehicle },
    { "endsignalstoggle", command_target::vehicle },
    { "headlightsdimtoggle", command_target::vehicle },
    { "headlightsdimenable", command_target::vehicle },
    { "headlightsdimdisable", command_target::vehicle },
    { "motorconnectorsopen", command_target::vehicle },
    { "motorconnectorsclose", command_target::vehicle },
    { "motordisconnect", command_target::vehicle },
    { "interiorlighttoggle", command_target::vehicle },
    { "interiorlightenable", command_target::vehicle },
    { "interiorlightdisable", command_target::vehicle },
    { "interiorlightdimtoggle", command_target::vehicle },
    { "interiorlightdimenable", command_target::vehicle },
    { "interiorlightdimdisable", command_target::vehicle },
    { "compartmentlightstoggle", command_target::vehicle },
    { "compartmentlightsenable", command_target::vehicle },
    { "compartmentlightsdisable", command_target::vehicle },
    { "instrumentlighttoggle", command_target::vehicle },
    { "instrumentlightenable", command_target::vehicle },
    { "instrumentlightdisable", command_target::vehicle },
    { "dashboardlighttoggle", command_target::vehicle },
    { "timetablelighttoggle", command_target::vehicle },
    { "generictoggle0", command_target::vehicle },
    { "generictoggle1", command_target::vehicle },
    { "generictoggle2", command_target::vehicle },
    { "generictoggle3", command_target::vehicle },
    { "generictoggle4", command_target::vehicle },
    { "generictoggle5", command_target::vehicle },
    { "generictoggle6", command_target::vehicle },
    { "generictoggle7", command_target::vehicle },
    { "generictoggle8", command_target::vehicle },
    { "generictoggle9", command_target::vehicle },
    { "batterytoggle", command_target::vehicle },
    { "batteryenable", command_target::vehicle },
    { "batterydisable", command_target::vehicle },
    { "motorblowerstogglefront", command_target::vehicle },
    { "motorblowerstogglerear", command_target::vehicle },
    { "motorblowersdisableall", command_target::vehicle },
    { "coolingfanstoggle", command_target::vehicle },
    { "tempomattoggle", command_target::vehicle },
	{ "springbraketoggle", command_target::vehicle },
	{ "springbrakeenable", command_target::vehicle },
	{ "springbrakedisable", command_target::vehicle },
	{ "springbrakeshutofftoggle", command_target::vehicle },
	{ "springbrakeshutoffenable", command_target::vehicle },
	{ "springbrakeshutoffdisable", command_target::vehicle },
	{ "springbrakerelease", command_target::vehicle },
    { "distancecounteractivate", command_target::vehicle },
    { "speedcontrolincrease", command_target::vehicle },
	{ "speedcontroldecrease", command_target::vehicle },
	{ "speedcontrolpowerincrease", command_target::vehicle },
	{ "speedcontrolpowerdecrease", command_target::vehicle },
	{ "speedcontrolbutton0", command_target::vehicle },
	{ "speedcontrolbutton1", command_target::vehicle },
	{ "speedcontrolbutton2", command_target::vehicle },
	{ "speedcontrolbutton3", command_target::vehicle },
	{ "speedcontrolbutton4", command_target::vehicle },
	{ "speedcontrolbutton5", command_target::vehicle },
	{ "speedcontrolbutton6", command_target::vehicle },
	{ "speedcontrolbutton7", command_target::vehicle },
	{ "speedcontrolbutton8", command_target::vehicle },
	{ "speedcontrolbutton9", command_target::vehicle },

    { "globalradiostop", command_target::simulation },
    { "timejump", command_target::simulation },
    { "timejumplarge", command_target::simulation },
    { "timejumpsmall", command_target::simulation },
    { "setdatetime", command_target::simulation },
    { "setweather", command_target::simulation },
    { "settemperature", command_target::simulation },
    { "vehiclemoveforwards", command_target::vehicle },
    { "vehiclemovebackwards", command_target::vehicle },
    { "vehicleboost", command_target::vehicle },
    { "debugtoggle", command_target::simulation },
    { "focuspauseset", command_target::simulation },
    { "pausetoggle", command_target::simulation },
    { "entervehicle", command_target::simulation },
    { "resetconsist", command_target::simulation },
    { "fillcompressor", command_target::simulation },
    { "consistreleaser", command_target::simulation },
    { "queueevent", command_target::simulation },
    { "setlight", command_target::simulation },
    { "insertmodel", command_target::simulation },
    { "deletemodel", command_target::simulation },
    { "trainsetmove", command_target::simulation },
    { "consistteleport", command_target::simulation },
    { "pullalarmchain", command_target::simulation },
    { "sendaicommand", command_target::simulation },
    { "spawntrainset", command_target::simulation },
    { "destroytrainset", command_target::simulation },
    { "quitsimulation", command_target::simulation },
};

} // simulation

// posts specified command for specified recipient
void
command_queue::push( command_data const &Command, std::size_t const Recipient ) {
	if (is_network_target(Recipient)) {
		auto lookup = m_intercept_queue.emplace(Recipient, commanddata_sequence());
		lookup.first->second.emplace_back(Command);
	} else {
		push_direct(Command, Recipient);
	}
}

void command_queue::push_direct(const command_data &Command, const uint32_t Recipient) {
	auto lookup = m_commands.emplace( Recipient, commanddata_sequence() );
	// recipient stack was either located or created, so we can add to it quite safely
	lookup.first->second.emplace_back( Command );
}

// retrieves oldest posted command for specified recipient, if any. returns: true on retrieval, false if there's nothing to retrieve
bool
command_queue::pop( command_data &Command, std::size_t const Recipient ) {

    auto lookup = m_commands.find( Recipient );
    if( lookup == m_commands.end() ) {
        // no command stack for this recipient, so no commands
        return false;
    }
    auto &commands = lookup->second;
    if( true == commands.empty() ) {

        return false;
    }
    // we have command stack with command(s) on it, retrieve and pop the first one
    Command = commands.front();
    commands.pop_front();

    return true;
}

bool command_queue::is_network_target(uint32_t const Recipient) {
	const command_target target = (command_target)(Recipient & ~0xffff);

	if (target == command_target::entity)
		return false;

	return true;
}

command_queue::commands_map command_queue::pop_intercept_queue() {
	commands_map map(m_intercept_queue);
	m_intercept_queue.clear();
	return map;
}

void command_queue::push_commands(const commands_map &commands) {
	for (auto const &kv : commands)
		for (command_data const &data : kv.second)
			push_direct(data, kv.first);
}

void
command_relay::post(user_command const Command, double const Param1, double const Param2,
                     int const Action, uint16_t Recipient, glm::vec3 Position, const std::string *Payload) const {

    auto const &command = simulation::Commands_descriptions[ static_cast<std::size_t>( Command ) ];

	if (command.target == command_target::vehicle && Recipient == 0) {
		// default 0 recipient is currently controlled train
		if (simulation::Train == nullptr)
			return;
		Recipient = simulation::Train->id();
	}

    if( ( command.target == command_target::vehicle )
     && ( true == FreeFlyModeFlag )
     && ( ( false == DebugModeFlag )
       && ( true == Global.RealisticControlMode ) ) ) {
        // in realistic control mode don't pass vehicle commands if the user isn't in one, unless we're in debug mode
        return;
    }

	if (Position == glm::vec3(0.0f))
		Position = Global.pCamera.Pos;

	uint32_t combined_recipient = static_cast<uint32_t>( command.target ) | Recipient;
	command_data commanddata({Command, Action, Param1, Param2, Timer::GetDeltaTime(), Position });
	if (Payload)
		commanddata.payload = *Payload;

	simulation::Commands.push(commanddata, combined_recipient);
}

//---------------------------------------------------------------------------
