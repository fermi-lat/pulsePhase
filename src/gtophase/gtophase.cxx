#include <cctype>
#include <cmath>
#include <iostream>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>

#include "pulsarDb/EphChooser.h"
#include "pulsarDb/EphComputer.h"
#include "pulsarDb/EphStatus.h"
#include "pulsarDb/PulsarToolApp.h"

#include "timeSystem/AbsoluteTime.h"
#include "timeSystem/EventTimeHandler.h"
#include "timeSystem/GlastTimeHandler.h"

#include "st_app/AppParGroup.h"
#include "st_app/StApp.h"
#include "st_app/StAppFactory.h"

#include "st_stream/Stream.h"
#include "st_stream/StreamFormatter.h"

using namespace pulsarDb;
using namespace timeSystem;

const std::string s_cvs_id("$Name:  $");

class OrbitalPhaseApp : public pulsarDb::PulsarToolApp {
  public:
    OrbitalPhaseApp();
    virtual void run();

  private:
    st_stream::StreamFormatter m_os;
};

OrbitalPhaseApp::OrbitalPhaseApp(): pulsarDb::PulsarToolApp(), m_os("OrbitalPhaseApp", "", 2) {
  setName("gtophase");
  setVersion(s_cvs_id);
}

void OrbitalPhaseApp::run() {
  // Clean up from any previous runs.
  resetApp();

  st_app::AppParGroup & par_group = getParGroup(); // getParGroup is in base class st_app::StApp

  // Prompt for selected parameters.
  par_group.Prompt("evfile");
  par_group.Prompt("evtable");
  par_group.Prompt("timefield");
  par_group.Prompt("scfile");
  par_group.Prompt("sctable");
  par_group.Prompt("psrdbfile");
  par_group.Prompt("psrname");
  par_group.Prompt("ra");
  par_group.Prompt("dec");
  par_group.Prompt("solareph");
  par_group.Prompt("matchsolareph");
  par_group.Prompt("angtol");
  par_group.Prompt("ophasefield");
  par_group.Prompt("ophaseoffset");
  par_group.Prompt("reportephstatus");

  par_group.Prompt("chatter");
  par_group.Prompt("clobber");
  par_group.Prompt("debug");
  par_group.Prompt("gui");
  par_group.Prompt("mode");

  par_group.Save();

  // Open the event file(s).
  openEventFile(par_group, false);

  // Setup time correction mode.
  defineTimeCorrectionMode("DEFAULT", REQUIRED, REQUIRED, SUPPRESSED);
  selectTimeCorrectionMode("DEFAULT");

  // Set up EphComputer for arrival time corrections.
  pulsarDb::StrictEphChooser chooser;
  initEphComputer(par_group, chooser, "NONE");

  // Use user input (parameters) together with computer to determine corrections to apply.
  bool vary_ra_dec = false;
  bool guess_pdot = false;
  initTimeCorrection(par_group, vary_ra_dec, guess_pdot, "START");

  // Report ephemeris status.
  std::set<EphStatusCodeType> code_to_report;
  code_to_report.insert(Remarked);
  reportEphStatus(m_os.warn(), code_to_report);

  // Reserve output column for creation if not existing in the event file(s).
  std::string phase_field = par_group["ophasefield"];
  reserveOutputField(phase_field, "1D");

  // Get EphComputer for orbital phase computation.
  EphComputer & computer(getEphComputer());

  // Read global phase offset.
  double phase_offset = par_group["ophaseoffset"];

  // Iterate over events.
  for (setFirstEvent(); !isEndOfEventList(); setNextEvent()) {
    // Get event time as AbsoluteTime.
    AbsoluteTime abs_evt_time(getEventTime());

    // Compute phase.
    double phase = computer.calcOrbitalPhase(abs_evt_time, phase_offset);

    // Write phase into output column.
    setFieldValue(phase_field, phase);
  }

}

// List supported mission(s).
timeSystem::EventTimeHandlerFactory<timeSystem::GlastTimeHandler> glast_handler;

st_app::StAppFactory<OrbitalPhaseApp> g_factory("gtophase");
