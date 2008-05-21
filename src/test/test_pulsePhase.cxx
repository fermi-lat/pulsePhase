#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

#include "facilities/commonUtilities.h"

#include "pulsarDb/FrequencyEph.h"
#include "pulsarDb/PulsarEph.h"

#include "timeSystem/AbsoluteTime.h"
#include "timeSystem/ElapsedTime.h"

#include "tip/Header.h"
#include "tip/IFileSvc.h"
#include "tip/Table.h"

using namespace pulsarDb;
using namespace timeSystem;

int main() {
  int status = 0;

  std::cerr.precision(20);
  std::cout.precision(20);

  // Set the data directory.
  std::string data_dir;
  try {
    data_dir = facilities::commonUtilities::getDataPath("pulsePhase");
  } catch (const std::exception & x) {
    std::cerr << x.what() << std::endl;
    return 1;
  }

  // Next test: read event file.
  std::auto_ptr<tip::Table> events(tip::IFileSvc::instance().editTable(facilities::commonUtilities::joinPath(data_dir, "D1.fits"),
    "EVENTS"));
 
  AbsoluteTime glast_origin("TDB", 51910, 0.);
  AbsoluteTime abs_epoch = glast_origin + ElapsedTime("TDB", Duration(0, 123.456789));
  FrequencyEph eph("TDB", abs_epoch, abs_epoch, abs_epoch, 0., 0., .11, 1.125e-2, -2.25e-4, 6.75e-6);

  // Add PULSE_PHASE field if missing.
  bool add_col = true;
  try {
    events->getFieldIndex("PULSE_PHASE");
    add_col = false;
  } catch (const tip::TipException &) {
  }
  if (add_col)
    events->appendField("PULSE_PHASE", "1D");

  // Iterate over events.
  for (tip::Table::Iterator itor = events->begin(); itor != events->end(); ++itor) {
    tip::Table::Record & rec = *itor;
    // Calculate phase.
    AbsoluteTime event_time = glast_origin + ElapsedTime("TDB", Duration(0, rec["TIME"].get()));
    double phase = eph.calcPulsePhase(event_time);

    // Write phase into output column.
    rec["PULSE_PHASE"].set(phase);
  }

  return status;
}
