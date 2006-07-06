#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

#include "pulsarDb/PulsarEph.h"
#include "pulsarDb/TimingModel.h"

#include "st_facilities/Env.h"

#include "timeSystem/AbsoluteTime.h"
#include "timeSystem/TimeRep.h"

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
    data_dir = st_facilities::Env::getDataDir("pulsePhase");
  } catch (const std::exception & x) {
    std::cerr << x.what() << std::endl;
    return 1;
  }

  // Simple test of timing model computation.
  TimingModel model;

  // Next test: read event file.
  std::auto_ptr<tip::Table> events(tip::IFileSvc::instance().editTable(st_facilities::Env::appendFileName(data_dir, "D1.fits"), "EVENTS"));
 
  double valid_since = 0.;
  double valid_until = 0.;

  const tip::Header & header(events->getHeader());
  header["TSTART"].get(valid_since);
  header["TSTOP"].get(valid_until);

  MetRep glast_tdb("TDB", 51910, 0., 0.);
  glast_tdb.setValue(valid_since);
  AbsoluteTime abs_valid_since(glast_tdb);
  glast_tdb.setValue(valid_until);
  AbsoluteTime abs_valid_until(glast_tdb);
  glast_tdb.setValue(123.456789);
  AbsoluteTime abs_epoch(glast_tdb);
//  GlastTdbTime abs_valid_since(valid_since);
//  FrequencyEph eph(abs_valid_since, GlastTdbTime(valid_until), GlastTdbTime(123.456789), .11, 1.125e-2, -2.25e-4, 6.75e-6);
  FrequencyEph eph("TDB", abs_valid_since, abs_valid_until, abs_epoch, .11, 1.125e-2, -2.25e-4, 6.75e-6);

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
    glast_tdb.setValue(rec["TIME"].get());
    double phase = model.calcPulsePhase(eph, AbsoluteTime(glast_tdb));
//    double phase = model.calcPulsePhase(eph, GlastTdbTime(rec["TIME"].get()));

    // Write phase into output column.
    rec["PULSE_PHASE"].set(phase);
  }

  return status;
}
