# -*- python -*-
# $Id: SConscript,v 1.8 2008/09/26 20:30:32 glastrm Exp $
# Authors: James Peachey <James.Peachey-1@nasa.gov>
# Version: pulsePhase-07-02-00

Import('baseEnv')
Import('listFiles')
progEnv = baseEnv.Clone()

progEnv.Tool('pulsarDbLib')
progEnv.Tool('st_appLib')
progEnv.Tool('st_facilitiesLib')
progEnv.Tool('timeSystemLib')
progEnv.Tool('tipLib')

gtophaseBin = progEnv.Program('gtophase', listFiles(['src/gtophase/*.cxx']))
gtpphaseBin = progEnv.Program('gtpphase', listFiles(['src/gtpphase/*.cxx']))
test_pulsePhaseBin = progEnv.Program('test_pulsePhase', listFiles(['src/test/*.cxx']))

progEnv.Tool('registerObjects', package = 'pulsePhase', binaries = [gtophaseBin, gtpphaseBin], testApps = [test_pulsePhaseBin], pfiles = listFiles(['pfiles/*.par']),
             data = listFiles(['data/*'], recursive = True))
