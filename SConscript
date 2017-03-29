# -*- python -*-
# $Id: SConscript,v 1.33 2011/05/16 21:01:41 hirayama Exp $
# Authors: James Peachey <James.Peachey-1@nasa.gov>, Joe Asercion <joseph.a.asercion@nasa.gov>
# Version: pulsePhase-09-00-04

Import('baseEnv')
Import('listFiles')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

pulsePhaseLib = libEnv.StaticLibrary('pulsePhase', listFiles(['src/*.cxx']))

progEnv.Tool('pulsePhaseLib')
gtophaseBin = progEnv.Program('gtophase', listFiles(['src/gtophase/*.cxx']))
gtpphaseBin = progEnv.Program('gtpphase', listFiles(['src/gtpphase/*.cxx']))
test_pulsePhaseBin = progEnv.Program('test_pulsePhase', listFiles(['src/test/*.cxx']))

progEnv.Tool('registerTargets', package = 'pulsePhase',
             staticLibraryCxts = [[pulsePhaseLib, progEnv]],
             binaryCxts = [[gtophaseBin,progEnv], [gtpphaseBin, progEnv]],
             testAppCxts = [[test_pulsePhaseBin, progEnv]],
             includes = listFiles(['pulsePhase/*.h']),
             pfiles = listFiles(['pfiles/*.par']),
             data = listFiles(['data/*'], recursive = True))
